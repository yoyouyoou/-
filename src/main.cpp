#include <QCoreApplication>
#include <QDebug>

#include "core/controller/plant_orchestrator.h"

using namespace bms;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    auto groupA = std::make_shared<Group>("group-A");
    auto stackA1 = std::make_shared<Stack>("stack-A1");
    auto stackA2 = std::make_shared<Stack>("stack-A2");

    auto clusterA11 = std::make_shared<Cluster>("cluster-A1-1");
    auto clusterA12 = std::make_shared<Cluster>("cluster-A1-2");
    auto clusterA21 = std::make_shared<Cluster>("cluster-A2-1");

    stackA1->addCluster(clusterA11);
    stackA1->addCluster(clusterA12);
    stackA2->addCluster(clusterA21);

    groupA->addStack(stackA1);
    groupA->addStack(stackA2);

    QObject::connect(groupA.get(), &Group::snapshotUpdated, [](const QString& groupId, const GroupSnapshot& snapshot) {
        qInfo().nospace()
            << "[" << groupId << "] V=" << snapshot.totalVoltageV
            << "V I=" << snapshot.totalCurrentA
            << "A Tmax=" << snapshot.maxTempC
            << "C runningStacks=" << snapshot.runningStacks;
    });

    QObject::connect(groupA.get(), &Group::stateChanged,
                     [](const QString& groupId, const QString& stackId, ControlState previous, ControlState current) {
                         qInfo() << "State" << groupId << stackId << toString(previous) << "=>" << toString(current);
                     });

    PlantOrchestrator orchestrator;
    orchestrator.addGroup(groupA);

    clusterA11->updateTelemetry({52.3, 15.2, 34.1, true});
    clusterA12->updateTelemetry({52.0, 15.1, 33.8, true});
    clusterA21->updateTelemetry({51.8, 15.0, 35.0, true});

    orchestrator.bootAll();
    orchestrator.startAll();
    orchestrator.stopAll();

    return 0;
}
