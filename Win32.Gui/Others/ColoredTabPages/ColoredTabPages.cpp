#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <vector>
#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>

using namespace std;

struct TabPage {
  HWND panel;
  TCITEM tabControlItem;
  wstring text;
  HBRUSH backBrush;
};

HWND window = nullptr;
HWND tabControl1 = nullptr;
vector<TabPage> tabPages(4);
vector<COLORREF> tabPagesColors = { RGB(0xFF, 0, 0), RGB(0, 0x80, 0), RGB(0, 0, 0xFF), RGB(0xFF, 0xFF, 0) };
vector<wstring> tabPageNames = { L"Red", L"Green", L"Blue", L"Yellow" };
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnWindowNotify(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  for (size_t index = 0; index < tabPages.size(); index++) {
    size_t currentPageIndex = SendMessage(tabControl1, TCM_GETCURSEL, 0, 0);
    ShowWindow(tabPages[index].panel, index == currentPageIndex ? SW_SHOW : SW_HIDE);
    SendMessage(window, WM_ERASEBKGND, reinterpret_cast<WPARAM>(window), 0);
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnEraseBackground(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  for (size_t index = 0; index < tabPages.size(); ++index) {
    RECT rect;
    GetClientRect(tabPages[index].panel, &rect);
    FillRect(GetDC(tabPages[index].panel), &rect, tabPages[index].backBrush);
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_NOTIFY) return OnWindowNotify(hwnd, message, wParam, lParam);
  if (message == WM_ERASEBKGND) return OnEraseBackground(hwnd, message, wParam, lParam);
  if (message == WM_ACTIVATE) SendMessage(window, WM_ERASEBKGND, reinterpret_cast<WPARAM>(window), 0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"TabControl example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 406, 316, nullptr, nullptr, nullptr, nullptr);
  tabControl1 = CreateWindowEx(0, WC_TABCONTROL, nullptr, WS_CHILD | WS_VISIBLE | TCS_BOTTOM, 10, 10, 370, 250, window, nullptr, nullptr, nullptr);
  for (size_t index = 0; index < tabPages.size(); index++) {
    tabPages[index].text = tabPageNames[index];
    tabPages[index].backBrush = CreateSolidBrush(tabPagesColors[index]);
    tabPages[index].tabControlItem.mask = TCIF_TEXT;
    tabPages[index].tabControlItem.pszText = const_cast<LPWSTR>(tabPages[index].text.c_str());
    TabCtrl_InsertItem(tabControl1, TabCtrl_GetItemCount(tabControl1), &tabPages[index].tabControlItem);
    RECT tabPageRectangle{ 0, 0, 370, 250 };
    SendMessage(tabControl1, TCM_ADJUSTRECT, false, reinterpret_cast<LPARAM>(&tabPageRectangle));
    tabPages[index].panel = CreateWindowEx(0, WC_DIALOG, nullptr, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, tabPageRectangle.left, tabPageRectangle.top, tabPageRectangle.right - tabPageRectangle.left, tabPageRectangle.bottom - tabPageRectangle.top, tabControl1, nullptr, nullptr, nullptr);
    SetBkColor(GetDC(tabPages[index].panel), tabPagesColors[index]);
  }
  TabCtrl_SetCurSel(tabControl1, -1);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc));

  ShowWindow(window, SW_SHOW);
  TabCtrl_SetCurSel(tabControl1, 0);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
