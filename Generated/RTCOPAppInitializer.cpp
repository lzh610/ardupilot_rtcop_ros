#include "./Generated/RTCOPAppInitializer.h"
#include "RTCOP/Core/RTCOPManager.h"
#include "RTCOP/Core/LayerdObjectInitializer.h"
#include "RTCOP/Core/LayerActivater.h"
#include "./Generated/BaseLayer.h"
#include "./Generated/English.h"
#include "./Generated/Japanese.h"
#include "./Generated/Ground.h"
#include "./Generated/Flight.h"

namespace RTCOP {
namespace Generated {

RTCOPAppInitializer::RTCOPAppInitializer()
{
}

RTCOPAppInitializer::~RTCOPAppInitializer()
{
}

Core::RTCOPManager* RTCOPAppInitializer::InitializeRTCOPManager()
{
	int numOfLayers = 5;
	int numOfClasses = 1;
	int* numOfMethods = new int[numOfClasses] {3};
	return new Core::RTCOPManager(numOfLayers, numOfClasses, numOfMethods);
}

Core::LayerdObjectInitializer* RTCOPAppInitializer::InitializeLayerdObjectInitializer(Core::RTCOPManager* manager)
{
	return new Core::LayerdObjectInitializer(manager);
}

Core::LayerActivater* RTCOPAppInitializer::InitializeLayerActivater(Core::RTCOPManager* manager)
{
	return new Core::LayerActivater(manager);
}

void RTCOPAppInitializer::RegisterLayers(Core::RTCOPManager* manager)
{
	int numOfBaseClasses = manager->GetNumOfBaseClasses();
	int* numOfBaseMethods = manager->GetNumOfBaseMethods();
	manager->RegisterLayer(new BaseLayer(0, "baselayer", numOfBaseClasses, numOfBaseMethods));
	manager->RegisterLayer(new English(1, "English", numOfBaseClasses, numOfBaseMethods));
	manager->RegisterLayer(new Japanese(2, "Japanese", numOfBaseClasses, numOfBaseMethods));
	manager->RegisterLayer(new Ground(3, "Ground", numOfBaseClasses, numOfBaseMethods));
	manager->RegisterLayer(new Flight(4, "Flight", numOfBaseClasses, numOfBaseMethods));
}

void RTCOPAppInitializer::FirstLayerActivation(Core::LayerActivater* activater)
{
	activater->ActivateLayer(0);
}

Core::Initializer* _GetDefaultInitializer_()
{
	return new RTCOPAppInitializer();
}

} // namespace Generated {}
} // namespace RTCOP {}
