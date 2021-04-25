#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <initializer_list>
#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND radioButton1 = nullptr;
HWND radioButton2 = nullptr;
HWND radioButton3 = nullptr;
HWND radioButton4 = nullptr;
HWND radioButton5 = nullptr;
HWND staticText1 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnAutoRadioButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  SendMessage(staticText1, WM_SETTEXT, 0, (LPARAM)(L"Radio 3 checked = "s + (SendMessage(radioButton3, BM_GETCHECK, 0, 0) == BST_CHECKED ? L"true   "s : L"false   "s)).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnRadioButton1Click(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  // Uncomments next lines to check / uncheck radio button 1 (auto check is false...)
  //SendMessage(radioButton1, BM_SETCHECK, SendMessage(radioButton1, BM_GETCHECK, 0, 0) == BST_UNCHECKED ? BST_CHECKED : BST_UNCHECKED, 0);
  //for (auto radioButton : { radioButton2, radioButton3, radioButton4, radioButton5 })
  //  SendMessage(radioButton, BM_SETCHECK, BST_UNCHECKED, 0);
  return OnAutoRadioButtonClick(hwnd, message, wParam, lParam);
}

LRESULT OnRadioButton5Click(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  // Uncomments next lines to check / uncheck radio button 5 (auto check is false...)
  //SendMessage(radioButton5, BM_SETCHECK, SendMessage(radioButton1, BM_GETCHECK, 0, 0) == BST_UNCHECKED ? BST_CHECKED : BST_UNCHECKED, 0);
  //for (auto radioButton : { radioButton1, radioButton2, radioButton3, radioButton4 })
  //  SendMessage(radioButton, BM_SETCHECK, BST_UNCHECKED, 0);
  return OnAutoRadioButtonClick(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == radioButton1) return OnRadioButton1Click(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == radioButton2) return OnAutoRadioButtonClick(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == radioButton3) return OnAutoRadioButtonClick(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == radioButton4) return OnAutoRadioButtonClick(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == radioButton5) return OnRadioButton5Click(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"RadioButton example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  radioButton1 = CreateWindowEx(0, WC_BUTTON, L"Radio 1", WS_CHILD | BS_RADIOBUTTON | WS_VISIBLE, 30, 30, 104, 24, window, nullptr, nullptr, nullptr);
  radioButton2 = CreateWindowEx(0, WC_BUTTON, L"Radio 2", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 30, 60, 104, 24, window, nullptr, nullptr, nullptr);
  radioButton3 = CreateWindowEx(0, WC_BUTTON, L"Radio 3", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 30, 90, 104, 24, window, nullptr, nullptr, nullptr);
  radioButton4 = CreateWindowEx(0, WC_BUTTON, L"Radio 4", WS_CHILD | BS_AUTORADIOBUTTON | BS_PUSHLIKE | WS_VISIBLE, 30, 120, 104, 24, window, nullptr, nullptr, nullptr);
  radioButton5 = CreateWindowEx(0, WC_BUTTON, L"Radio 5", WS_CHILD | BS_RADIOBUTTON | BS_PUSHLIKE | WS_VISIBLE, 30, 150, 104, 24, window, nullptr, nullptr, nullptr);
  staticText1 = CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE | SS_SIMPLE, 20, 180, 200, 23, window, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(radioButton3, BM_SETCHECK, BST_CHECKED, 0);
  SendMessage(staticText1, WM_SETTEXT, 0, (LPARAM)(L"Radio 3 checked = "s + (SendMessage(radioButton3, BM_GETCHECK, 0, 0) == BST_CHECKED ? L"true   "s : L"false   "s)).c_str());

  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
