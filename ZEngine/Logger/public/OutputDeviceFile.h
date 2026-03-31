#include "Core/Core.h"
#include "OutputDevice.h"

#include <fstream>


namespace ZEngine
{
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
		const int MaxCacheChars = MaxCacheSize / sizeof(wchar_t);

	public:
		ZOutputDeviceFile();
		~ZOutputDeviceFile();
		virtual void Log(std::string Line, const ZBaseLogger* logger, const LogLevel level) override;

		void Flush();
		
	};
}