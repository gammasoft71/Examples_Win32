#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND comboBox1 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"ComboBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  comboBox1 = CreateWindowEx(0, WC_COMBOBOX, L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 10, 10, 121, 21, form, nullptr, nullptr, nullptr);
 
  SendMessage(comboBox1, CB_ADDSTRING, 0, (LPARAM)L"item1");
  SendMessage(comboBox1, CB_ADDSTRING, 0, (LPARAM)L"item2");
  SendMessage(comboBox1, CB_ADDSTRING, 0, (LPARAM)L"item3");
  SendMessage(comboBox1, CB_SETCURSEL, 1, 0);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return (int)message.wParam;
}
