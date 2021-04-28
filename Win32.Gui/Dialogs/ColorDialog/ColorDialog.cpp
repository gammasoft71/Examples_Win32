#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND button1 = nullptr;
WNDPROC defWndProc = nullptr;
COLORREF window_back_color = RGB(0xF0, 0xF0, 0xF0);

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static COLORREF customColors[] = {RGB(0xFF, 0x00, 0x00), RGB(0x00, 0xFF, 0x00), RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0x00), RGB(0xF0, 0xF0, 0xF0), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0xFF, 0xFF) };
  CHOOSECOLOR chooseColor { 0 };
  chooseColor.lStructSize = sizeof(chooseColor);
  chooseColor.hwndOwner = hwnd;
  chooseColor.rgbResult = window_back_color;
  chooseColor.lpCustColors = customColors;
  chooseColor.Flags = CC_RGBINIT | CC_ANYCOLOR;

  if (ChooseColor(&chooseColor)) {
    window_back_color = chooseColor.rgbResult;
    RECT rect;
    GetClientRect(window, &rect);
    InvalidateRect(window, &rect, true);
  }

  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnControlColorDialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  static COLORREF color = window_back_color;
  static HBRUSH brush = CreateSolidBrush(color);

  if (color != window_back_color) {
    DeleteObject(brush);
    color = window_back_color;
    brush = CreateSolidBrush(color);
  }

  return reinterpret_cast<LRESULT>(brush);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button1) return OnButtonClick(hwnd, message, wParam, lParam);
  if (message == WM_CTLCOLORDLG && reinterpret_cast<HWND>(lParam) == window) return OnControlColorDialog(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"ColorDialog exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"Color...", WS_CHILD | WS_VISIBLE, 10, 10, 80, 25, window, nullptr, nullptr, nullptr);
  
  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
}
