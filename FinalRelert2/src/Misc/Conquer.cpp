#include <Conquer.h>

int Calculate_CRC(void* buffer, int length)
{
	return CRCEngine()(buffer, length);
}

RawFileClass LogFile;
void Log_Prepare(const char* const dir, const char* const logname)
{
	if (dir == nullptr || logname == nullptr)
		return;

	// Prepare directory
	CreateDirectory(dir, nullptr);

	// Prepare log file
	char path[_MAX_PATH];
	_makepath(path, "", dir, logname, ".log");

	LogFile.Open(path, FILE_ACCESS_WRITE);
}

void Log_Begin()
{
	Log_Prepare("Debug", "DEBUG");
}

void Log_String(const char* const format, ...)
{
	char buffer[0x400];

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	if (LogFile.Is_Open())
		LogFile.Write(buffer, strlen(buffer));

#ifndef NDEBUG
	OutputDebugString(buffer);
#endif
}

void Log_Close()
{
	if (LogFile.Is_Open())
	{
		unsigned int dt = LogFile.Get_Date_Time();

		char drive[_MAX_PATH];
		char dir[_MAX_PATH];
		char filename[_MAX_PATH];
		char ext[_MAX_PATH];
		char buffer[_MAX_PATH];
		_splitpath(LogFile.File_Name(), drive, dir, nullptr, ext);
		sprintf(filename, "debug-%04d%02d%02d-%02d%02d%02d",
			YEAR(dt), MONTH(dt), DAY(dt), HOUR(dt), MINUTE(dt), SECOND(dt));
		_makepath(buffer, drive, dir, filename, ".log");

		LogFile.Close();

		MoveFile(LogFile.File_Name(), buffer);
	}
}

HANDLE AppMutex;
bool Setup_Mutex()
{
	AppMutex = CreateMutex(nullptr, FALSE, "22457198-8780-45D2-BD23-D7736C257F47");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hwnd = FindWindow("22457198-8780-45D2-BD23-D7736C257F47", nullptr);
		if (hwnd != NULL)
		{
			SetForegroundWindow(hwnd);
			ShowWindow(hwnd, SW_RESTORE);
		}
		if (AppMutex != NULL)
		{
			CloseHandle(AppMutex);
			AppMutex = NULL;
		}
		Log_String("RA2MD is already running...Bail!\n");
		return false;
	}
	Log_String("Create AppMutex okay.\n");
	return true;
}

void Release_Mutex()
{
	if (AppMutex != NULL)
	{
		CloseHandle(AppMutex);
		AppMutex = NULL;
	}
}
