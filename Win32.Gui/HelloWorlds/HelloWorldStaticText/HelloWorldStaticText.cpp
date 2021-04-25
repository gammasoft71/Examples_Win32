#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND window = nullptr;
HWND label = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window)
    PostQuitMessage(0);
  if (message == WM_SIZE && hwnd == window) {
    RECT windowRect, labelRect;
    GetClientRect(window, &windowRect);
    GetClientRect(label, &labelRect);
    SetWindowPos(label, HWND_TOP, (windowRect.right - windowRect.left - labelRect.right - labelRect.left) / 2 + windowRect.left, (windowRect.bottom - windowRect.top - labelRect.bottom - labelRect.top) / 2 + windowRect.top, 0, 0, SWP_NOSIZE);
  }
  if (message == WM_CTLCOLORSTATIC && (HWND)lParam == label) {
    CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
    SetTextColor((HDC)wParam, RGB(0X00, 0X80, 0X00));
    return 0;
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"Hello world (label)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 330, nullptr, nullptr, nullptr, nullptr);
  label = CreateWindowEx(0, WC_STATIC, L"Hello, World!", WS_CHILD | WS_VISIBLE | SS_SIMPLE, 5, 100, 280, 52, window, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(window, WM_CTLCOLORSTATIC, (WPARAM)GetDC(label), (LPARAM)label);
  SendMessage(label, WM_SETFONT, (WPARAM)CreateFont(int(-34 / 72.0f * GetDeviceCaps(GetDC(window), LOGPIXELSY)), 0, 0, 0, FW_BOLD, true, false, false, 0, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial"), true);

  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
