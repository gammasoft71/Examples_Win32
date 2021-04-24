#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND radioButton1 = nullptr;
HWND radioButton2 = nullptr;
HWND radioButton3 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"RadioButton example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  radioButton1 = CreateWindowEx(0, WC_BUTTON, L"radioButton 1", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 30, 30, 104, 24, form, nullptr, nullptr, nullptr);
  radioButton2 = CreateWindowEx(0, WC_BUTTON, L"radioButton 2", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 30, 60, 104, 24, form, nullptr, nullptr, nullptr);
  radioButton3 = CreateWindowEx(0, WC_BUTTON, L"radioButton 3", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 30, 90, 104, 24, form, nullptr, nullptr, nullptr);
  
  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(radioButton1, BM_SETCHECK, BST_CHECKED, 0);
  SendMessage(radioButton2, BM_SETCHECK, BST_UNCHECKED, 0);
  SendMessage(radioButton3, BM_SETCHECK, BST_UNCHECKED, 0);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
