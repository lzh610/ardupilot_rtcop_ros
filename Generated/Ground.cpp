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
#include "./Generated/Flight.h"
#include "./Generated/Ground.h"

namespace RTCOP {
namespace Generated {

Ground* Ground::GetInstance()
{
	return (Ground*)RTCOP::Framework::Instance->GetRTCOPManager()->GetLayer((int)LayerID::Ground);
}

Ground::Ground(const int id, const char* const name, int numOfBaseClasses, int* numOfBaseMethods)
	:RTCOP::Core::Layer(id, name, numOfBaseClasses, numOfBaseMethods)
{
	int size0 = sizeof(volatile void*) * numOfBaseMethods[0];
	volatile void** virtualFunctionTable0	 = DependentCode::baselayer::Hello::GetVirtualFunctionTable(this);
	std::memcpy(_Private->_VirtualFunctionTables[0], virtualFunctionTable0, size0);
	_Private->_VirtualFunctionTables[0][1] = 0;
	_Private->_VirtualFunctionTables[0][2] = 0;
}

Ground::~Ground()
{
}

void* Ground::InitializeLayerdObject(void* obj, int classID)
{
	int layerID = _Private->_ID;
	if (classID == 0)
	{
		::Ground::Hello* layerdObject = reinterpret_cast<::Ground::Hello*>(obj);
		layerdObject->_Private->_PartialClassMembers[layerID] = new ::Ground::Hello::PartialClassMembers();
		layerdObject->_Private->_PartialClassMembers[layerID]->_Layer = this;
		volatile void* vfp = DependentCode::GetLayerdObjectFinalizer(layerdObject);
		layerdObject->_Private->_PartialClassMembers[layerID]->_Finalizer = vfp;
		layerdObject->_RTCOP_InitializePartialClass();
	}
	return obj;
}

void Ground::_RTCOP_OnActivating()
{
}

void Ground::_RTCOP_OnActivated()
{
}

void Ground::_RTCOP_OnDeactivating()
{
}

void Ground::_RTCOP_OnDeactivated()
{
}

} // namespace Generated {}
} // namespace RTCOP {}

using namespace gnc ;
namespace Ground
{
void Hello::Print ()
{
	Hello::PartialClassMembers* layer_members = (Hello::PartialClassMembers*)_Private->_PartialClassMembers[3];
	volatile void* _RTCOP_proceedaddr = RTCOP::Framework::Instance->GetRTCOPManager()->GetLayer(3)->GetVirtualFunctionTableForProceeding(0)[0];
	auto proceed = [this, _RTCOP_proceedaddr]() { RTCOP::Generated::DependentCode::baselayer::Hello::ExecuteProceed_Print(this, _RTCOP_proceedaddr); };
	ROS_INFO_STREAM ( "Ground Mode" ) ;

}


}


namespace Ground{

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

