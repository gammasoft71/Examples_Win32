#include <Windows.h>

int main(int argc, char* argv[]) {
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"Hello, World!\n", 14, nullptr, nullptr);  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"Hello, World!\n", 14, nullptr, nullptr);
}
