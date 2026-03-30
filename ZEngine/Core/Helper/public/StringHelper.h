#pragma once
#include <string>
#include <Windows.h>
#include <locale.h>

namespace ZEngine {
	namespace StringHelper {
        static void StringToWString(const std::string& str, std::wstring& OutWS) {
            if (str.empty()) return;

            // 1. 计算转换后所需的宽字符长度
            int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);

            // 2. 分配缓冲区并执行转换
			OutWS.resize(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &OutWS[0], size_needed);


        }

        static void wstring_to_utf8(const std::wstring& wstr, std::string &OutStr)
        {
            if (wstr.empty()) return;
			
			int size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), NULL, 0, NULL, NULL);
			OutStr.resize(size, 0);
			WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &OutStr[0], size, NULL, NULL);
        }
	}
}