#ifndef __RTCOP_GENERATED_DEPENDENTCODE__
#define __RTCOP_GENERATED_DEPENDENTCODE__

namespace baselayer { class Hello; } 
namespace English { class Hello; } 
namespace Japanese { class Hello; } 
namespace Ground { class Hello; } 
namespace Flight { class Hello; } 

namespace RTCOP {
namespace Generated {

class BaseLayer;
class English;
class Japanese;
class Ground;
class Flight;

namespace DependentCode {

volatile void* GetLayerdObjectFinalizer(::English::Hello* obj);
volatile void* GetLayerdObjectFinalizer(::Japanese::Hello* obj);
volatile void* GetLayerdObjectFinalizer(::Ground::Hello* obj);
volatile void* GetLayerdObjectFinalizer(::Flight::Hello* obj);

namespace baselayer { namespace Hello { 
volatile void** GetVirtualFunctionTable(BaseLayer* layer);
volatile void** GetVirtualFunctionTable(English* layer);
volatile void** GetVirtualFunctionTable(Japanese* layer);
volatile void** GetVirtualFunctionTable(Ground* layer);
volatile void** GetVirtualFunctionTable(Flight* layer);

void ExecuteProceed_Print(void* layerdObject, volatile void* proceed);

}}


} // namespace DependentCode {}
} // namespace Generated {}
} // namespace RTCOP {}
#endif // !__RTCOP_GENERATED_DEPENDENTCODE__
