cmake_minimum_required(VERSION 3.0.2)
project(Ardupilot-RTCOP-ROS)

set(CMAKE_C_FLAGS "-no-pie -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS "-no-pie -std=c++11 -pthread")
set(CMAKE_AUTORCC ON)
find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  mavros
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES Ardupilot-RTCOP-ROS
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
    ../RTCOP/Include
    include
    ./Generated
    ./gnc
    ./PLAM
    .
    ${catkin_INCLUDE_DIRS}
)

file(GLOB MY_L_SOURCES *.lcpp)
add_custom_command(OUTPUT Generated COMMAND "mono" "${PROJECT_SOURCE_DIR}/../RTCOP/Tool/LayerCompiler.exe" "${MY_L_SOURCES}" "-r" "${PROJECT_SOURCE_DIR}" "-i" "${PROJECT_SOURCE_DIR}" "-t" "linux64" "-e" "gcc" "-o" "${PROJECT_SOURCE_DIR}/Generated")
link_directories(../RTCOP/Library/Linux/x64)
file(GLOB MY_SOURCES *.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp)
add_executable(${PROJECT_NAME}_node Generated ${MY_SOURCES})
target_link_libraries(${PROJECT_NAME}_node
  RTCOP
  ${catkin_LIBRARIES}
)

