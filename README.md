﻿# Win32 ExamplesShows how to use [Win32](https://learn.microsoft.com/en-us/windows/win32/api/) api by proghramming code ([c++17](https://en.cppreference.com/w/)).[![win32](docs/Pictures/win32_header.png)](https://gammasoft71.wixsite.com/gammasoft/win32)## [Win32.System](src/Win32.System/README.md)[Win32.System](src/Win32.System/README.md) contains Win32 console examples (CLI).* [HelloWorlds](src/Win32.System/HelloWorlds/README.md) contains xtd.core "Hello, World!" examples.* [Console](src/Win32.System/Console/README.md) contains console examples.* [Processes](src/Win32.System/Processes/README.md) contains process examples.* [Others](src/Win32.System/Others/README.md) contains others examples.## [Win32.Gui](src/Win32.Gui/README.md)[Win32.Gui](src/Win32.Gui/README.md) contains Win32 controls examples (GUI).* [HelloWorld](src/Win32.Gui/HelloWorlds/README.md) contains Win32 controls "Hello, World!" examples.* [Applications](src/Win32.Gui/Console/README.md) contains application examples.* [Dialogs](src/Win32.Gui/Console/README.md) contains dialog examples.* [Windows](src/Win32.Gui/Windows/README.md) contains windows examples.* [MenusAndToolbars](src/Win32.Gui/MenusAndToolbars/README.md) contains dialog examples.* [Containers](src/Win32.Gui/Containers/README.md) contains containers examples.* [Controls](src/Win32.Gui/Containers/README.md) contains common controls examples.* [Components](src/Win32.Gui/Containers/README.md) contains components examples.* [Events](src/Win32.Gui/Evnets/README.md) contains evenrs examples.* [Others](src/Win32.Gui/Others/README.md) contains others examples.## [Win32.UnitTest](./Win32.UnitTest/README.md)[Win32.UnitTest](./Win32.UnitTest/README.md) contains Win32 UnitTest examples.## Download``` shellgit clone https://github.com/gammasoft71/Win32Examples Win32Examples```## Generate and buildTo build this project, open "Console" and type following lines:``` shellmkdir build && cd buildcmake .. start Win32.Examples.sln```Select any project and type Ctrl+F5 to build and run it.## RemarksThis project run only on Windows with [Visual Studio](https://www.visualstudio.com) and [CMake](https://cmake.org).