#ifndef __RTCOP_GENERATED_FLIGHT__
#define __RTCOP_GENERATED_FLIGHT__

#include "RTCOP/Core/Layer.h"
#include "RTCOP/Core/LayerdObject.h"
#include "RTCOP/Core/PartialClassMembers.h"


#include "./Generated/BaseLayer.h"

namespace RTCOP {
namespace Generated {

class Flight : public RTCOP::Core::Layer
{
public:
	static Flight* GetInstance();
	explicit Flight(const int id, const char* const name, int numOfBaseClasses, int* numOfBaseMethods);
	virtual ~Flight() override;
protected:
	virtual void* InitializeLayerdObject(void* obj, int classID) override;
	virtual void _RTCOP_OnActivating() override;
	virtual void _RTCOP_OnActivated() override;
	virtual void _RTCOP_OnDeactivating() override;
	virtual void _RTCOP_OnDeactivated() override;
};

} // namespace Generated {}
} // namespace RTCOP {}

namespace Flight
{
class Hello : public RTCOP::Core::LayerdObject<baselayer::Hello>
{
public:
	friend RTCOP::Generated::Flight;
	class PartialClassMembers : public RTCOP::Core::PartialClassMembers
	{
	public:
	};
	Hello ();
private:
	void _RTCOP_InitializePartialClass();
	void _RTCOP_FinalizePartialClass();
	public:
	virtual void Print ();

};
void OnActivating ();
void OnActivated ();
void OnDeactivating ();
void OnDeactivated ();

}


#endif
