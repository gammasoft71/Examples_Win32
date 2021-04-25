#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>
#include <initializer_list>

HWND window = nullptr;
HWND comboBox1 = nullptr;
HWND comboBox2 = nullptr;
HWND comboBox3 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnComboBoxChange(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static LRESULT selected_index = -1;
  if (selected_index != SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0)) {
    selected_index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
    SendMessage(comboBox1, CB_SETCURSEL, selected_index, 0);
    SendMessage(comboBox2, CB_SETCURSEL, selected_index, 0);
    SendMessage(comboBox3, CB_SETCURSEL, selected_index, 0);
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == comboBox1) return OnComboBoxChange(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == comboBox2) return OnComboBoxChange(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == CBN_SELCHANGE && (HWND)lParam == comboBox3) return OnComboBoxChange(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"ComboBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  comboBox1 = CreateWindowEx(0, WC_COMBOBOX, L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 10, 10, 120, 21, window, nullptr, nullptr, nullptr);
  comboBox2 = CreateWindowEx(0, WC_COMBOBOX, L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 50, 120, 21, window, nullptr, nullptr, nullptr);
  comboBox3 = CreateWindowEx(0, WC_COMBOBOX, L"", WS_CHILD | WS_VSCROLL | WS_VISIBLE | CBS_SIMPLE, 10, 90, 120, 170, window, nullptr, nullptr, nullptr);

  for (auto item : { L"Item1", L"Item2", L"Item3", L"Item4", L"Item5", L"Item6", L"Item7", L"Item8", L"Item9", L"Item10" }) {
    SendMessage(comboBox1, CB_ADDSTRING, 0, (LPARAM)item);
    SendMessage(comboBox2, CB_ADDSTRING, 0, (LPARAM)item);
    SendMessage(comboBox3, CB_ADDSTRING, 0, (LPARAM)item);
  }
  SendMessage(comboBox1, CB_SETCURSEL, 1, 0);
  SendMessage(comboBox2, CB_SETCURSEL, 1, 0);
  SendMessage(comboBox3, CB_SETCURSEL, 1, 0);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return (int)message.wParam;
}
