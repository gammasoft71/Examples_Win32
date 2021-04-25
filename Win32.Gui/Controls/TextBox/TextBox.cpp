#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace literals;

HWND window = nullptr;
HWND textBox1 = nullptr;
HWND textBox2 = nullptr;
WNDPROC defWndProc = nullptr;

std::wstring GetText(HWND hwnd) {
  wstring text(SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0) + 1, '\0');
  SendMessage(hwnd, WM_GETTEXT, (WPARAM)text.size(), (LPARAM)text.c_str());
  return text;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_COMMAND && HIWORD(wParam) == EN_CHANGE) {
    wstring text = GetText((HWND)lParam);
    HWND otherTextBox = (HWND)lParam == textBox1 ? textBox2 : textBox1;
    if (GetText(otherTextBox) != text)
      SendMessage(otherTextBox, WM_SETTEXT, 0, (LPARAM)text.c_str());
  }
  if (message == WM_CLOSE && hwnd == window) PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"TextBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  textBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"textBox", WS_CHILD | WS_VISIBLE, 10, 10, 100, 23, window, nullptr, nullptr, nullptr);
  textBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"textBox", WS_CHILD | WS_VISIBLE, 10, 50, 100, 23, window, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return (int)message.wParam;
}
