#pragma once

#include <QObject>
#include <QString>

namespace bms {

struct ClusterTelemetry {
    double voltageV {0.0};
    double currentA {0.0};
    double maxTempC {0.0};
    bool communicationOk {true};
};

class Cluster : public QObject {
    Q_OBJECT

public:
    explicit Cluster(QString id, QObject* parent = nullptr);

    const QString& id() const;
    const ClusterTelemetry& telemetry() const;

    void updateTelemetry(const ClusterTelemetry& telemetry);

signals:
    void telemetryUpdated(const QString& clusterId, const bms::ClusterTelemetry& telemetry);

private:
    QString id_;
    ClusterTelemetry telemetry_;
};

} // namespace bms
