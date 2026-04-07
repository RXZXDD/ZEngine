#include "Core/Core.h"
#include "OutputDevice.h"
#include "Logger/public/LoggerMacro.h"


#include <fstream>


namespace ZEngine
{

	DECLARE_LOGGER_EXTERN(FileLogger)
	class ZOutputDeviceFile : public ZOutputDevice
	{
		//2026_10_29_15_19.log
		std::string FileName;

		//TODO filepath
		std::string FilePath;

		std::ofstream FileStream;

		std::string cache;

		const std::string LogFileNameSuffix = ".log";

		const int MaxCacheSize = 1024 * 4;
		const int MaxCacheChars = MaxCacheSize / sizeof(char);

	public:
		ZOutputDeviceFile();
		~ZOutputDeviceFile();
		virtual void Log(const ZLogRecord& Record) override;

		void Flush();
		
	};
}