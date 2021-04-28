#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <iomanip>
#include <sstream>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;

HWND window = nullptr;
HWND staticText = nullptr;
HWND button = nullptr;
UINT_PTR timer = 0;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

void CALLBACK OnTimerTick(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD time) {
  if (idEvent == timer) {
    static auto counter = 0;
    wstringstream stream;
    stream << fixed << setprecision(1) << static_cast<double>(++counter) / 10;
    SendMessage(staticText, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(stream.str().c_str()));
  }
}

LRESULT ChangeStaticTextColor(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto result = CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  SetTextColor(reinterpret_cast<HDC>(wParam), RGB(30, 144, 255));
  return result;
}

LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static auto enableTimer = false;
  enableTimer = !enableTimer;
  SendMessage(button, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(enableTimer ? L"Stop" : L"Start"));
  if (enableTimer) timer = SetTimer(nullptr, 0, 100, OnTimerTick);
  else KillTimer(nullptr, timer);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && reinterpret_cast<HWND>(lParam) == button) return OnButtonClick(hwnd, message, wParam, lParam);
  if (message == WM_CTLCOLORSTATIC && reinterpret_cast<HWND>(lParam) == staticText) return ChangeStaticTextColor(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"Timer example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 246, 176, nullptr, nullptr, nullptr, nullptr);
  staticText = CreateWindowEx(0, WC_STATIC, L"0.0", WS_CHILD | WS_VISIBLE, 10, 10, 210, 70, window, nullptr, nullptr, nullptr);
  button = CreateWindowEx(0, WC_BUTTON, L"Start", WS_CHILD | WS_VISIBLE, 10, 100, 75, 25, window, nullptr, nullptr, nullptr);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  SendMessage(staticText, WM_SETFONT, reinterpret_cast<WPARAM>(CreateFont(static_cast<int>(-48 / 72.0f * GetDeviceCaps(GetDC(window), LOGPIXELSY)), 0, 0, 0, FW_NORMAL, true, false, false, 0, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial")), true);
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
}
