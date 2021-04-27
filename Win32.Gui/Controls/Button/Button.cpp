#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND button1 = nullptr;
HWND button2 = nullptr;
HWND staticText1 = nullptr;
HWND staticText2 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButton1Click(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static auto buttonClicked = 0;
  auto result = L"button1 clicked "s + to_wstring(++buttonClicked) + L" times"s;
  SendMessage(staticText1, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(result.c_str()));
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButton2Click(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static auto buttonClicked = 0;
  auto result = L"button2 clicked "s + to_wstring(++buttonClicked) + L" times"s;
  SendMessage(staticText2, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(result.c_str()));
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button1) return OnButton1Click(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button2) return OnButton2Click(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"Button example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"button1", WS_CHILD | WS_VISIBLE, 50, 50, 75, 25, window, nullptr, nullptr, nullptr);
  button2 = CreateWindowEx(0, WC_BUTTON, L"button2", WS_CHILD | WS_VISIBLE, 50, 100, 200, 75, window, nullptr, nullptr, nullptr);
  staticText1 = CreateWindowEx(0, WC_STATIC, L"button1 clicked 0 times", WS_CHILD | WS_VISIBLE, 50, 200, 200, 23, window, nullptr, nullptr, nullptr);
  staticText2 = CreateWindowEx(0, WC_STATIC, L"button2 clicked 0 times", WS_CHILD | WS_VISIBLE, 50, 230, 200, 23, window, nullptr, nullptr, nullptr);
  
  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return static_cast<int>(message.wParam);
}
