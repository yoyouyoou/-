#pragma once

#include <QObject>
#include <QVector>
#include <memory>

#include "core/model/group.h"

namespace bms {

class PlantOrchestrator : public QObject {
    Q_OBJECT

public:
    explicit PlantOrchestrator(QObject* parent = nullptr);

    void addGroup(const std::shared_ptr<Group>& group);
    void bootAll();
    void startAll();
    void stopAll();

private:
    QVector<std::shared_ptr<Group>> groups_;
};

} // namespace bms
