#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND panel1 = nullptr;
HWND panel2 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main(int argc, char* argv[]) {
  form = CreateWindowEx(0, WC_DIALOG, L"Panel example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 656, 521, nullptr, nullptr, nullptr, nullptr);
  panel1 = CreateWindowEx(0, WC_DIALOG, nullptr, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER, 10, 10, 305, 460, form, nullptr, nullptr, nullptr);
  panel2 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_DIALOG, nullptr, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 325, 10, 305, 460, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
