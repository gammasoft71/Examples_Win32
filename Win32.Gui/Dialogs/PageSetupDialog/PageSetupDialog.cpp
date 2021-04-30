#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>
#include <ShlObj.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND button1 = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAGESETUPDLG pageSetup = { 0 };
  pageSetup.lStructSize = sizeof(pageSetup);
  pageSetup.hwndOwner = hwnd;
  pageSetup.Flags = PSD_DEFAULTMINMARGINS;
  if (PageSetupDlg(&pageSetup) != 0) {
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button1) return OnButtonClick(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"PageSetupDialog exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"Page Setup...", WS_CHILD | WS_VISIBLE, 10, 10, 100, 25, window, nullptr, nullptr, nullptr);
  
  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
}
