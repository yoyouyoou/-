# BMS Backend (Qt/Linux) 工程骨架

基于 Linux + Qt(Core) 的 BMS 四级控制架构后台应用初版模板：

- Group（分组控制）
- Stack（每组若干堆）
- Cluster（每堆控制簇）
- 状态机模板（INIT/STANDBY/PRECHARGE/RUNNING/STOPPING/FAULT_LOCKED）

## 目录

```text
.
├── CMakeLists.txt
├── src
│   ├── main.cpp
│   └── core
│       ├── controller
│       │   ├── plant_orchestrator.cpp
│       │   └── plant_orchestrator.h
│       ├── model
│       │   ├── cluster.cpp
│       │   ├── cluster.h
│       │   ├── group.cpp
│       │   ├── group.h
│       │   ├── stack.cpp
│       │   └── stack.h
│       └── state_machine
│           ├── control_state.cpp
│           └── control_state.h
```

## 构建

> 需要预先安装 Qt6 开发环境（Qt6Config.cmake 可被 CMake 找到）

```bash
cmake -S . -B build
cmake --build build -j
```

## 后续建议

1. 将 Cluster 下行通信接入 CAN/Modbus 适配器。
2. Stack 增加 SOC/SOH/SOP 算法模块。
3. Group 增加功率分配策略与保护优先级。
4. Plant 层增加 EMS/SCADA 接口（MQTT/OPC UA）。
