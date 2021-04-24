#include <Windows.h>

int main() {
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"Hello, World!\n", 14, nullptr, nullptr);
}
