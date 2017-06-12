#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

bool TaskExecuteAndWait(std::string execpath, std::string *pOutput)
{
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES securityAttr;
	HANDLE inputPipe, outputPipe;
	std::string output;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&securityAttr, sizeof(securityAttr));
	securityAttr.nLength = sizeof(securityAttr);
	securityAttr.bInheritHandle = TRUE;
	int len;
	int slength = (int)execpath.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, execpath.c_str(), slength, nullptr, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, execpath.c_str(), slength, buf, len);
	if (usePipes) {


		::CreatePipe(&inputPipe, &outputPipe, &securityAttr, 0);

		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdInput = NULL;
		si.hStdOutput = outputPipe;
		si.hStdError = outputPipe;
	}

	if (!CreateProcess(NULL,   // No module name (use command line)
		buf,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		TRUE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		delete[] buf;
		DWORD le = GetLastError();
		std::cout << "CreateProcess Failed. Error code:" << le << std::endl;
		
		return "-1";
	}

	
	WaitForSingleObject(pi.hProcess, INFINITE);

	if (usePipes)
	{

		CloseHandle(outputPipe);

		const int BUFFER_SIZE = 200;
		DWORD NumberOfBytesRead = 0;
		do
		{
			char buf[BUFFER_SIZE+1] = "";
		
			if (::ReadFile(inputPipe, buf, BUFFER_SIZE, &NumberOfBytesRead, 0))
			{
				if (NumberOfBytesRead == 0)
					break;

				buf[NumberOfBytesRead] = '\0';

				output += std::string(buf);
			}

		} while (NumberOfBytesRead != 0);

		CloseHandle(inputPipe);

	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	delete[] buf;
	output.erase(std::remove_if(output.begin(), output.end(), [](char c) { return std::isspace(c); }), output.end());
	return output;
}

