#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND label = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_CLOSE: PostQuitMessage(0); return 0;
  case WM_ERASEBKGND: SetBkColor((HDC)wParam, GetBkColor(GetDC(hwnd))); return 0;
  case WM_CTLCOLORSTATIC: SetTextColor((HDC)wParam, RGB(0X00, 0X80, 0X00)); return 0;
  default: return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  }
}

int main(int argc, char* argv[]) {
  form = CreateWindowEx(0, WC_DIALOG, L"My first application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 330, nullptr, nullptr, nullptr, nullptr);
  label = CreateWindowEx(0, WC_STATIC, L"Hello, World!", WS_CHILD | WS_VISIBLE, 5, 100, 290, 100, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(form, WM_CTLCOLORSTATIC, (WPARAM)GetDC(label), (LPARAM)label);
  SendMessage(label, WM_SETFONT, (WPARAM)CreateFont(int(-34 / 72.0f * GetDeviceCaps(GetDC(form), LOGPIXELSY)), 0, 0, 0, FW_BOLD, true, false, false, 0, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial"), true);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
