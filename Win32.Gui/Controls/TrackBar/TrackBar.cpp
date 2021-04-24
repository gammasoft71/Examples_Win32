#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;

HWND form = nullptr;
HWND trackBar = nullptr;
HWND progressBar = nullptr;
HWND label = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  if (message == WM_HSCROLL && hwnd == form && (HWND)lParam == trackBar) {
    SendMessage(progressBar, PBM_SETPOS, SendMessage(trackBar, TBM_GETPOS, 0, 0), 0);
    SendMessage(label, WM_SETTEXT, 0, (LPARAM)to_wstring(SendMessage(trackBar, TBM_GETPOS, 0, 0)).c_str());
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"TrackBar example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  trackBar = CreateWindowEx(0, TRACKBAR_CLASS, nullptr, WS_CHILD | TBS_HORZ | TBS_NOTICKS | WS_VISIBLE, 20, 50, 200, 23, form, nullptr, nullptr, nullptr);
  progressBar = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_SMOOTH | WS_VISIBLE, 20, 100, 200, 23, form, nullptr, nullptr, nullptr);
  label = CreateWindowEx(0, WC_STATIC, L"100", WS_CHILD | WS_VISIBLE, 20, 150, 100, 23, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(trackBar, TBM_SETRANGEMIN, 1, 0);
  SendMessage(trackBar, TBM_SETRANGEMAX, 1, 200);
  SendMessage(trackBar, TBM_SETPOS, 1, 100);
  SendMessage(progressBar, PBM_SETRANGE32, 0, 200);
  SendMessage(progressBar, PBM_SETPOS, 100, 0);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
