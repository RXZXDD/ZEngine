
#include "Logger/public/OutputDeviceRedirector.h"
#include "Logger/public/LoggerMacro.h"
//#include "RHI/public/RHI.h"


#define GLog ZEngine::ZOutputDeviceRedirector::Get()

DECLARE_LOGGER_EXTERN(Default)
DECLARE_LOGGER_EXTERN(RHI)
DECLARE_LOGGER_EXTERN(Shader)
