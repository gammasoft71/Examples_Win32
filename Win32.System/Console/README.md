# Console

[This folder](.) contains Win32 console examples.

* [Console](Console/README.md) demonstrates the use of [WriteConsole](https://learn.microsoft.com/windows/console/writeconsole) and [ReadConsole](https://learn.microsoft.com/windows/console/readconsole) functions.
* [ConsoleColor](ConsoleColor/README.md) demonstrates the use of [WriteConsole](https://learn.microsoft.com/windows/console/writeconsole) and [SetConsoleTextAttribute](https://learn.microsoft.com/windows/console/setconsoletextattribute) functions.

## Generate and build

To build this project, open "Console" and type following lines:

``` shell
mkdir build && cd build
cmake .. 
start Console.sln
```

Select any project and type Ctrl+F5 to build and run it.
