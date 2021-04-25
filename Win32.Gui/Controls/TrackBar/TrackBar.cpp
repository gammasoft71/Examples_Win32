#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;

HWND window = nullptr;
HWND trackBar = nullptr;
HWND progressBar = nullptr;
HWND staticText = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnTrackBarChanged(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  LRESULT value = SendMessage(trackBar, TBM_GETPOS, 0, 0);
  SendMessage(progressBar, PBM_SETPOS, value, 0);
  SendMessage(staticText, WM_SETTEXT, 0, (LPARAM)to_wstring(value).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_HSCROLL && hwnd == window && (HWND)lParam == trackBar) return OnTrackBarChanged(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"TrackBar example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  trackBar = CreateWindowEx(0, TRACKBAR_CLASS, nullptr, WS_CHILD | TBS_HORZ | TBS_NOTICKS | WS_VISIBLE, 20, 50, 200, 23, window, nullptr, nullptr, nullptr);
  progressBar = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_SMOOTH | WS_VISIBLE, 20, 100, 200, 23, window, nullptr, nullptr, nullptr);
  staticText = CreateWindowEx(0, WC_STATIC, L"100", WS_CHILD | WS_VISIBLE, 20, 150, 100, 23, window, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(trackBar, TBM_SETRANGEMIN, 1, 0);
  SendMessage(trackBar, TBM_SETRANGEMAX, 1, 200);
  SendMessage(trackBar, TBM_SETPOS, 1, 100);
  SendMessage(progressBar, PBM_SETRANGE32, 0, 200);
  SendMessage(progressBar, PBM_SETPOS, 100, 0);

  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
