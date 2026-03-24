#pragma once

#include <QString>

namespace bms {

enum class ControlState {
    Init,
    Standby,
    Precharge,
    Running,
    Stopping,
    FaultLocked
};

enum class ControlEvent {
    BootComplete,
    StartRequested,
    PrechargeOk,
    StopRequested,
    StopCompleted,
    FaultDetected,
    FaultCleared,
    CommunicationLost
};

QString toString(ControlState state);
QString toString(ControlEvent event);
ControlState nextState(ControlState current, ControlEvent event);

} // namespace bms
