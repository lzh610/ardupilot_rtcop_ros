#ifndef __RTCOP_GENERATED_GROUND__
#define __RTCOP_GENERATED_GROUND__

#include "RTCOP/Core/Layer.h"
#include "RTCOP/Core/LayerdObject.h"
#include "RTCOP/Core/PartialClassMembers.h"


#include "./Generated/BaseLayer.h"

namespace RTCOP {
namespace Generated {

class Ground : public RTCOP::Core::Layer
{
public:
	static Ground* GetInstance();
	explicit Ground(const int id, const char* const name, int numOfBaseClasses, int* numOfBaseMethods);
	virtual ~Ground() override;
protected:
	virtual void* InitializeLayerdObject(void* obj, int classID) override;
	virtual void _RTCOP_OnActivating() override;
	virtual void _RTCOP_OnActivated() override;
	virtual void _RTCOP_OnDeactivating() override;
	virtual void _RTCOP_OnDeactivated() override;
};

} // namespace Generated {}
} // namespace RTCOP {}

namespace Ground
{
class Hello : public RTCOP::Core::LayerdObject<baselayer::Hello>
{
public:
	friend RTCOP::Generated::Ground;
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

}


#endif
