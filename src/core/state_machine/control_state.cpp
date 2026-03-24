#include "core/state_machine/control_state.h"

namespace bms {

QString toString(ControlState state) {
    switch (state) {
    case ControlState::Init: return "INIT";
    case ControlState::Standby: return "STANDBY";
    case ControlState::Precharge: return "PRECHARGE";
    case ControlState::Running: return "RUNNING";
    case ControlState::Stopping: return "STOPPING";
    case ControlState::FaultLocked: return "FAULT_LOCKED";
    }
    return "UNKNOWN";
}

QString toString(ControlEvent event) {
    switch (event) {
    case ControlEvent::BootComplete: return "BOOT_COMPLETE";
    case ControlEvent::StartRequested: return "START_REQUESTED";
    case ControlEvent::PrechargeOk: return "PRECHARGE_OK";
    case ControlEvent::StopRequested: return "STOP_REQUESTED";
    case ControlEvent::StopCompleted: return "STOP_COMPLETED";
    case ControlEvent::FaultDetected: return "FAULT_DETECTED";
    case ControlEvent::FaultCleared: return "FAULT_CLEARED";
    case ControlEvent::CommunicationLost: return "COMMUNICATION_LOST";
    }
    return "UNKNOWN";
}

ControlState nextState(ControlState current, ControlEvent event) {
    if (event == ControlEvent::FaultDetected || event == ControlEvent::CommunicationLost) {
        return ControlState::FaultLocked;
    }

    switch (current) {
    case ControlState::Init:
        if (event == ControlEvent::BootComplete) {
            return ControlState::Standby;
        }
        break;
    case ControlState::Standby:
        if (event == ControlEvent::StartRequested) {
            return ControlState::Precharge;
        }
        break;
    case ControlState::Precharge:
        if (event == ControlEvent::PrechargeOk) {
            return ControlState::Running;
        }
        if (event == ControlEvent::StopRequested) {
            return ControlState::Stopping;
        }
        break;
    case ControlState::Running:
        if (event == ControlEvent::StopRequested) {
            return ControlState::Stopping;
        }
        break;
    case ControlState::Stopping:
        if (event == ControlEvent::StopCompleted) {
            return ControlState::Standby;
        }
        break;
    case ControlState::FaultLocked:
        if (event == ControlEvent::FaultCleared) {
            return ControlState::Standby;
        }
        break;
    }

    return current;
}

} // namespace bms
