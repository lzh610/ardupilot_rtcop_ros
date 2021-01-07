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
(既にcatkin_ws/srcを作ったことを前提とする)
```
cd catkin_ws/src
git clone https://github.com/tanigawaikuta/RTCOP.git
```

### Ardupilot-RTCOP-ROS
```
cd catkin_ws/src
https://github.com/lzh610/Ardupilot-RTCOP-ROS.git
```

### ビルド
```
cd catkin_ws/src
catkin build
source ~/.bashrc
```

## 実行

```
cd ~/catkin_ws/src/ardupilot_rtcop_ros/shell/
sh node_group_start.sh
```

十秒ぐらいを待ちして

```
rosrun ardupilot_rtcop_ros ardupilot_rtcop_ros_node
```

を実行する

元のターミナルで３つのタブが自動的に開かれる（以下で左側からA,B,Cと略称する）

Aタブでメインノードを実行する

レイヤコントロールノードにおけるリクエスト情報がＢタブに見られる

メインノードの動かせるためＣタブでmode guidedを入力してください。

## チュートリアル

https://github.com/Intelligent-Quads/iq_tutorials

（ビデオ版のリンクもこのページに記載されている）
