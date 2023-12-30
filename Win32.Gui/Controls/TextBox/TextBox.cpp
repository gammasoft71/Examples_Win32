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

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

std::wstring GetText(HWND hwnd) {
  size_t size = SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
  if (!size) return L"";
  auto text = wstring(size, '\0');
  SendMessage(hwnd, WM_GETTEXT, text.size() + 1, reinterpret_cast<LPARAM>(text.c_str()));
  return text;
}

LRESULT OnTextChanged(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto text = GetText(reinterpret_cast<HWND>(lParam));
  for (auto textBox : {textBox1, textBox2})
    if (GetText(textBox) != text)
      SendMessage(textBox, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text.c_str()));
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == EN_CHANGE) return OnTextChanged(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"TextBox example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  textBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"textBox", WS_CHILD | WS_VISIBLE, 10, 10, 100, 23, window, nullptr, nullptr, nullptr);
  textBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"textBox", WS_CHILD | WS_VISIBLE, 10, 50, 100, 23, window, nullptr, nullptr, nullptr);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}
