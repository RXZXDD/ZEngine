#include "GlobalCore.h"
#include "../public/OutputDeviceFile.h"
#include "Core/Helper/public/StringHelper.h"

#include <Windows.h>
#include <stdio.h>
#include <filesystem>


namespace ZEngine
{
	DEFINE_LOGGER(FileLogger)
	ZOutputDeviceFile::ZOutputDeviceFile()
	{
		namespace fs = std::filesystem;
		try {
			if (fs::create_directories("./Save")) {
				OutputDebugString(L"文件夹创建成功！\n");
			}
			else{ 
				OutputDebugString(L"文件夹已存在或无需创建。\n");
			}
		}
		catch (const fs::filesystem_error& e) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::string buf{ "mkdir faileds %s \n" };
			buf.replace(buf.find("%s"), 2, e.what());
			std::wstring wbuf;
			ZEngine::StringHelper::StringToWString(buf, wbuf);
			OutputDebugString(wbuf.c_str());
			

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::abort();
		}


		//TODO 拼接文件路径
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		char str[26];
		ctime_s(str, sizeof str, &now_c);
		std::string sstr(str, str + 26);
		std::replace(sstr.begin(), sstr.end(), ' ', '_');
		std::replace(sstr.begin(), sstr.end(), ':', '_');
		sstr = sstr.substr(0, sstr.size() - 2);
		

		FileName = sstr + LogFileNameSuffix;

		FilePath = "./Save/"+FileName;


		FileStream.open(FilePath, std::ios::out | std::ios::app);

		if (!FileStream.is_open()) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

			printf_s("failed to open %s\n", FilePath.c_str());

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::abort();
		}
		else {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf_s("log file created: %s\n", FilePath.c_str());
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		FileStream.close();

		cache.reserve(MaxCacheChars);
	}
	ZOutputDeviceFile::~ZOutputDeviceFile()
	{
		if (cache.size() > 0)
			Flush();

		if(FileStream.is_open())
			FileStream.close();
	}
	void ZEngine::ZOutputDeviceFile::Log(const ZLogRecord& Record)
	{
		const size_t LineSize = Record.msg.size();

		if (cache.size() + LineSize > MaxCacheChars) 
			Flush();
		cache.append(Record.msg);
	}
	void ZOutputDeviceFile::Flush()
	{
		ZLOG(FileLogger, Display, "flushing");
		FileStream.open(FilePath, std::ios::out | std::ios::app);

		if (!FileStream.is_open()) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

			printf_s("failed to open %s\n", FilePath.c_str());

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::abort();
		}
		else {
			FileStream.write(cache.data(), cache.size());
			cache.clear();
		}


		FileStream.close();
	}
}