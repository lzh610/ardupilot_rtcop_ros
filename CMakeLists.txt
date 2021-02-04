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
    ./timer
    .
    ${catkin_INCLUDE_DIRS}
    
)

file(GLOB MY_L_SOURCES *.lcpp)
add_custom_command(OUTPUT Generated COMMAND "mono" "${PROJECT_SOURCE_DIR}/../RTCOP/Tool/LayerCompiler.exe" "${MY_L_SOURCES}" "-r" "${PROJECT_SOURCE_DIR}" "-i" "${PROJECT_SOURCE_DIR}" "-t" "linux64" "-e" "gcc" "-o" "${PROJECT_SOURCE_DIR}/Generated")
link_directories(../RTCOP/Library/Linux/x64)
file(GLOB MAIN main.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB GROUND LCN/ground_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_1 LCN/test_1_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_2 LCN/test_2_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_3 LCN/test_3_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_4 LCN/test_4_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_5 LCN/test_5_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_6 LCN/test_6_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_7 LCN/test_7_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_8 LCN/test_8_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_9 LCN/test_9_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)
file(GLOB TEST_10 LCN/test_10_node.cpp Generated/*.cpp gnc/*.cpp PLAM/*.cpp timer/*.cpp)

add_executable(${PROJECT_NAME}_node Generated ${MAIN})
add_executable(ground_node Generated ${GROUND})
add_executable(test_1_node Generated ${TEST_1})
add_executable(test_2_node Generated ${TEST_2})
add_executable(test_3_node Generated ${TEST_3})
add_executable(test_4_node Generated ${TEST_4})
add_executable(test_5_node Generated ${TEST_5})
add_executable(test_6_node Generated ${TEST_6})
add_executable(test_7_node Generated ${TEST_7})
add_executable(test_8_node Generated ${TEST_8})
add_executable(test_9_node Generated ${TEST_9})
add_executable(test_10_node Generated ${TEST_10})



target_link_libraries(${PROJECT_NAME}_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(ground_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_1_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_2_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_3_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_4_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_5_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_6_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_7_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_8_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_9_node
  RTCOP
  ${catkin_LIBRARIES}
)

target_link_libraries(test_10_node
  RTCOP
  ${catkin_LIBRARIES}
)