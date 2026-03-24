#include "core/controller/plant_orchestrator.h"

namespace bms {

PlantOrchestrator::PlantOrchestrator(QObject* parent)
    : QObject(parent) {}

void PlantOrchestrator::addGroup(const std::shared_ptr<Group>& group) {
    groups_.append(group);
}

void PlantOrchestrator::bootAll() {
    for (const auto& group : groups_) {
        group->dispatch(ControlEvent::BootComplete);
    }
}

void PlantOrchestrator::startAll() {
    for (const auto& group : groups_) {
        group->dispatch(ControlEvent::StartRequested);
        group->dispatch(ControlEvent::PrechargeOk);
    }
}

void PlantOrchestrator::stopAll() {
    for (const auto& group : groups_) {
        group->dispatch(ControlEvent::StopRequested);
        group->dispatch(ControlEvent::StopCompleted);
    }
}

} // namespace bms
