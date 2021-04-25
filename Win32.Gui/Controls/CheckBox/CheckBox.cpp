#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>
#include <map>
#include <string>

using namespace std;

HWND window = nullptr;
HWND checkBox1 = nullptr;
HWND checkBox2 = nullptr;
HWND checkBox3 = nullptr;
HWND checkBox4 = nullptr;
HWND checkBox5 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

wstring ButtonStateToString(LRESULT state) {
  map<LRESULT, wstring> states = {{BST_UNCHECKED, L"Unchecked"}, {BST_CHECKED, L"Checked"}, {BST_INDETERMINATE, L"Indeterminate"}};
  auto it = states.find(state);
  return it != states.end() ? it->second : L"(unknown)";
}

LRESULT OnAutoCheckBoxClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)ButtonStateToString(SendMessage((HWND)lParam, BM_GETCHECK, 0, 0)).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnCheckBox1Click(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  // Uncomments next line to check / uncheck check box 1 (auto check is false...)
  //SendMessage(checkBox1, BM_SETCHECK, SendMessage(checkBox1, BM_GETCHECK, 0, 0) == BST_UNCHECKED ? BST_CHECKED : BST_UNCHECKED, 0);
  return OnAutoCheckBoxClick(hwnd, message, wParam, lParam);
}

LRESULT OnCheckBox5Click(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  // Uncomments next line to check / uncheck check box 5 (auto check is false...)
  //SendMessage(checkBox5, BM_SETCHECK, SendMessage(checkBox5, BM_GETCHECK, 0, 0) == BST_UNCHECKED ? BST_CHECKED : BST_UNCHECKED, 0);
  return OnAutoCheckBoxClick(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == checkBox1) return OnCheckBox1Click(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == checkBox2) return OnAutoCheckBoxClick(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == checkBox3) return OnAutoCheckBoxClick(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == checkBox4) return OnAutoCheckBoxClick(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == checkBox5) return OnCheckBox5Click(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"CheckBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  checkBox1 = CreateWindowEx(0, WC_BUTTON, L"Unchecked", WS_CHILD | BS_CHECKBOX | WS_VISIBLE, 30, 30, 104, 24, window, nullptr, nullptr, nullptr);
  checkBox2 = CreateWindowEx(0, WC_BUTTON, L"Checked", WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 30, 60, 104, 24, window, nullptr, nullptr, nullptr);
  checkBox3 = CreateWindowEx(0, WC_BUTTON, L"Indeterminate", WS_CHILD | BS_AUTO3STATE | WS_VISIBLE, 30, 90, 104, 24, window, nullptr, nullptr, nullptr);
  checkBox4 = CreateWindowEx(0, WC_BUTTON, L"Checked", WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_VISIBLE, 30, 120, 104, 24, window, nullptr, nullptr, nullptr);
  checkBox5 = CreateWindowEx(0, WC_BUTTON, L"Unchecked", WS_CHILD | BS_CHECKBOX | BS_PUSHLIKE | WS_VISIBLE, 30, 150, 104, 24, window, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(checkBox1, BM_SETCHECK, BST_UNCHECKED, 0);
  SendMessage(checkBox2, BM_SETCHECK, BST_CHECKED, 0);
  SendMessage(checkBox3, BM_SETCHECK, BST_INDETERMINATE, 0);
  SendMessage(checkBox4, BM_SETCHECK, BST_CHECKED, 0);

  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
