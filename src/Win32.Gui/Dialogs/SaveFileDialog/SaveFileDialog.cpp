#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <map>
#include <string>
#include <Windows.h>
#include <CommCtrl.h>
#include <ShlObj.h>

using namespace std;
using namespace std::literals;

HWND window = nullptr;
HWND button1 = nullptr;
HWND staticText1 = nullptr;
WNDPROC defWndProc = nullptr;
wstring selectedFile;

LRESULT OnWindowClose(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PostQuitMessage(0);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT OnButtonClick(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  wchar_t iInitialDirectory[MAX_PATH];
  SHGetSpecialFolderPath(nullptr, iInitialDirectory, CSIDL_DESKTOP, false);

  OPENFILENAME openFileName = { 0 };
  openFileName.lStructSize = sizeof(openFileName);
  openFileName.hwndOwner = hwnd;
  openFileName.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*";
  openFileName.nFilterIndex = 1;

  std::wstring fileName(MAX_PATH, ' ');
  lstrcpyW(fileName.data(), selectedFile.c_str());
  openFileName.lpstrFile = (LPWSTR)fileName.c_str();
  openFileName.nMaxFile = MAX_PATH;
  openFileName.lpstrInitialDir = iInitialDirectory;
  openFileName.Flags = OFN_CREATEPROMPT;
  openFileName.lpstrDefExt = L"txt";

  BOOL result = GetSaveFileName(&openFileName);
  if (result) {
    selectedFile = fileName;
    SendMessage(staticText1, WM_SETTEXT, 0, reinterpret_cast<LPARAM>((L"File = "s + selectedFile).c_str()));
  }
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == window) return OnWindowClose(hwnd, message, wParam, lParam);
  if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == button1) return OnButtonClick(hwnd, message, wParam, lParam);
  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  window = CreateWindowEx(0, WC_DIALOG, L"SaveFileDialog exemple", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
  button1 = CreateWindowEx(0, WC_BUTTON, L"Save...", WS_CHILD | WS_VISIBLE, 10, 10, 80, 25, window, nullptr, nullptr, nullptr);
  staticText1 = CreateWindowEx(0, WC_STATIC, L"File = ", WS_CHILD | WS_VISIBLE, 10, 45, 274, 215, window, nullptr, nullptr, nullptr);

  defWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
  ShowWindow(window, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
}
