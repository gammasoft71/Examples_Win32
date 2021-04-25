#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND window = nullptr;
HWND progressBar1 = nullptr;
HWND progressBar2 = nullptr;
HWND progressBar3 = nullptr;
HWND progressBar4 = nullptr;
HWND progressBar5 = nullptr;
UINT_PTR timer = 0;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

void CALLBACK OnTimerTick(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD time) {
  static int position = 0;
  position = position < 140 ? position + 1 : 0;
  SendMessage(progressBar4, PBM_SETPOS,  position, 0);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"ProgressBar example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  progressBar1 = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_SMOOTH | WS_VISIBLE, 50, 50, 200, 23, window, nullptr, nullptr, nullptr);
  progressBar2 = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_SMOOTH | WS_VISIBLE, 50, 80, 200, 23, window, nullptr, nullptr, nullptr);
  progressBar3 = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_SMOOTH | WS_VISIBLE, 50, 110, 200, 23, window, nullptr, nullptr, nullptr);
  progressBar4 = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_SMOOTH | WS_VISIBLE, 50, 140, 200, 23, window, nullptr, nullptr, nullptr);
  progressBar5 = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | PBS_MARQUEE | WS_VISIBLE, 50, 170, 200, 23, window, nullptr, nullptr, nullptr);
  timer = SetTimer(nullptr, 0, 50, OnTimerTick);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(progressBar2, PBM_SETPOS, 50, 0);
  SendMessage(progressBar3, PBM_SETRANGE32, 0, 300);
  SendMessage(progressBar3, PBM_SETPOS, 300, 0);
  SendMessage(progressBar4, PBM_SETRANGE32, 0, 140);
  SendMessage(progressBar5, PBM_SETMARQUEE, 1, 100);

  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
