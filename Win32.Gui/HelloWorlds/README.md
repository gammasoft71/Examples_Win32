
# Win32.Gui Examples

Shows how to use [Win32](https://learn.microsoft.com/en-us/windows/win32/api/) controls by proghramming code ([c++17](https://en.cppreference.com/w/)).

[![win32](../docs/Pictures/win32_header.png)](https://gammasoft71.wixsite.com/gammasoft/win32)

## Hello Worlds

* [HelloWorldEmoticons](HelloWorlds/HelloWorldEmoticons/README.md) The classic first application HelloWorld width emoticons.
* [HelloWorldMessageBox](HelloWorlds/HelloWorldMessageBox/README.md) The classic first application HelloWorld with MessageBox.
* [HelloWorldMessageBox2](HelloWorlds/HelloWorldMessageBox2/README.md) The classic first application HelloWorld with MessageBox.
* [HelloWorldPaint](HelloWorlds/HelloWorldPaint/README.md) The classic first application HelloWorld with GDI+ drawing objects.
* [HelloWorldStaticText](HelloWorlds/HelloWorldStaticText/README.md) The classic first application HelloWorld with StaticText control.

## Generate and build

To build this project, open "Console" and type following lines:

``` shell
mkdir build && cd build
cmake .. 
start HelloWorlds.sln
```

Select any project and type Ctrl+F5 to build and run it.

## Remarks

This project run only on Windows with [Visual Studio](https://www.visualstudio.com) and [CMake](https://cmake.org).

See [Desktop App User Interface](https://docs.microsoft.com/en-us/windows/win32/windows-application-ui-development) for more informations.
