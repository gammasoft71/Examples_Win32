# Hello Worlds

[This folder](.) contains Win32 controls "Hello, World!" examples.

* [HelloWorldEmoticons](HelloWorldEmoticons/README.md) The classic first application HelloWorld width emoticons.
* [HelloWorldMessageBox](HelloWorldMessageBox/README.md) The classic first application HelloWorld with MessageBox.
* [HelloWorldMessageBox2](HelloWorldMessageBox2/README.md) The classic first application HelloWorld with MessageBox.
* [HelloWorldPaint](HelloWorldPaint/README.md) The classic first application HelloWorld with GDI+ drawing objects.
* [HelloWorldStaticText](HelloWorldStaticText/README.md) The classic first application HelloWorld with StaticText control.

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
