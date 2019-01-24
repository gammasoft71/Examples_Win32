#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND groupBox1 = nullptr;
HWND groupBox2 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main(int argc, char* argv[]) {
  form = CreateWindowEx(0, WC_DIALOG, L"GroupBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 656, 521, nullptr, nullptr, nullptr, nullptr);
  groupBox1 = CreateWindowEx(0, WC_BUTTON, L"GroupBox 1", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 305, 460, form, nullptr, nullptr, nullptr);
  groupBox2 = CreateWindowEx(0, WC_BUTTON, L"", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 325, 10, 305, 460, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
