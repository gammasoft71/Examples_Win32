#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <chrono>
#include <thread>
#include <string>
#include <Windows.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace std::chrono_literals;

HWND window = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

void OnApplicationIdle() {
  static int counter = 0;
  SendMessage(window, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(to_wstring(++counter).c_str()));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  
  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (message.message != WM_QUIT) {
    if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
      DispatchMessage(&message);
    else {
      static auto lastIdleTime = high_resolution_clock::now();
      if (high_resolution_clock::now() - lastIdleTime >= 100ms) {
        OnApplicationIdle();
        lastIdleTime = high_resolution_clock::now();
      }
      sleep_for(20ms);
    }
  }
}
