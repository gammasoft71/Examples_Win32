#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <Windows.h>
#include <CommCtrl.h>

HWND form;
HWND button1;
HWND button2;
HWND label1;
HWND label2;

WNDPROC defWndProc;

int button1Clicked = 0;
int button2Clicked = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  if (message == WM_COMMAND && (HWND)lParam == button1) {
    std::wstring result = L"button1 clicked " + std::to_wstring(++button1Clicked) + L" times";
    SendMessage(label1, WM_SETTEXT, 0, (LPARAM)result.c_str());
  }
  if (message == WM_COMMAND && (HWND)lParam == button2) {
    std::wstring result = L"button2 clicked " + std::to_wstring(++button2Clicked) + L" times";
    SendMessage(label2, WM_SETTEXT, 0, (LPARAM)result.c_str());
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main(int argc, char* argv[]) {
  form = CreateWindowEx(0, WC_DIALOG, L"Button example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"button1", WS_CHILD | WS_VISIBLE, 50, 50, 75, 25, form, nullptr, nullptr, nullptr);
  button2 = CreateWindowEx(0, WC_BUTTON, L"button2", WS_CHILD | WS_VISIBLE, 50, 100, 200, 75, form, nullptr, nullptr, nullptr);
  label1 = CreateWindowEx(0, WC_STATIC, L"button1 clicked 0 times", WS_CHILD | WS_VISIBLE, 50, 200, 200, 23, form, nullptr, nullptr, nullptr);
  label2 = CreateWindowEx(0, WC_STATIC, L"button2 clicked 0 times", WS_CHILD | WS_VISIBLE, 50, 230, 200, 23, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  ShowWindow(form, SW_SHOW);

  MSG message;
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
