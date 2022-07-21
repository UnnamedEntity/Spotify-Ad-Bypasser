#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <filesystem>
#include <string.h>
#include <Lmcons.h>

void restart_spotify()
{
    system("taskkill /F /IM spotify.exe");
    system("cd %~dp0");
    system("start Spotify");
    system("cls");
	
    INPUT ip;
	
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; 
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = VK_MEDIA_PLAY_PAUSE; 
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));
}

int main()
{
	SetConsoleTitleA("Auto spotify restarter");

	std::cout << "Spotify ad bypasser" << std::endl;
	std::cout << "This restarts spotify on an ad, which causes the ad to be skipped" << std::endl;



	while (true) //loop
	{
		static HWND spotify_hwnd = nullptr;

		static float last_hwnd_time = 0.f;

		if ((!spotify_hwnd || spotify_hwnd == INVALID_HANDLE_VALUE)) {
			for (HWND hwnd = GetTopWindow(0); hwnd; hwnd = GetWindow(hwnd, GW_HWNDNEXT)) {

				if (!(IsWindowVisible)(hwnd))
					continue;

				int length = (GetWindowTextLengthW)(hwnd);
				if (length == 0)
					continue;

				WCHAR filename[300];
				DWORD pid;
				(GetWindowThreadProcessId)(hwnd, &pid);

				const auto spotify_handle = (OpenProcess)(PROCESS_QUERY_INFORMATION, FALSE, pid);
				(K32GetModuleFileNameExW)(spotify_handle, nullptr, filename, 300);

				std::wstring sane_filename{ filename };

				(CloseHandle)(spotify_handle);

				if (sane_filename.find((L"Spotify.exe")) != std::string::npos)
					spotify_hwnd = hwnd;
			}
		}
		else if (spotify_hwnd && spotify_hwnd != INVALID_HANDLE_VALUE) {
			WCHAR title[300];

			if (!(GetWindowTextW)(spotify_hwnd, title, 300))
				spotify_hwnd = nullptr;
			else 
			{
				std::wstring sane_title{ title };

				if (sane_title.find((L"Spotify")) == std::string::npos && sane_title.find((L"-")) == std::string::npos)
				{
					restart_spotify();
				}
			}
		}
	}
}
