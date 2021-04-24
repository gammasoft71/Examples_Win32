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

HWND form = nullptr;
HWND tabControl1 = nullptr;
vector<TabPage> tabPages(4);
vector<COLORREF> tabPagesColors = { RGB(0xFF, 0, 0), RGB(0, 0x80, 0), RGB(0, 0, 0xFF), RGB(0xFF, 0xFF, 0) };
vector<wstring> tabPageNames = { L"Red", L"Green", L"Blue", L"Yellow" };
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) PostQuitMessage(0);
  if (message == WM_NOTIFY)
    for (size_t index = 0; index < tabPages.size(); index++)
      ShowWindow(tabPages[index].panel, index == SendMessage(tabControl1, TCM_GETCURSEL, 0, 0) ? SW_SHOW : SW_HIDE);

  if (message == WM_CTLCOLORDLG && (HWND)lParam == form) {
    SetBkColor((HDC)wParam, RGB(0, 0xFF, 0));
    return (LRESULT)CreateSolidBrush(RGB(0, 0xFF, 0));
  }

  if (message == WM_CTLCOLORDLG || message == WM_CTLCOLOR)
    for (size_t index = 0; index < tabPages.size(); index++) {
      if (tabPages[index].panel == (HWND)lParam) {
        SetBkColor((HDC)wParam, tabPagesColors[index]);
        return (LRESULT)CreateSolidBrush(tabPagesColors[index]);
      }
    }
 
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"TabControl example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 406, 316, nullptr, nullptr, nullptr, nullptr);
  tabControl1 = CreateWindowEx(0, WC_TABCONTROL, nullptr, WS_CHILD | WS_VISIBLE, 10, 10, 370, 250, form, nullptr, nullptr, nullptr);
  for (size_t index = 0; index < tabPages.size(); index++) {
    tabPages[index].text = tabPageNames[index];
    tabPages[index].backBrush = CreateSolidBrush(tabPagesColors[index]);
    tabPages[index].tabControlItem.mask = TCIF_TEXT;
    tabPages[index].tabControlItem.pszText = (LPWSTR)tabPages[index].text.c_str();
    TabCtrl_InsertItem(tabControl1, TabCtrl_GetItemCount(tabControl1), &tabPages[index].tabControlItem);
    RECT tabPageRectangle{ 0, 0, 370, 250 };
    SendMessage(tabControl1, TCM_ADJUSTRECT, false, (LPARAM)&tabPageRectangle);
    tabPages[index].panel = CreateWindowEx(0, WC_DIALOG, nullptr, WS_CHILD | WS_CLIPSIBLINGS, tabPageRectangle.left, tabPageRectangle.top, tabPageRectangle.right - tabPageRectangle.left, tabPageRectangle.bottom - tabPageRectangle.top, tabControl1, nullptr, nullptr, nullptr);
  }

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  for (size_t index = 0; index < tabPages.size(); index++) {
    HDC deviceContext = GetDC(tabPages[index].panel);
    SendMessage(form, WM_ERASEBKGND, (WPARAM)deviceContext, (WPARAM)tabPages[index].panel);
    //SendMessage(form, WM_CTLCOLOR, (WPARAM)deviceContext, (WPARAM)tabPages[index].panel);
    ReleaseDC(tabPages[index].panel, deviceContext);
    RedrawWindow((HWND)form, nullptr, nullptr, RDW_INVALIDATE);
  }

  ShowWindow(tabPages[0].panel, SW_SHOW);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
