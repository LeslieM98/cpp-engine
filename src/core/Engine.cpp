//
// Created by Leslie on 13.10.2024.
//

#include "core/Engine.hpp"

<<<<<<< HEAD
using namespace fimbulwinter::engine::core;
=======
using namespace fimbulwinter::engine;
>>>>>>> 354d66004a1f79e0a83f252265d6b653d7118b04

void Engine::resizeComponentStorage() {
    const auto newSize = Component::getRegisteredComponents().size();

    for (auto &entity: Engine::entities) {
        entity.resize(newSize);
    }
}

void Engine::tick() {
    for (auto &stage: this->systemStorage) {
        for (auto &subStage: stage) {

            for (auto &system: subStage) {
                for (auto &entity: this->entities) {
                    std::vector<Component *> componentView(entity.size()); // TODO: Garbage Code
                    for (int i = 0; i < entity.size(); i++) {
                        componentView[i] = entity[i].get();
                    }
                    const auto systemHasRun = system->run(componentView);
                }
            }

        }
    }
}

Engine::EntityId Engine::instanciateEntity(const std::vector<Component *> components) {
    this->entities.emplace_back();
    this->resizeComponentStorage();
    auto &newestEntity = this->entities.back();

    for (auto &component: components) {
        newestEntity[component->getId()].reset(component);
    }
    return this->entities.size() - 1;
}

void Engine::registerSystem(SystemFunctorBase *system) {
    const Stage stage = system->getStage();
    const SubStage subStage = system->getSubStage();

    const auto stageIdx = static_cast<int>(stage);
    const auto subStageIdx = static_cast<int>(subStage);
    const auto stageCount = stageIdx + 1;
    const auto subStageCount = subStageIdx + 1;

    if (this->systemStorage.size() < stageCount) {
        this->systemStorage.resize(stageCount);
    }
    if (this->systemStorage[stageIdx].size() < subStageCount) {
        this->systemStorage[stageIdx].resize(subStageCount);
    }
    this->systemStorage[stageIdx].reserve(subStageIdx + 1);

    this->systemStorage[stageIdx][subStageIdx].emplace_back(system);
}

void Engine::run() {
    workerThread = std::jthread([this](std::stop_token stopToken) {
        while (!stopToken.stop_requested()) {
            this->tick();
        }
    });
}

void Engine::terminate() {
    this->workerThread->request_stop();
}


