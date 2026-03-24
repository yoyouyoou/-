cmake_minimum_required(VERSION 3.21)
project(bms_backend VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(bms_backend
    src/main.cpp
    src/core/model/cluster.cpp
    src/core/model/stack.cpp
    src/core/model/group.cpp
    src/core/controller/plant_orchestrator.cpp
    src/core/state_machine/control_state.cpp
)

target_include_directories(bms_backend PRIVATE src)

target_link_libraries(bms_backend PRIVATE Qt6::Core)
