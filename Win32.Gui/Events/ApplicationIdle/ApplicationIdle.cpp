#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <chrono>
#include <string>
#include <Windows.h>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

HWND form = nullptr;
WNDPROC defWndProc = nullptr;

void OnApplicationIdle() {
  static int counter = 0;
  SendMessage(form, WM_SETTEXT, 0, (LPARAM)to_wstring(++counter).c_str());
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE) PostQuitMessage(0);
  if (message == WM_ENTERIDLE) OnApplicationIdle();
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = {0};
  while (message.message != WM_QUIT) {
    if (PeekMessage(&message, nullptr, 0, 0, PM_NOREMOVE)) {
      GetMessage(&message, nullptr, 0, 0);
      DispatchMessage(&message);
    } else {
      static high_resolution_clock::time_point lastIdleTime = high_resolution_clock::now();
      if (high_resolution_clock::now() - lastIdleTime >= 100ms) {
        OnApplicationIdle();
        lastIdleTime = high_resolution_clock::now();
      }
    }
  }
  return (int)message.wParam;
}
