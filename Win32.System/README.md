
# Win32.System Examples

Shows how to use [Win32](https://learn.microsoft.com/en-us/windows/win32/api/) System api by proghramming code ([c++17](https://en.cppreference.com/w/)).

[![win32](../docs/Pictures/win32_header.png)](https://gammasoft71.wixsite.com/gammasoft/win32)

## [Hello World](HelloWorlds/README.md)

* [HelloWorld](HelloWorlds/HelloWorld/README.md) The classic first application "Hello, World!" with Win32 [WriteConsole](https://learn.microsoft.com/windows/console/writeconsole) function.

## [Console](Console/README.md)

* [Console](Console/Console/README.md) demonstrates the use of [WriteConsole](https://learn.microsoft.com/windows/console/writeconsole) and [ReadConsole](https://learn.microsoft.com/windows/console/readconsole) functions.
* [ConsoleColor](Console/ConsoleColor/README.md) demonstrates the use of [WriteConsole](https://learn.microsoft.com/windows/console/writeconsole) and [SetConsoleTextAttribute](https://learn.microsoft.com/windows/console/setconsoletextattribute) functions.

## [Processes](Processes/README.md)

* [Process](Processes/Process/README.md) demonstrates the use of [CreateProcess](https://learn.microsoft.com/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessw) function.

## [Others](Others/README.md)

* [StringConversion](Others/StringConversion/README.md) demonstrates the use of std::wcstombs and std::mbstowcs functions.

## Generate and build

To build this project, open "Console" and type following lines:

``` shell
mkdir build && cd build
cmake .. 
start Win32.Gui.sln
```

Select any project and type Ctrl+F5 to build and run it.
