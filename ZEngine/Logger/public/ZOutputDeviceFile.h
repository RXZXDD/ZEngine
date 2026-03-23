#include "Core/Core.h"
#include "ZOutputDevice.h"

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
		virtual void Log(std::wstring Line) override;

		void Flush();
		
	};
}