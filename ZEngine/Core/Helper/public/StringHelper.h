#pragma once
#include <string>
#include <Windows.h>

namespace ZEngine {
	namespace StringHelper {
        void StringToWString(const std::string& str, std::wstring& OutWS) {
            if (str.empty()) return;

            // 1. 计算转换后所需的宽字符长度
            int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);

            // 2. 分配缓冲区并执行转换
			OutWS.resize(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &OutWS[0], size_needed);


        }
	}
}