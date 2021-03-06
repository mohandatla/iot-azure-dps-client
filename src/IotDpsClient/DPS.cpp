/*
Copyright 2017 Microsoft
Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "stdafx.h"
#include "DPSService.h"

#define SERVICE_NAME             L"IotDpsClient"

void DoDpsWork();
void ResetDps();

[Platform::MTAThread]
int wmain(int argc, wchar_t *argv[])
{
    TRACE("Entering wmain...");

    if ((argc > 1) && ((*argv[1] == L'-' || (*argv[1] == L'/'))))
    {
        if (_wcsicmp(L"install", argv[1] + 1) == 0)
        {
            DPSService::Install(SERVICE_NAME);
        }
        else if (_wcsicmp(L"remove", argv[1] + 1) == 0)
        {
            DPSService::Uninstall(SERVICE_NAME);
        }
        else if (_wcsicmp(L"debug", argv[1] + 1) == 0)
        {
            DoDpsWork();
        }
        else if (_wcsicmp(L"resetdps", argv[1] + 1) == 0)
        {
            ResetDps();
        }
    }
    else
    {
        TRACE(L"Parameters:");
        TRACE(L" -install  to install the service.");
        TRACE(L" -remove   to remove the service.");
        TRACE(L"");
        TRACE(L"Running service...");

        DPSService service(SERVICE_NAME);
        DPSService::Run(service);
    }

    TRACE("Exiting wmain.");

    return 0;
}
