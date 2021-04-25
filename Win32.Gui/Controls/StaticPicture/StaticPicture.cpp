#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND window = nullptr;
HWND panel1 = nullptr;
HWND staticPicture1 = nullptr;
HBITMAP picture = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"StaticPicture example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 340, nullptr, nullptr, nullptr, nullptr);
  panel1 = CreateWindowEx(0, WC_DIALOG, nullptr, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER, 10, 10, 280, 280, window, nullptr, nullptr, nullptr);
  staticPicture1 = CreateWindowEx(0, WC_STATIC, L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, 12, 12, 280, 280, panel1, nullptr, nullptr, nullptr);
  picture = (HBITMAP)LoadImage(nullptr, L"Resources\\Logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  SendMessage(staticPicture1, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)picture);;

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
