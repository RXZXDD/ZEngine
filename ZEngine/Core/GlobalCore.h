
#include "Logger/public/OutputDeviceRedirector.h"
#include "Logger/public/LoggerMacro.h"



#define GLog ZEngine::ZOutputDeviceRedirector::Get()

DECLARE_LOGGER_EXTERN(Default)
DECLARE_LOGGER_EXTERN(Renderer)
DECLARE_LOGGER_EXTERN(RHI)
DECLARE_LOGGER_EXTERN(Shader)
