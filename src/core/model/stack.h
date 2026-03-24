#pragma once

#include <QObject>
#include <QVector>
#include <memory>

#include "core/model/cluster.h"
#include "core/state_machine/control_state.h"

namespace bms {

struct StackSnapshot {
    double totalVoltageV {0.0};
    double totalCurrentA {0.0};
    double maxTempC {0.0};
};

class Stack : public QObject {
    Q_OBJECT

public:
    explicit Stack(QString id, QObject* parent = nullptr);

    void addCluster(const std::shared_ptr<Cluster>& cluster);
    const QString& id() const;
    ControlState state() const;
    StackSnapshot snapshot() const;

public slots:
    void dispatch(ControlEvent event);

signals:
    void stateChanged(const QString& stackId, bms::ControlState previous, bms::ControlState current);
    void snapshotUpdated(const QString& stackId, const bms::StackSnapshot& snapshot);

private slots:
    void onClusterTelemetry(const QString& clusterId, const bms::ClusterTelemetry& telemetry);

private:
    void refreshSnapshot();

    QString id_;
    QVector<std::shared_ptr<Cluster>> clusters_;
    ControlState state_ {ControlState::Init};
    StackSnapshot snapshot_;
};

} // namespace bms
