#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <cstdint>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;

HWND form = nullptr;
HWND labelCompany = nullptr;
HWND labelProduct = nullptr;
HWND labelVersion = nullptr;
HWND labelCompanyName = nullptr;
HWND labelProductName = nullptr;
HWND labelProductVersion = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main(int argc, char* argv[]) {
  wstring currentModuleName(MAX_PATH, 0);
  GetModuleFileName(nullptr, (LPWSTR)currentModuleName.c_str(), currentModuleName.length());

  int32_t versionHandle = 0;
  int32_t versionSize = GetFileVersionInfoSize(currentModuleName.c_str(), (LPDWORD)&versionHandle);
  wstring versionData(versionSize, 0);
  GetFileVersionInfo(currentModuleName.c_str(), versionHandle, versionSize, (LPVOID)versionData.c_str());
  
  wchar_t* value;
  int32_t valueLength = 0;
  VerQueryValue((LPVOID)versionData.c_str(), L"\\StringFileInfo\\000004b0\\CompanyName", (LPVOID*)&value, (PUINT)&valueLength);
  wstring valueCompanyName(value);
  VerQueryValue((LPVOID)versionData.c_str(), L"\\StringFileInfo\\000004b0\\ProductName", (LPVOID*)&value, (PUINT)&valueLength);
  wstring valueProductName(value);
  VerQueryValue((LPVOID)versionData.c_str(), L"\\StringFileInfo\\000004b0\\ProductVersion", (LPVOID*)&value, (PUINT)&valueLength);
  wstring valueProductVersion(value);

  form = CreateWindowEx(0, WC_DIALOG, L"Form with version info", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 140, nullptr, nullptr, nullptr, nullptr);
  labelCompany = CreateWindowEx(0, WC_STATIC, L"Company name", WS_CHILD | WS_VISIBLE, 10, 12, 105, 23, form, nullptr, nullptr, nullptr);
  labelProduct = CreateWindowEx(0, WC_STATIC, L"Product name", WS_CHILD | WS_VISIBLE, 10, 42, 105, 23, form, nullptr, nullptr, nullptr);
  labelVersion = CreateWindowEx(0, WC_STATIC, L"Product version", WS_CHILD | WS_VISIBLE, 10, 72, 105, 23, form, nullptr, nullptr, nullptr);
  labelCompanyName = CreateWindowEx(WS_EX_CLIENTEDGE, WC_STATIC, valueCompanyName.c_str(), WS_CHILD | WS_VISIBLE, 120, 10, 170, 23, form, nullptr, nullptr, nullptr);
  labelProductName = CreateWindowEx(WS_EX_CLIENTEDGE, WC_STATIC, valueProductName.c_str(), WS_CHILD | WS_VISIBLE, 120, 40, 170, 23, form, nullptr, nullptr, nullptr);
  labelProductVersion = CreateWindowEx(WS_EX_CLIENTEDGE, WC_STATIC, valueProductVersion.c_str(), WS_CHILD | WS_VISIBLE, 120, 70, 170, 23, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
