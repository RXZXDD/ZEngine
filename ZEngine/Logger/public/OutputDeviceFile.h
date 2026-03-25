#include "Core/Core.h"
#include "OutputDevice.h"

#include <fstream>


namespace ZEngine
{
	class ZOutputDeviceFile : public ZOutputDevice
	{
		//2026_10_29_15_19.log
		std::wstring FileName;

		//TODO filepath
		std::wstring FilePath;

		std::wofstream FileStream;

		std::wstring cache;

		const std::wstring LogFileNameSuffix = L".log";

		const int MaxCacheSize = 1024 * 4;
		const int MaxCacheChars = MaxCacheSize / sizeof(wchar_t);

	public:
		ZOutputDeviceFile();
		~ZOutputDeviceFile();
		virtual void Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level) override;

		void Flush();
		
	};
}