#include "pipeManager.h"
#include <Windows.h>
#include <iostream>
#include <winsock.h>

HANDLE hPipe;
DWORD dwRead;
DWORD dwWritten;
struct Vector3 {
	float x;
	float y;
	float z;
};
char networkBuffer[KILOBYTE];
void instantiateServer() {
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
		1,
		KILOBYTE * 16,
		KILOBYTE * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		PIPE_ACCEPT_REMOTE_CLIENTS);
	
}
void instantiateClient() {
	char szPath[128] = "";
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	gethostname(szPath, sizeof(szPath));
	char temp[100] = "\\\\%s\\pipe\\Pipe";
	char pipeName[200];
	sprintf(pipeName, temp, szPath);
	WSACleanup();
	puts(pipeName);
	hPipe = CreateFile(TEXT(pipeName),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	printf("%d", GetLastError());
}
bool readNetwork() {
	if (ReadFile(hPipe, networkBuffer, KILOBYTE, &dwRead, NULL) != FALSE) {
		return 1;
	}
	return 0;
}
void writeNetwork() {
	WriteFile(hPipe,
		networkBuffer,
		KILOBYTE,   // = length of string + terminating '\0' !!!
		&dwWritten,
		NULL);
}
void disconnect() {
	DisconnectNamedPipe(hPipe);
}
char* getBuffer() {
	return networkBuffer;
}