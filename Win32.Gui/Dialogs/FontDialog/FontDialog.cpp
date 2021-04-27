#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

HWND window = nullptr;
HWND button1 = nullptr;
HWND staticText1 = nullptr;
WNDPROC defWndProc = nullptr;
COLORREF textForeColor = RGB(0, 0, 0);

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  CHOOSEFONT chooseFont{ 0 };
  chooseFont.lStructSize = sizeof(chooseFont);
  chooseFont.hwndOwner = hwnd;
  HFONT font = reinterpret_cast<HFONT>(SendMessage(staticText1, WM_GETFONT, 0, 0));
  if (!font) font = reinterpret_cast<HFONT>(GetStockObject(SYSTEM_FONT));
  LOGFONT logFont{ 0 };
  GetObject(font, sizeof(logFont), &logFont);
  chooseFont.lpLogFont = &logFont;
  chooseFont.iPointSize = static_cast<int>(std::abs(logFont.lfHeight * 72.0f / static_cast<float>(GetDeviceCaps(GetDC(staticText1), LOGPIXELSY))));
  chooseFont.Flags = CF_INITTOLOGFONTSTRUCT | CF_TTONLY | CF_EFFECTS | CF_SCALABLEONLY;
  chooseFont.rgbColors = textForeColor;
  if (ChooseFont(&chooseFont)) {
    textForeColor = chooseFont.rgbColors;
    SendMessage(staticText1, WM_SETFONT, reinterpret_cast<WPARAM>(CreateFontIndirect(chooseFont.lpLogFont)), true);
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT ChangeStaticTextColor(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  LRESULT result = CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  SetTextColor(reinterpret_cast<HDC>(wParam), textForeColor);
  return result;
}

LRESULT OnWindowResize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  LRESULT result = CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  RECT windowRect, staticTextRect;
  GetClientRect(window, &windowRect);
  GetClientRect(staticText1, &staticTextRect);
  staticTextRect.right = windowRect.right - 10;
  staticTextRect.bottom = windowRect.bottom - 10;
  SetWindowPos(staticText1, HWND_TOP, staticTextRect.left, staticTextRect.top, staticTextRect.right - staticTextRect.left, staticTextRect.bottom - staticTextRect.top, SWP_NOMOVE);
  RedrawWindow(staticText1, nullptr, nullptr, RDW_INVALIDATE);
  return result;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_SIZE && hwnd == window) return OnWindowResize(hwnd, message, wParam, lParam);
  if (message == WM_CTLCOLORSTATIC && reinterpret_cast<HWND>(lParam) == staticText1) return ChangeStaticTextColor(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button1) return OnButtonClick(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"FontDialog exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 416, 440, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"Font...", WS_CHILD | WS_VISIBLE, 10, 10, 80, 25, window, nullptr, nullptr, nullptr);
  staticText1 = CreateWindowEx(0, WC_STATIC, 
    L"The quick brown fox jumps over the lazy dog.\n"
    L"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.\n"
    L"0123456789+-*/%~^&|=<>≤≥±÷≠{{[()]}},;:.?¿!¡\n"
    L"àçéèêëïî@@°_#§$ù£€æœøπµ©®∞\\\"'\n"
    L"\u0400\u0401\u0402\u0403\u0404\u0405\u0406\u0407\u0408\u0409\u040a\u040b\u040c\u040d\u040e\u040f\n"
    L"\u0410\u0411\u0412\u0413\u0414\u0415\u0416\u0417\u0418\u0419\u041a\u041b\u041c\u041d\u041e\u041f\n"
    L"\u4ea0\u4ea1\u4ea2\u4ea3\u4ea4\u4ea5\u4ea6\u4ea7\u4ea8\u4ea9\u4eaa\u4eab\u4eac\u4ead\u4eae\u4eaf\n"
    L"\u4eb0\u4eb1\u4eb2\u4eb3\u4eb4\u4eb5\u4eb6\u4eb7\u4eb8\u4eb9\u4eba\u4ebb\u4ebc\u4ebd\u4ebe\u4ebf\n"
    L"\U0001F428", WS_CHILD | WS_VISIBLE, 10, 50, 380, 340, window, nullptr, nullptr, nullptr);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return static_cast<int>(message.wParam);
}
