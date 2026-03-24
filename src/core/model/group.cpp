#include "core/model/group.h"
#include <algorithm>

namespace bms {

Group::Group(QString id, QObject* parent)
    : QObject(parent), id_(std::move(id)) {}

void Group::addStack(const std::shared_ptr<Stack>& stack) {
    stacks_.append(stack);
    connect(stack.get(), &Stack::snapshotUpdated, this, &Group::onStackSnapshot);
    connect(stack.get(), &Stack::stateChanged, this, &Group::onStackState);
    refreshSnapshot();
}

const QString& Group::id() const {
    return id_;
}

GroupSnapshot Group::snapshot() const {
    return snapshot_;
}

void Group::dispatch(ControlEvent event) {
    for (const auto& stack : stacks_) {
        stack->dispatch(event);
    }
    refreshSnapshot();
    emit snapshotUpdated(id_, snapshot_);
}

void Group::onStackSnapshot(const QString&, const StackSnapshot&) {
    refreshSnapshot();
    emit snapshotUpdated(id_, snapshot_);
}

void Group::onStackState(const QString& stackId, ControlState previous, ControlState current) {
    Q_UNUSED(previous)
    Q_UNUSED(current)
    emit stateChanged(id_, stackId, previous, current);
    refreshSnapshot();
    emit snapshotUpdated(id_, snapshot_);
}

void Group::refreshSnapshot() {
    GroupSnapshot next;
    for (const auto& stack : stacks_) {
        const auto s = stack->snapshot();
        next.totalVoltageV += s.totalVoltageV;
        next.totalCurrentA += s.totalCurrentA;
        next.maxTempC = std::max(next.maxTempC, s.maxTempC);
        if (stack->state() == ControlState::Running) {
            ++next.runningStacks;
        }
    }
    snapshot_ = next;
}

} // namespace bms
