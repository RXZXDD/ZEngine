#include "../public/OutputDeviceFile.h"

#include <chrono>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <filesystem>


namespace ZEngine
{
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
			OutputDebugString(L"mkdir faileds \n");
			

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::abort();
		}


		//TODO 拼接文件路径
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		char str[26];
		ctime_s(str, sizeof str, &now_c);
		std::wstring wstr(str, str + 26);
		std::replace(wstr.begin(), wstr.end(), L' ', L'_');
		std::replace(wstr.begin(), wstr.end(), L':', L'_');
		wstr = wstr.substr(0, wstr.size() - 2);
		

		FileName = wstr + LogFileNameSuffix;

		FilePath = L"./Save/"+FileName;


		FileStream.open(FilePath, std::ios::out | std::ios::app);

		if (!FileStream.is_open()) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

			wprintf_s(L"failed to open %s\n", FilePath.c_str());

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::abort();
		}
		else {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			wprintf_s(L"log file created: %s\n", FilePath.c_str());
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
	void ZEngine::ZOutputDeviceFile::Log(std::wstring Line, const ZBaseLogger* logger, const LogLevel level)
	{
		const size_t LineSize = Line.size();

		if (cache.size() + LineSize > MaxCacheChars) 
			Flush();
		cache.append(Line);

	}
	void ZOutputDeviceFile::Flush()
	{
		FileStream.open(FilePath, std::ios::out | std::ios::app);

		if (!FileStream.is_open()) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

			wprintf_s(L"failed to open %s\n", FilePath.c_str());

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