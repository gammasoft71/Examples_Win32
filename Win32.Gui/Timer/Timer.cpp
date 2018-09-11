#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <iomanip>
#include <sstream>
#include <Windows.h>
#include <CommCtrl.h>

using namespace std;

HWND form = nullptr;
HWND label = nullptr;
HWND button = nullptr;
UINT_PTR timer = 0;
bool enableTimer = false;
int counter = 0;

WNDPROC defWndProc;

void CALLBACK  OnTimerTick(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD time) {
  if (idEvent == timer) {
    wstringstream stream;
    stream << fixed << setprecision(1) << (double)++counter / 10;
    SendMessage(label, WM_SETTEXT, 0, (LPARAM)stream.str().c_str());
  }
}

void OnButtonClick() {
  enableTimer = !enableTimer;
  SendMessage(button, WM_SETTEXT, 0, enableTimer ? (LPARAM)L"Stop" : (LPARAM)L"Start");
  if (enableTimer)
    timer = SetTimer(nullptr, 0, 100, OnTimerTick);
  else
    KillTimer(nullptr, timer);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_CLOSE: PostQuitMessage(0); return 0;
  case WM_ERASEBKGND: SetBkColor((HDC)wParam, GetBkColor(GetDC(hwnd))); return 0;
  case WM_CTLCOLORSTATIC: SetTextColor((HDC)wParam, RGB(30, 144, 255)); return 0;
  case WM_COMMAND: if ((HWND)lParam == button) OnButtonClick(); return 0;
  default: return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
  }
}

int main(int argc, char* argv[]) {
  form = CreateWindowEx(0, WC_DIALOG, L"Timer example", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 246, 176, nullptr, nullptr, nullptr, nullptr);
  label = CreateWindowEx(0, WC_STATIC, L"0.0", WS_CHILD | WS_VISIBLE, 10, 10, 210, 70, form, nullptr, nullptr, nullptr);
  button = CreateWindowEx(0, WC_BUTTON, L"Start", WS_CHILD | WS_VISIBLE, 10, 100, 75, 25, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(form, WM_CTLCOLORSTATIC, (WPARAM)GetDC(label), (LPARAM)label);
  SendMessage(label, WM_SETFONT, (WPARAM)CreateFont(int(-48 / 72.0f * GetDeviceCaps(GetDC(form), LOGPIXELSY)), 0, 0, 0, FW_NORMAL, true, false, false, 0, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial"), true);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}
