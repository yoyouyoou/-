#include "core/model/stack.h"
#include <algorithm>

namespace bms {

Stack::Stack(QString id, QObject* parent)
    : QObject(parent), id_(std::move(id)) {}

void Stack::addCluster(const std::shared_ptr<Cluster>& cluster) {
    clusters_.append(cluster);
    connect(cluster.get(), &Cluster::telemetryUpdated, this, &Stack::onClusterTelemetry);
    refreshSnapshot();
}

const QString& Stack::id() const {
    return id_;
}

ControlState Stack::state() const {
    return state_;
}

StackSnapshot Stack::snapshot() const {
    return snapshot_;
}

void Stack::dispatch(ControlEvent event) {
    const auto previous = state_;
    state_ = nextState(state_, event);
    if (previous != state_) {
        emit stateChanged(id_, previous, state_);
    }
}

void Stack::onClusterTelemetry(const QString&, const ClusterTelemetry&) {
    refreshSnapshot();
    emit snapshotUpdated(id_, snapshot_);
}

void Stack::refreshSnapshot() {
    StackSnapshot next;
    for (const auto& cluster : clusters_) {
        const auto& t = cluster->telemetry();
        next.totalVoltageV += t.voltageV;
        next.totalCurrentA += t.currentA;
        next.maxTempC = std::max(next.maxTempC, t.maxTempC);
    }
    snapshot_ = next;
}

} // namespace bms
