#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND checkBox1 = nullptr;
HWND checkBox2 = nullptr;
HWND checkBox3 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"CheckBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  checkBox1 = CreateWindowEx(0, WC_BUTTON, L"Checked", WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 30, 30, 104, 24, form, nullptr, nullptr, nullptr);
  checkBox2 = CreateWindowEx(0, WC_BUTTON, L"Unchecked", WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 30, 60, 104, 24, form, nullptr, nullptr, nullptr);
  checkBox3 = CreateWindowEx(0, WC_BUTTON, L"Indeterminate", WS_CHILD | BS_AUTO3STATE | WS_VISIBLE, 30, 90, 104, 24, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(checkBox1, BM_SETCHECK, BST_CHECKED, 0);
  SendMessage(checkBox2, BM_SETCHECK, BST_UNCHECKED, 0);
  SendMessage(checkBox3, BM_SETCHECK, BST_INDETERMINATE, 0);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
