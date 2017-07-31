//Author: War_L0k_01                        |
//Date: 30.07.17                            |
//Organization:                             |
//   ________   _______      __       __ 	|
//	/        | /       \    /  \     /  |   |
//  $$$$$$$$/  $$$$$$$  |   $$  \   /$$ |   |
//     $$ |    $$ |  $$ |   $$$  \ /$$$ |   |
//     $$ |    $$ |  $$ |   $$$$  /$$$$ |   |
//     $$ |    $$ |  $$ |   $$ $$ $$/$$ |   |
//     $$ | __ $$ |__$$ |__ $$ |$$$/ $$ |   |
//     $$ |/  |$$    $$//  |$$ | $/  $$ |   |
//     $$/ $$/ $$$$$$$/ $$/ $$/      $$/    |
//_________________________________________ |

#include <iostream>
#include <Windows.h>

int main() {

	//path to our Dll
	LPCSTR DllPath = "";

	// Open a handle to target process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 000);

	//Allocate the memory of the dll path in the target process
	//length of the path string
	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1,
		MEM_COMMIT, PAGE_READWRITE);

	//Write the path to the adress we just allocated
	//in the target process
	WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath,
		strlen(DllPath) + 1, 0);

	//Create a RemoteThread in the target process
	//Calls LoadlibraryA as our dllpath as an argument -> program loads our dll
	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
			"LoadLibraryA"), pDllPath, 0, 0);

	// Wait for the execution of our loader thread to finish
	WaitForSingleObject(hLoadThread, INFINITE);

	std::cout "Dll path allocated at" << pDllPath << std::endl;
	std::cin.get();

	// Free the memory allocated for our dll path
	VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) +1, MEM_RELEASE);

	return 0;
}