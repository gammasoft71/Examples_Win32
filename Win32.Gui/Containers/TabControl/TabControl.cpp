#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <string>
#include <vector>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

struct TabPage {
  HWND panel;
  TCITEM tabControlItem;
  wstring text;
};

HWND window = nullptr;
HWND tabControl1 = nullptr;
vector<TabPage> tabPages(3);
WNDPROC defWndProc = nullptr;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnWindowNotify(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  for (size_t index = 0; index < tabPages.size(); index++)
    ShowWindow(tabPages[index].panel, index == SendMessage(tabControl1, TCM_GETCURSEL, 0, 0) ? SW_SHOW : SW_HIDE);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_NOTIFY && hwnd == window) return OnWindowNotify(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"TabControl example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 406, 316, nullptr, nullptr, nullptr, nullptr);
  tabControl1 = CreateWindowEx(0, WC_TABCONTROL, nullptr, WS_CHILD | WS_VISIBLE, 10, 10, 370, 250, window, nullptr, nullptr, nullptr);
  for (size_t index = 0; index < tabPages.size(); index++) {
    tabPages[index].text = L"tabPage"s + to_wstring(index + 1);
    tabPages[index].tabControlItem.mask = TCIF_TEXT;
    tabPages[index].tabControlItem.pszText = (LPWSTR)tabPages[index].text.c_str();
    TabCtrl_InsertItem(tabControl1, TabCtrl_GetItemCount(tabControl1), &tabPages[index].tabControlItem);
    RECT tabPageRectangle{ 0, 0, 370, 250 };
    SendMessage(tabControl1, TCM_ADJUSTRECT, false, (LPARAM)&tabPageRectangle);
    tabPages[index].panel = CreateWindowEx(0, WC_DIALOG, nullptr, WS_CHILD | WS_CLIPSIBLINGS, tabPageRectangle.left, tabPageRectangle.top, tabPageRectangle.right - tabPageRectangle.left, tabPageRectangle.bottom - tabPageRectangle.top, tabControl1, nullptr, nullptr, nullptr);
  }

  defWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
  ShowWindow(tabPages[0].panel, SW_SHOW);
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
