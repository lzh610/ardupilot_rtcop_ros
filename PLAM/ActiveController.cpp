//
//  ActiveController.cpp
//  AAA
//
//  Created by 劉子涵 on 2020/03/22.
//  Copyright © 2020 劉子涵. All rights reserved.
//

#include "ActiveController.h"


using namespace std;
using namespace RTCOP;
namespace PLAM{
ActiveController::ActiveController(RTCOP::Generated::LayerID id,int s,thread::id tid){
    layerid = id;
    status = s;
    thread_id = tid;
}

void ActiveController::set_id(RTCOP::Generated::LayerID id){
    layerid = id;
}

void ActiveController::set_status(int s){
    status = s;
}

void ActiveController::set_threadId(thread::id id){
    thread_id = id;
}

RTCOP::Generated::LayerID ActiveController::get_id(){
    return layerid;
}

int ActiveController::get_status(){
    return status;
}

thread::id ActiveController::get_threadId(){
    return thread_id;
}


vector<ActiveController> controller;
int emergency_flag = 0;
mutex m;


void thread_sleep(int index){
    while (controller[index].get_status() == 1) {
        chrono::milliseconds duration(20);
        this_thread::sleep_for(duration);
    }
}

int get_this_thread_index(thread::id tid){
    //cout<<tid;
    int index=0;
    for(int i=0;i<controller.size();i++){
        if(controller[i].get_threadId() == tid){
            index = i;
            break;
        }
    }
    return index;
}

void break_point(){
    int index = get_this_thread_index(this_thread::get_id());
    //cout<<controller[index].get_status();
    //printf("%d %d %d\n",index,this_thread::get_id(),controller[index].get_status());
    if(controller[index].get_status() == 1){
        thread_sleep(index);
    }
    else if(controller[index].get_status() == 2)
        pthread_exit(NULL);
}

void active_emergency(RTCOP::Generated::LayerID layerid, int s, RTCOP::Generated::LayerID target_layerid,bool b){
    m.lock();
    ActiveController ac(layerid,0,this_thread::get_id());
    controller.push_back(ac);
    emergency_flag = 1;
    m.unlock();
    if(layerid == target_layerid){
        for(int i = 0;i < controller.size();i++){
            //printf("%d,%d\n",controller[i].get_id(),controller[i].get_threadId());
            if(controller[i].get_id() != layerid){
                //printf("suspend :%d;thread id:%d\n",i,controller[i].get_threadId());
                controller[i].set_status(s);
                //printf("status:%d",controller[i].get_status());
            }
        }
    
        activate(layerid);
        if(b == true){
            for(int i = 0;i < controller.size();i++){
                if(controller[i].get_id() != layerid){
                    controller[i].set_status(0);
                }
            }   
        }
    }
    
    else{
        int target_index = 0;
        for(int i = 0;i < controller.size();i++){
            if(controller[i].get_id() == target_layerid){
                controller[i].set_status(s);
                target_index = i;
                break;
            }
        }
        activate(layerid);
        if(b == true)
            controller[target_index].set_status(0);
    }
    
    m.lock();
    emergency_flag = 0;
    controller.erase(controller.begin()+get_this_thread_index(this_thread::get_id()));
    m.unlock();
}

void deactive_emergency(RTCOP::Generated::LayerID layerid, RTCOP::Generated::LayerID target_layerid){
    m.lock();
    ActiveController ac(layerid,0,this_thread::get_id());
    controller.push_back(ac);
    emergency_flag = 1;
    m.unlock();
    if(layerid == target_layerid){
        deactivate(layerid);
        for(int i = 0;i < controller.size();i++){

            if(controller[i].get_id() != layerid){
                controller[i].set_status(0);
            }
        }
    }
    else{
        //int target_index = 0;
        for(int i = 0;i < controller.size();i++){
            deactivate(layerid);
            if(controller[i].get_id() == target_layerid){
                controller[i].set_status(0);
                //target_index = i;
                break;
            }
        }
    }
    m.lock();
    emergency_flag = 0;
    controller.erase(controller.begin()+get_this_thread_index(this_thread::get_id()));
    m.unlock();
}






void active(RTCOP::Generated::LayerID layerid){
    
    while (emergency_flag == 1) {
        chrono::milliseconds duration(20);
        this_thread::sleep_for(duration);
    }
    
    m.lock();
    ActiveController ac(layerid,0,this_thread::get_id());
    controller.push_back(ac);
    m.unlock();
    
    activate(layerid);
    
    m.lock();
    controller.erase(controller.begin()+get_this_thread_index(this_thread::get_id()));
    m.unlock();
}

void active2(RTCOP::Generated::LayerID layerid){
    
    while (emergency_flag == 1) {
        chrono::milliseconds duration(20);
        this_thread::sleep_for(duration);
    }
    
    m.lock();
    ActiveController ac(layerid,0,this_thread::get_id());
    controller.push_back(ac);
    
    activate(layerid);
    
    m.unlock();
    
}

void active_normal(RTCOP::Generated::LayerID layerid){
    thread t(active,layerid);
    t.detach();
    usleep(1000);
}

void active_normal_mu(RTCOP::Generated::LayerID layerid){
    thread t(active,layerid);
    t.detach();
    usleep(1000);
}

void active_break(RTCOP::Generated::LayerID layerid){
    thread t(active_emergency,layerid,2,layerid,true);
    t.detach();
    usleep(1000);
}

void active_break(RTCOP::Generated::LayerID layerid,RTCOP::Generated::LayerID target_layerid){
    thread t(active_emergency,layerid,2,target_layerid,true);
    t.detach();
    usleep(1000);
}

void active_suspend(RTCOP::Generated::LayerID layerid){
    thread t(active_emergency,layerid,1,layerid,true);
    t.detach();
    usleep(1000);
}

void active_suspend(RTCOP::Generated::LayerID layerid,RTCOP::Generated::LayerID target_layerid){
    thread t(active_emergency,layerid,1,target_layerid,true);
    t.detach();
    usleep(1000);
}


void active_suspend_until_deactive(RTCOP::Generated::LayerID layerid){
    thread t(active_emergency,layerid,1,layerid,false);
    t.detach();
    usleep(1000);
}


void active_suspend_until_deactive(RTCOP::Generated::LayerID layerid,RTCOP::Generated::LayerID target_layerid){
    thread t(active_emergency,layerid,1,target_layerid,false);
    t.detach();
    usleep(1000);
}

void deactive_suspend(RTCOP::Generated::LayerID layerid){
    thread t(deactive_emergency,layerid,layerid);
    t.detach();
    usleep(1000);
}

}