#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <string>
#include <Windows.h>

std::string to_string(const std::string& str) {
  return str;
}

std::string to_string(const std::wstring& wstr) {
  std::string str(wstr.size(), 0);
  std::wcstombs(&str[0], wstr.c_str(), wstr.size());
  return str;
}

std::wstring to_wstring(const std::string& str) {
  std::wstring wstr(str.size(), 0);
  std::mbstowcs(&wstr[0], str.c_str(), str.size());
  return wstr;
}

std::wstring to_wstring(const std::wstring& wstr) {
  return wstr;
}

int main() {
  WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), to_string("Hello, World1 !\n").c_str(), 16, nullptr, nullptr);
  WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), to_string(L"Hello, World2 !\n").c_str(), 16, nullptr, nullptr);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), to_wstring("Hello, World3 !\n").c_str(), 16, nullptr, nullptr);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), to_wstring(L"Hello, World4 !\n").c_str(), 16, nullptr, nullptr);
}