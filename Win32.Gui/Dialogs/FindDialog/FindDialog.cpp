#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND button1 = nullptr;
HWND findReplaceDialog = nullptr;
WNDPROC defWndProc = nullptr;
wstring findWhat = L"Gammasoft";
UINT UM_FIND_BUTTON_CLICKED = RegisterWindowMessage(FINDMSGSTRING);

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

UINT_PTR OnFind(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  FINDREPLACE* findReplace = reinterpret_cast<FINDREPLACE*>(lParam);
  if ((findReplace->Flags & FR_DIALOGTERM) == FR_DIALOGTERM) OutputDebugString(L"Cancel dialog\n");
  if ((findReplace->Flags & FR_FINDNEXT) == FR_FINDNEXT) OutputDebugString((L"Find next \""s + findReplace->lpstrFindWhat + L"\"\n"s).c_str());
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}
LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static wchar_t findWhatBuffer[1024];

  lstrcpyW(findWhatBuffer, findWhat.c_str());

  static FINDREPLACE findReplace = { 0 };
  findReplace.lStructSize = sizeof(findReplace);
  findReplace.hwndOwner = hwnd;
  findReplace.Flags = FR_DOWN | FR_FINDNEXT | FR_MATCHCASE | FR_WHOLEWORD;
  findReplace.lpstrFindWhat = findWhatBuffer;
  findReplace.wFindWhatLen = 1024;
  findReplaceDialog = FindText(&findReplace);

  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button1) return OnButtonClick(hwnd, message, wParam, lParam);
  if (message == UM_FIND_BUTTON_CLICKED && hwnd == window) return OnFind(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"FindDialog exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"Find...", WS_CHILD | WS_VISIBLE, 10, 10, 75, 25, window, nullptr, nullptr, nullptr);
  
  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = {0};
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}
