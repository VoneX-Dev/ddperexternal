#include <spoofer.h>
#include <filesystem>
#include <iostream>

void Spoofer::SpoofDDnetFolders() {

    
    WCHAR desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        std::wstring desktopDir(desktopPath);

        if (!std::filesystem::exists(desktopDir + L"\\BackupDDNetFiles"))
            std::filesystem::create_directory(desktopDir + L"\\BackupDDNetFiles");

        std::wcout << L"Spoofing loading..." << std::endl;

        Spoofer::CheckDDNetFolders(desktopDir);
        std::wcout << L"Spoofing DDNet folder done!" << std::endl;
    
        Spoofer::CheckTeeworldsFolders(desktopDir);
        std::wcout << L"Spoofing Teeworlds folder done!" << std::endl;

        std::wcout << L"Spoofed!" << std::endl;

    } else {
        std::wcerr << L"Unable to obtain the path to the user's Desktop folder." << std::endl;
    }
}

void Spoofer::CheckDDNetFolders(std::wstring desktopDir) {

    auto pathDDNet = std::filesystem::temp_directory_path().parent_path().parent_path().parent_path() / L"Roaming\\DDNet";

    if (!std::filesystem::exists(pathDDNet)) {
        std::wcout << L"DDNet folder not found!" << std::endl;
        return;
    }

    std::filesystem::copy(pathDDNet, desktopDir + L"\\BackupDDNetFiles/DDNet", std::filesystem::copy_options::recursive);

    std::wcout << L"Operation completed successfully (DDNet backup)!" << std::endl;

    std::filesystem::remove_all(pathDDNet);
}
void Spoofer::CheckTeeworldsFolders(std::wstring desktopDir){

    auto pathTeeworlds = std::filesystem::temp_directory_path().parent_path().parent_path().parent_path() / "Roaming\\Teeworlds";

    if (!std::filesystem::exists(pathTeeworlds)) { 
        std::wcout << L"Teeworlds folder not found!" << std::endl;
        return;
    }

    std::filesystem::copy(pathTeeworlds, desktopDir + L"\\BackupDDNetFiles/Teeworlds", std::filesystem::copy_options::recursive);

    std::wcout << L"Operation completed successfully (Teeworlds backup)!" << std::endl;

    std::filesystem::remove_all(pathTeeworlds);
}