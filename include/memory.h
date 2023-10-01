#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include <cstdint>
#include <string_view>

class Memory
{
private:
	std::uintptr_t processId = 0;
	void* processHandle = nullptr;

public:


	Memory(const std::string_view processName) noexcept
	{
		::PROCESSENTRY32 entry = { };
		entry.dwSize = sizeof(::PROCESSENTRY32);

		const auto snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		std::string_view entryName; // Declare the entryName variable

		while (::Process32Next(snapShot, &entry))
		{
			// Assuming entry.szExeFile is of type WCHAR *
			WCHAR* wideCharString = entry.szExeFile;

			// Calculate the required buffer size for the converted string
			int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideCharString, -1, nullptr, 0, nullptr, nullptr);

			// Create a buffer to hold the converted string
			std::string narrowCharString(bufferSize, '\0');

			// Perform the conversion
			WideCharToMultiByte(CP_UTF8, 0, wideCharString, -1, &narrowCharString[0], bufferSize, nullptr, nullptr);

			// Now, narrowCharString contains the converted narrow character string
			const char* szExeFile = narrowCharString.c_str();			std::string_view entryName(szExeFile);
			if (processName == entryName)
			{
				processId = entry.th32ProcessID;
				processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
				break;
			}
		}
	}


		// Free handle
	if (snapShot)
		::CloseHandle(snapShot);
	}

	// Destructor that frees the opened handle
	~Memory()
	{
		if (processHandle)
			::CloseHandle(processHandle);
	}

	// Returns the base address of a module by name
	const std::uintptr_t GetModuleAddress(const std::string_view moduleName) const noexcept
	{
		::MODULEENTRY32 entry = { };
		entry.dwSize = sizeof(::MODULEENTRY32);

		const auto snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

		std::uintptr_t result = 0;

		while (::Module32Next(snapShot, &entry))
		{
			if (!moduleName.compare(entry.szModule))
			{
				result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
				break;
			}
		}

		if (snapShot)
			::CloseHandle(snapShot);

		return result;
	}

	// Read process memory
	template <typename T>
	constexpr const T Read(const std::uintptr_t& address) const noexcept
	{
		T value = { };
		::ReadProcessMemory(processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
		return value;
	}

	// Write process memory
	template <typename T>
	constexpr void Write(const std::uintptr_t& address, const T& value) const noexcept
	{
		::WriteProcessMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
	}
};