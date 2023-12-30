#include <iostream>
#include <string>
#include <Windows.h>

int main() {
  STARTUPINFO startupInfo;
  PROCESS_INFORMATION processInfo;

  ZeroMemory(&startupInfo, sizeof(startupInfo));
  startupInfo.cb = sizeof(startupInfo);
  ZeroMemory(&processInfo, sizeof(processInfo));

  std::wstring name = L"explorer c:\\Users\\yves\\Desktop\\sample.txt";
  if (CreateProcess(nullptr, (wchar_t*)name.c_str(), nullptr, nullptr, false, 0, nullptr, nullptr, &startupInfo, &processInfo) == 0) {
    std::cout << "CreateProcess failed " << GetLastError() << std::endl;
    return 1;
  }

  /*
  if (!CreateProcess(L"cmd /c dir", nullptr, nullptr, nullptr, false, 0, nullptr, nullptr, &startupInfo, &processInfo)) {
    std::cout << "CreateProcess failed " << GetLastError() << std::endl;
    return 1;
  }*/
  WaitForSingleObject(processInfo.hProcess, INFINITE);
  return 0;
}
