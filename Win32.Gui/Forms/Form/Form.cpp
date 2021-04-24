#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND button = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form && MessageBox(form, L"Are you sure you want exit?", L"Close Form", MB_ICONQUESTION | MB_YESNO) == IDYES) PostQuitMessage(0);
  if (message == WM_COMMAND && (HWND)lParam == button) SendMessage(form, WM_CLOSE, 0, 0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"Form example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, nullptr, nullptr, nullptr, nullptr);
  button = CreateWindowEx(0, WC_BUTTON, L"Close", WS_CHILD | WS_VISIBLE, 10, 10, 75, 25, form, nullptr, nullptr, nullptr);
 
  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
