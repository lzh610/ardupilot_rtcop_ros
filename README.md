# Ardupilot-RTCOP-ROS

## 依頼
- ROS-gazebo
- Ardupilot
- RTCOP

## プロジェクト構成
catkin_ws/src/
 
 -Ardupilot-RTCOP-ROS
 
 -iq_sim
 
 -mavlink 
 
 -mavros
 
 -RTCOP

## 実装方法

### ROS相関
https://github.com/Intelligent-Quads/iq_tutorials/blob/master/docs/installing_ros.md

### Ardupilot
https://github.com/Intelligent-Quads/iq_tutorials/blob/master/docs/Installing_Ardupilot.md

### GAZEBO
https://github.com/Intelligent-Quads/iq_tutorials/blob/master/docs/installing_gazebo_arduplugin.md

### RTCOP
(既にcatkin_ws/srcを作ることを前提とする)
```
cd catkin_ws/src
git clone https://github.com/tanigawaikuta/RTCOP.git
```

### Ardupilot-RTCOP-ROS
```
cd catkin_ws/src
https://github.com/lzh610/Ardupilot-RTCOP-ROS.git
```

###　ビルド
```
cd catkin_ws/src
catkin build
source ~/.bashrc
```

## 実行

ターミナル４つ開く（A，B，C，Dと略称）
順番により
```
roslaunch iq_sim runway.launch　
cd ~/ardupilot/ArduCopter/ && sim_vehicle.py -v ArduCopter -f gazebo-iris --cons
roslaunch iq_sim apm.launch
rosrun Ardupilot-RTCOP-ROS Ardupilot-RTCOP-ROS_node
```

を実行する

Ｄを実行したらＢに戻し、"mode guided"を実行

すべてのINFOをＤで表示する。


