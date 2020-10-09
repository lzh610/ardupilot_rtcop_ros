#include "./Generated/API.h"
#include "./Generated/Layer_Private.h"
#include "./Generated/LayerdObject_Private.h"
#include "RTCOP/Framework.h"
#include "RTCOP/Core/RTCOPManager.h"
#include "./Generated/DependentCode.h"
#include <iostream>
#include <cstring>

#include "ros/ros.h"
#include "stdio.h"
#include "gnc_functions.h"

#include "./Generated/BaseLayer.h"
#include "./Generated/English.h"
#include "./Generated/Japanese.h"
#include "./Generated/Ground.h"
#include "./Generated/Flight.h"

namespace RTCOP {
namespace Generated {

Flight* Flight::GetInstance()
{
	return (Flight*)RTCOP::Framework::Instance->GetRTCOPManager()->GetLayer((int)LayerID::Flight);
}

Flight::Flight(const int id, const char* const name, int numOfBaseClasses, int* numOfBaseMethods)
	:RTCOP::Core::Layer(id, name, numOfBaseClasses, numOfBaseMethods)
{
	int size0 = sizeof(volatile void*) * numOfBaseMethods[0];
	volatile void** virtualFunctionTable0	 = DependentCode::baselayer::Hello::GetVirtualFunctionTable(this);
	std::memcpy(_Private->_VirtualFunctionTables[0], virtualFunctionTable0, size0);
	_Private->_VirtualFunctionTables[0][1] = 0;
	_Private->_VirtualFunctionTables[0][2] = 0;
}

Flight::~Flight()
{
}

void* Flight::InitializeLayerdObject(void* obj, int classID)
{
	int layerID = _Private->_ID;
	if (classID == 0)
	{
		::Flight::Hello* layerdObject = reinterpret_cast<::Flight::Hello*>(obj);
		layerdObject->_Private->_PartialClassMembers[layerID] = new ::Flight::Hello::PartialClassMembers();
		layerdObject->_Private->_PartialClassMembers[layerID]->_Layer = this;
		volatile void* vfp = DependentCode::GetLayerdObjectFinalizer(layerdObject);
		layerdObject->_Private->_PartialClassMembers[layerID]->_Finalizer = vfp;
		layerdObject->_RTCOP_InitializePartialClass();
	}
	return obj;
}

void Flight::_RTCOP_OnActivating()
{
	::Flight::OnActivating();
}

void Flight::_RTCOP_OnActivated()
{
	::Flight::OnActivated();
}

void Flight::_RTCOP_OnDeactivating()
{
	::Flight::OnDeactivating();
}

void Flight::_RTCOP_OnDeactivated()
{
	::Flight::OnDeactivated();
}

} // namespace Generated {}
} // namespace RTCOP {}

using namespace gnc ;
namespace Flight
{
void Hello::Print ()
{
	Hello::PartialClassMembers* layer_members = (Hello::PartialClassMembers*)_Private->_PartialClassMembers[4];
	volatile void* _RTCOP_proceedaddr = RTCOP::Framework::Instance->GetRTCOPManager()->GetLayer(4)->GetVirtualFunctionTableForProceeding(0)[0];
	auto proceed = [this, _RTCOP_proceedaddr]() { RTCOP::Generated::DependentCode::baselayer::Hello::ExecuteProceed_Print(this, _RTCOP_proceedaddr); };
	ROS_INFO_STREAM ( "Flight Mode" ) ;

}

void OnActivating ()
{
	ros :: Rate rate ( 1 ) ;
	takeoff ( 1 ) ;
	nextWayPoint . x = 0 ;
	nextWayPoint . y = 0 ;
	nextWayPoint . z = 5 ;
	nextWayPoint . psi = 0 ;
	waypointlist . push_back ( nextWayPoint ) ;
	ROS_INFO_STREAM ( "taking off" ) ;
	ros :: spinOnce ( ) ;
	rate . sleep ( ) ;
	set_destination ( waypointlist [ 0 ] . x , waypointlist [ 0 ] . y , waypointlist [ 0 ] . z , waypointlist [ 0 ] . psi ) ;
	}

void OnActivated ()
{
	ROS_INFO_STREAM ( "Layer1::OnActivatedの実行\n" ) ;
	}

void OnDeactivating ()
{
	ROS_INFO_STREAM ( "Layer1::OnDeactivatingの実行\n" ) ;
	}

void OnDeactivated ()
{
	ROS_INFO_STREAM ( "Layer1::OnDeactivatedの実行\n" ) ;
	}


}


namespace Flight{

Hello::Hello()
	: RTCOP::Core::LayerdObject<baselayer::Hello>()
{
}

void Hello::_RTCOP_InitializePartialClass()
{
}

void Hello::_RTCOP_FinalizePartialClass()
{
}


}

