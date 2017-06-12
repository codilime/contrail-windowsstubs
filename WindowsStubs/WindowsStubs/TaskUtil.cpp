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
    bool retval = true;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&securityAttr, sizeof(securityAttr));
    securityAttr.nLength = sizeof(securityAttr);
    securityAttr.bInheritHandle = TRUE;
    int len;
    int slength = (int)execpath.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, execpath.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, execpath.c_str(), slength, buf, len);
    if (pOutput)
    {
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
        DWORD le = GetLastError();
        std::cout << "CreateProcess Failed. Error code:" << le << std::endl;
        retval = false;
        goto cleanup;
    }
    
    if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED)
    {
        DWORD le = GetLastError();
        std::cout << "WaitForSingleObject Failed. Error code:" << le << std::endl;
        retval = false;
        goto cleanup;
    }

    if (pOutput)
    {
        CloseHandle(outputPipe);
        const int BUFFER_SIZE = 200;
        DWORD nNumberOfBytesToRead = 0;
        do
        {
            char buf[BUFFER_SIZE + 1];
        
            if (::ReadFile(inputPipe, buf, BUFFER_SIZE, &nNumberOfBytesToRead, 0))
            {
                if (nNumberOfBytesToRead == 0)
                    break;

                buf[nNumberOfBytesToRead] = '\0';

                *pOutput += buf;
            }

        } while (nNumberOfBytesToRead != 0);
        pOutput->erase(std::remove_if(pOutput->begin(), pOutput->end(), [](char c) { return std::isspace(c); }), pOutput->end());
        CloseHandle(inputPipe);
    }

cleanup: //goto is very commonly used in Microsoft sample code.to make code look cleaner and avoid too many ifs.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    delete[] buf;
    return true;
}

