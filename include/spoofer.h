#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>
#include <shlobj.h>

class Spoofer {
    public:
        static void SpoofDDnetFolders();
        static void CheckDDNetFolders(std::wstring desktopDir);
        static void CheckTeeworldsFolders(std::wstring desktopDir);
        // tabahkar
};