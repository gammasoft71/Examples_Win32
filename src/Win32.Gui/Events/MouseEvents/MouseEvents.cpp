#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>
#include <Windows.h>
#include <Windowsx.h>
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

wstring MouseToString(const wstring& event, const wstring& button, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << event << "={Button=" << button << ", Virtual Keys=0x" << hex << setfill(L'0') << setw(2) << GET_KEYSTATE_WPARAM(wParam) << dec << ", location=[{x=" << GET_X_LPARAM(lParam) << ", y=" << GET_Y_LPARAM(lParam) << "}]" << "}" << endl;
  return stream.str();
}

LRESULT OnLeftButtonDoubleClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDoubleClick", L"Left", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnLeftButtonDown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDown", L"Left", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnLeftButtonUp(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseUp", L"Left", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnMouseHorizontalWheel(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << "MouseHorizontalWheel={Delta=" << GET_WHEEL_DELTA_WPARAM(wParam) << ", location=[{x=" << GET_X_LPARAM(lParam) << ", y=" << GET_Y_LPARAM(lParam) << "}]" << "}" << endl;
  OutputDebugString(stream.str().c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnMouseMove(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << "MouseMove={Virtual Keys=0x" << hex << setfill(L'0') << setw(2) << GET_KEYSTATE_WPARAM(wParam) << dec << ", location=[{x=" << GET_X_LPARAM(lParam) << ", y=" << GET_Y_LPARAM(lParam) << "}]" << "}" << endl;
  OutputDebugString(stream.str().c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnMouseWheel(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wstringstream stream;
  stream << "MouseWheel={Delta=" << GET_WHEEL_DELTA_WPARAM(wParam) << ", location=[{x=" << GET_X_LPARAM(lParam) << ", y=" << GET_Y_LPARAM(lParam) << "}]" << "}" << endl;
  OutputDebugString(stream.str().c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnMiddleButtonDoubleClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDoubleClick", L"Middle", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnMiddleButtonDown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDown", L"Middle", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnMiddleButtonUp(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseUp", L"Middle", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnRightButtonDoubleClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDoubleClick", L"Right", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnRightButtonDown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDown", L"Right", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnRightButtonUp(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseUp", L"Right", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnXButtonDoubleClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDoubleClick", L"X", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnXButtonDown(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseDown", L"X", wParam, lParam).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnXButtonUp(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  OutputDebugString(MouseToString(L"MouseUp", L"X", wParam, lParam).c_str());
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
  DrawText(hdc, L"Mouse traces are sent to the output debuger.", -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK);
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
  if (message == WM_LBUTTONDBLCLK && hwnd == window) return OnLeftButtonDoubleClick(hwnd, message, wParam, lParam);
  if (message == WM_LBUTTONDOWN && hwnd == window) return OnLeftButtonDown(hwnd, message, wParam, lParam);
  if (message == WM_LBUTTONUP && hwnd == window) return OnLeftButtonUp(hwnd, message, wParam, lParam);
  if (message == WM_MBUTTONDBLCLK && hwnd == window) return OnMiddleButtonDoubleClick(hwnd, message, wParam, lParam);
  if (message == WM_MBUTTONDOWN && hwnd == window) return OnMiddleButtonDown(hwnd, message, wParam, lParam);
  if (message == WM_MBUTTONUP && hwnd == window) return OnMiddleButtonUp(hwnd, message, wParam, lParam);
  if (message == WM_MOUSEHWHEEL && hwnd == window) return OnMouseHorizontalWheel(hwnd, message, wParam, lParam);
  if (message == WM_MOUSEMOVE && hwnd == window) return OnMouseMove(hwnd, message, wParam, lParam);
  if (message == WM_MOUSEWHEEL && hwnd == window) return OnMouseWheel(hwnd, message, wParam, lParam);
  if (message == WM_RBUTTONDBLCLK && hwnd == window) return OnRightButtonDoubleClick(hwnd, message, wParam, lParam);
  if (message == WM_RBUTTONDOWN && hwnd == window) return OnRightButtonDown(hwnd, message, wParam, lParam);
  if (message == WM_RBUTTONUP && hwnd == window) return OnRightButtonUp(hwnd, message, wParam, lParam);
  if (message == WM_XBUTTONDBLCLK && hwnd == window) return OnXButtonDoubleClick(hwnd, message, wParam, lParam);
  if (message == WM_XBUTTONDOWN && hwnd == window) return OnXButtonDown(hwnd, message, wParam, lParam);
  if (message == WM_XBUTTONUP && hwnd == window) return OnXButtonUp(hwnd, message, wParam, lParam);
  if (message == WM_PAINT && hwnd == window) return OnWindowPaint(hwnd, message, wParam, lParam);
  if (message == WM_SIZE && hwnd == window) return OnWindowResize(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"MouseEvents example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));  
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}
