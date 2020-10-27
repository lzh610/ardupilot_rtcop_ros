//
//  ActiveController.hpp
//  AAA
//
//  Created by 劉子涵 on 2020/03/22.
//  Copyright © 2020 劉子涵. All rights reserved.
//

#ifndef ActiveController_h
#define ActiveController_h

#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "API.h"

using namespace std;
//-------------データ構造--------------
//スレードのコントローラー
namespace PLAM{
class ActiveController{
private:
    RTCOP::Generated::LayerID layerid;
    int status;//0:正常系;1:一旦停止;2:中断
    thread::id thread_id;//中断ポイントを実行するとき
public:
    ActiveController(RTCOP::Generated::LayerID id,int s,thread::id tid);
    void set_id(RTCOP::Generated::LayerID id);
    void set_status(int s);
    void set_threadId(thread::id id);
    RTCOP::Generated::LayerID get_id();
    int get_status();
    thread::id get_threadId();
    
};

extern mutex m;

//スレードのコントローラーを管理リスト
extern vector<ActiveController> controller;

//異常処理レイヤを実行するとき他のレイヤのアクティベーションを実行させないようなコントローラー
extern int emergency_flag;


//---------------------------
//タイマー
extern time_t t;

//正常系アクティベート
extern void active_normal(RTCOP::Generated::LayerID layerid);

//正常系デアクティベーション
extern void deactive_normal(RTCOP::Generated::LayerID layerid);

//異常処理・アクティベーション-------------------------
//他の正常系アクティベートを全部中断させる
extern void active_break(RTCOP::Generated::LayerID layerid);

//指定された正常系アクティベートを中断させる
extern void active_break(RTCOP::Generated::LayerID layerid,vector<RTCOP::Generated::LayerID> target_layerid);

//他の正常系アクティベートを全部一時停止させる
extern void active_suspend(RTCOP::Generated::LayerID layerid);

//指定された正常系アクティベートを一時停止させる
extern void active_suspend(RTCOP::Generated::LayerID layerid,vector<RTCOP::Generated::LayerID> target_layerid);

//デアクティベートまで一時停止
extern void active_suspend_until_deactive(RTCOP::Generated::LayerID layerid);

//デアクティベートまで一時停止（1 to n）
extern void active_suspend_until_deactive(RTCOP::Generated::LayerID layerid,vector<RTCOP::Generated::LayerID> target_layerid);
//------------------------------------------------------------

//中断ポイント
extern void break_point();


//異常処理・デアクティベーション--------------------------
//他の正常系デアクティベートを全部中断させる
extern void deactive_break(RTCOP::Generated::LayerID layerid);

//指定された正常系デアクティベートを中断させる
extern void deactive_break(RTCOP::Generated::LayerID layerid,vector<RTCOP::Generated::LayerID> target_layerid);

//他の正常系デアクティベートを全部一時停止させる
extern void deactive_suspend(RTCOP::Generated::LayerID layerid);

//指定された正常系デアクティベートを一時停止させる
extern void deactive_suspend(RTCOP::Generated::LayerID layerid,vector<RTCOP::Generated::LayerID> target_layerid);




}
#endif /* ActiveController_h */
