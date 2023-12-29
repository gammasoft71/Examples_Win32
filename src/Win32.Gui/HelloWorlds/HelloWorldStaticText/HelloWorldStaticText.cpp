#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND window = nullptr;
HWND staticText = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnWindowResize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  LRESULT result = CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  RECT windowRect, labelRect;
  GetClientRect(window, &windowRect);
  GetClientRect(staticText, &labelRect);
  SetWindowPos(staticText, HWND_TOP, (windowRect.right - windowRect.left - labelRect.right - labelRect.left) / 2 + windowRect.left, (windowRect.bottom - windowRect.top - labelRect.bottom - labelRect.top) / 2 + windowRect.top, 0, 0, SWP_NOSIZE);
  return result;
}

LRESULT ChangeStaticTextColor(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  LRESULT result = CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  SetTextColor((HDC)wParam, RGB(0X00, 0X80, 0X00));
  return result;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_SIZE && hwnd == window) return OnWindowResize(hwnd, message, wParam, lParam);
  if (message == WM_CTLCOLORSTATIC && (HWND)lParam == staticText) return ChangeStaticTextColor(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"Hello world (StaticText)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 340, nullptr, nullptr, nullptr, nullptr);
  staticText = CreateWindowEx(0, WC_STATIC, L"Hello, World!", WS_CHILD | WS_VISIBLE, 5, 100, 280, 52, window, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(staticText, WM_SETFONT, (WPARAM)CreateFont(int(-34 / 72.0f * GetDeviceCaps(GetDC(window), LOGPIXELSY)), 0, 0, 0, FW_BOLD, true, false, false, 0, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial"), true);

  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
