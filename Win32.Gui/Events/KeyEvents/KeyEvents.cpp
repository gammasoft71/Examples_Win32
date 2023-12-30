#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace std::chrono_literals;

HWND window = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnKeyDown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << "KeyDown={Virtual KeyCode=0x" << fixed << hex << setfill(L'0') << setw(2) << wParam << "}"<< endl;
  OutputDebugString(stream.str().c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnChar(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << "Char={KeyChar='" << static_cast<wchar_t>(wParam ) << "'}" << endl;
  OutputDebugString(stream.str().c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnKeyUp(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << "KeyUp={Virtual KeyCode=0x" << fixed << hex << setfill(L'0') << setw(2) << wParam << "}" << endl;
  OutputDebugString(stream.str().c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnWindowPaint(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT paintStruct;
  HDC hdc = BeginPaint(hwnd, &paintStruct);
  static HBRUSH brush = CreateSolidBrush(RGB(0xF0, 0xF0, 0xF0));
  FillRect(hdc, &paintStruct.rcPaint, brush);
  SetBkMode(hdc, TRANSPARENT);
  RECT rect = paintStruct.rcPaint;
  rect.left = rect.top = 10;
  rect.bottom -= 20;
  rect.right -= 20;
  DrawText(hdc, L"Key traces are sent to the output debuger.", -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK);
  EndPaint(hwnd, &paintStruct);
  return 0;
}

LRESULT OnWindowResize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  LRESULT result = CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  RECT rect;
  GetClientRect(hwnd, &rect);
  InvalidateRect(hwnd, &rect, false);
  return result;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_KEYDOWN && hwnd == window) return OnKeyDown(hwnd, message, wParam, lParam);
  if (message == WM_CHAR && hwnd == window) return OnChar(hwnd, message, wParam, lParam);
  if (message == WM_KEYUP && hwnd == window) return OnKeyUp(hwnd, message, wParam, lParam);
  if (message == WM_PAINT && hwnd == window) return OnWindowPaint(hwnd, message, wParam, lParam);
  if (message == WM_SIZE && hwnd == window) return OnWindowResize(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"KeyEvents example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}
