#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

HWND window = nullptr;
HWND groupBox1 = nullptr;
HWND groupBox2 = nullptr;
HWND radioButton1 = nullptr;
HWND radioButton2 = nullptr;
HWND radioButton3 = nullptr;
HWND radioButton4 = nullptr;
HWND radioButton5 = nullptr;
HWND radioButton6 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"GroupBox and RadioButton example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 200, nullptr, nullptr, nullptr, nullptr);
  groupBox1 = CreateWindowEx(0, WC_BUTTON, L"Group 1", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 135, 140, window, nullptr, nullptr, nullptr);
  groupBox2 = CreateWindowEx(0, WC_BUTTON, L"Group 2", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 155, 10, 135, 140, window, nullptr, nullptr, nullptr);
  radioButton1 = CreateWindowEx(0, WC_BUTTON, L"radio 1", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 20, 104, 24, groupBox1, nullptr, nullptr, nullptr);
  radioButton2 = CreateWindowEx(0, WC_BUTTON, L"radio 2", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 50, 104, 24, groupBox1, nullptr, nullptr, nullptr);
  radioButton3 = CreateWindowEx(0, WC_BUTTON, L"radio 3", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 80, 104, 24, groupBox1, nullptr, nullptr, nullptr);
  radioButton4 = CreateWindowEx(0, WC_BUTTON, L"radio 4", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 20, 104, 24, groupBox2, nullptr, nullptr, nullptr);
  radioButton5 = CreateWindowEx(0, WC_BUTTON, L"radio 5", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 50, 104, 24, groupBox2, nullptr, nullptr, nullptr);
  radioButton6 = CreateWindowEx(0, WC_BUTTON, L"radio 6", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 80, 104, 24, groupBox2, nullptr, nullptr, nullptr);
  
  SendMessage(radioButton1, BM_SETCHECK, BST_CHECKED, 0);
  SendMessage(radioButton5, BM_SETCHECK, BST_CHECKED, 0);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
  
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
