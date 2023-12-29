#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND buttonShowMessage = nullptr;
WNDPROC defWndProc = nullptr;

void AboutBox(const wstring& title, const wstring& name, const wstring& description, const wstring& version, const wstring& copyright) {
  static const auto lineSeparator = wstring(86, ' ');
  MessageBox(nullptr, (name + L"\n" + version + L"\n" + lineSeparator + L"\n" + copyright + L"\n" + description + L"\n" + lineSeparator).c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
}

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  AboutBox(L"About AboutBox", L"AboutBox", L"About dialog description.", L"1.0.0", L"Copyright © 2021 Gammasoft.\nAll rights reserved.");
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == buttonShowMessage) return OnButtonClick(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"AboutBox exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  buttonShowMessage = CreateWindowEx(0, WC_BUTTON, L"About...", WS_CHILD | WS_VISIBLE, 10, 10, 80, 25, window, nullptr, nullptr, nullptr);
  
  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
}
