// SteamLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <string>

std::string GetWindowTitle(HWND hwnd)
{
	char wndTitle[256];
	GetWindowTextA(hwnd, wndTitle, sizeof(wndTitle));
	return std::string(wndTitle);
}

int WindowOpen(HWND hwnd)
{
	char wndTitle[256];
	return GetWindowTextA(hwnd, wndTitle, 256) > 0 ? 1 : 0;
}

int main(int argc, char *argv[])
{
	std::cout << "Steam Launcher\n";

	if (argc <= 1) {
		std::cout << std::endl << "Usage: SteamLauncher.exe APPID" << std::endl << "Example: `SteamLauncher.exe 628800` to launch Super Hydorah";
		std::cout << std::endl << "Do note that this program expects steam.exe to be in PATH";
		return 0;
	}

	std::string command = "steam.exe steam://rungameid/";
	command += std::string(argv[1]);

	std::cout << std::endl << command << std::endl;
	system(command.c_str());

	HWND gameHwnd = nullptr;
    
	while (gameHwnd == nullptr) {
		HWND hwnd = GetForegroundWindow();
		std::string windowTitle = GetWindowTitle(hwnd);
		std::cout << std::endl << hwnd << " - " << windowTitle;

		// If Steam is nowhere in the title, assume its the game
		// TODO: There are probably way better ways of detecting this?
		if (windowTitle.find("Steam") == std::string::npos) {
			gameHwnd = hwnd;
		}
	}

	std::cout << std::endl << "Game Window found! Waiting for the game to close...";

	// TODO: Use WinEvents and register for EVENT_OBJECT_DESTROY events for this instead of this proof-of-concept approach?
	while (WindowOpen(gameHwnd) == 1) {
		Sleep(100);
	}

	return 0;
}
