#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

HWND form = nullptr;
HWND buttonShowMessage = nullptr;
HWND labelDiallogResult = nullptr;
WNDPROC defWndProc = nullptr;

wstring DialogResultTostring(int32_t ddialogResult) {
  static map<int32_t, wstring> dialogResults{{IDABORT, L"Abort"}, {IDCANCEL, L"Cancel"}, {IDCLOSE, L"Close"}, {IDCONTINUE, L"Contnue"}, {IDHELP, L"Hellp"}, {IDIGNORE, L"Ignore"}, {IDNO, L"No"}, {IDOK, L"OK"}, {IDRETRY, L"Retry"}, {IDTIMEOUT, L"Timeout"}, {IDTRYAGAIN, L"TryAgain"}, {IDYES, L"Yes"}};
  auto it = dialogResults.find(ddialogResult);
  return it != dialogResults.end() ? it->second : L"(unknown)";
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == buttonShowMessage) {
    wstring result = L"DialogResult = "s + DialogResultTostring(MessageBox(form, L"Hello, World!", L"Message", MB_OKCANCEL|MB_ICONWARNING));
    SendMessage(labelDiallogResult, WM_SETTEXT, 0, (LPARAM)result.c_str());
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"Message box exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  buttonShowMessage = CreateWindowEx(0, WC_BUTTON, L"Message...", WS_CHILD | WS_VISIBLE, 10, 10, 80, 25, form, nullptr, nullptr, nullptr);
  labelDiallogResult = CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE, 10, 45, 200, 23, form, nullptr, nullptr, nullptr);
  
  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(form, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
