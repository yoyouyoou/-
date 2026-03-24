#include "core/model/cluster.h"

namespace bms {

Cluster::Cluster(QString id, QObject* parent)
    : QObject(parent), id_(std::move(id)) {}

const QString& Cluster::id() const {
    return id_;
}

const ClusterTelemetry& Cluster::telemetry() const {
    return telemetry_;
}

void Cluster::updateTelemetry(const ClusterTelemetry& telemetry) {
    telemetry_ = telemetry;
    emit telemetryUpdated(id_, telemetry_);
}

} // namespace bms
