# ConHost/OpenConsole

All source code in this repository comes from microsoft/terminal, except for:

+ Code in the generated folder which is generated by code generators.
+ Some manually downloaded third-party libraries in the oss directory.
+ Code marked with 'WinUI3 Terminal Patch.'

This repository only includes enough code to build ConHost/OpenConsole.

Roadmap:

1. Fix the code and synchronize it to upstream
2. Fix code that relies on the UNICODE macro, change it to use wide characters unconditionally, and synchronize it to upstream
3. Add exe resource files to implement all functionalities of conhost
4. Replace outdated functions and improve performance
