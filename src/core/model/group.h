#pragma once

#include <QObject>
#include <QVector>
#include <memory>

#include "core/model/stack.h"

namespace bms {

struct GroupSnapshot {
    double totalVoltageV {0.0};
    double totalCurrentA {0.0};
    double maxTempC {0.0};
    qsizetype runningStacks {0};
};

class Group : public QObject {
    Q_OBJECT

public:
    explicit Group(QString id, QObject* parent = nullptr);

    void addStack(const std::shared_ptr<Stack>& stack);
    const QString& id() const;
    GroupSnapshot snapshot() const;

public slots:
    void dispatch(ControlEvent event);

signals:
    void snapshotUpdated(const QString& groupId, const bms::GroupSnapshot& snapshot);
    void stateChanged(const QString& groupId, const QString& stackId, bms::ControlState previous, bms::ControlState current);

private slots:
    void onStackSnapshot(const QString& stackId, const bms::StackSnapshot& snapshot);
    void onStackState(const QString& stackId, bms::ControlState previous, bms::ControlState current);

private:
    void refreshSnapshot();

    QString id_;
    QVector<std::shared_ptr<Stack>> stacks_;
    GroupSnapshot snapshot_;
};

} // namespace bms
