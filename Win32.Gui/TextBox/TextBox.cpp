#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form;
HWND textBox1;
HWND textBox2;

WNDPROC defWndProc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main(int argc, char* argv[]) {
  form = CreateWindowEx(0, WC_DIALOG, L"TextBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  textBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"textBox1", WS_CHILD | WS_VISIBLE, 10, 10, 100, 23, form, nullptr, nullptr, nullptr);
  textBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"textBox2", WS_CHILD | WS_VISIBLE, 10, 50, 100, 23, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  ShowWindow(form, SW_SHOW);

  MSG message;
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return (int)message.wParam;
}
