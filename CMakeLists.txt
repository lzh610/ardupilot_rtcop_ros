cmake_minimum_required(VERSION 3.0.2)
project(ardupilot_rtcop_ros)

set(CMAKE_C_FLAGS "-no-pie -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS "-no-pie -std=c++1z -pthread")
set(CMAKE_AUTORCC ON)
find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  mavros
  roscpp
  std_msgs
  genmsg
  message_generation
)

add_service_files(
  DIRECTORY srv
  FILES
  activation_msg.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES Ardupilot-RTCOP-ROS
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
CATKIN_DEPENDS message_runtime
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
file(GLOB MAIN main.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp)
file(GLOB GROUND ground_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp)
file(GLOB FLIGHT flight_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp)
file(GLOB NOSIGNAL nosignal_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp)
add_executable(${PROJECT_NAME}_node Generated ${MAIN})
add_executable(ground_node Generated ${GROUND})
add_executable(flight_node Generated ${FLIGHT})
add_executable(nosignal_node Generated ${NOSIGNAL})

target_link_libraries(${PROJECT_NAME}_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(ground_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(flight_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(nosignal_node
  RTCOP
  ${catkin_LIBRARIES}
)


