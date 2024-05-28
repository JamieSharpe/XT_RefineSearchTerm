module;

#include <Windows.h>

export module Miscellaneous;

import XTension;
import Utils;
import std;

/// <summary>
/// Miscellaneous Functions
/// </summary>
export namespace JCS::XWFWrapper::Miscellaneous
{
    VOID XWF_OutputMessage(LPWSTR lpMessage, DWORD nFlags)
    {
        return XWF::Miscellaneous::XWF_OutputMessage(lpMessage, nFlags);
    }

    VOID XWF_OutputMessage(const char* message, DWORD nFlags)
    {
        std::wstring wideMessage = JCS::Utils::StringToWideString(message);
        return JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage(wideMessage.data(), nFlags);
    }

    VOID XWF_OutputMessage(const wchar_t* message, DWORD nFlags)
    {
        return JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage((LPWSTR)message, nFlags);
    }

    VOID XWF_OutputMessage(const std::wstring& message, DWORD nFlags)
    {
        return JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage(message.data(), nFlags);
    }

    INT64 XWF_GetUserInput(LPWSTR lpMessage, LPWSTR lpBuffer, DWORD nBufferLen, DWORD nFlags)
    {
        return XWF::Miscellaneous::XWF_GetUserInput(lpMessage, lpBuffer, nBufferLen, nFlags);
    }

    VOID XWF_ShowProgress(LPWSTR lpCaption, DWORD nFlags)
    {
        return XWF::Miscellaneous::XWF_ShowProgress(lpCaption, nFlags);
    }

    VOID XWF_SetProgressPercentage(DWORD nPercent)
    {
        return XWF::Miscellaneous::XWF_SetProgressPercentage(nPercent);
    }

    VOID XWF_SetProgressDescription(LPWSTR lpStr)
    {
        return XWF::Miscellaneous::XWF_SetProgressDescription(lpStr);
    }

    BOOL XWF_ShouldStop()
    {
        return XWF::Miscellaneous::XWF_ShouldStop();
    }

    VOID XWF_HideProgress()
    {
        return XWF::Miscellaneous::XWF_HideProgress();
    }

    BOOL XWF_ReleaseMem(PVOID lpBuffer)
    {
        return XWF::Miscellaneous::XWF_ReleaseMem(lpBuffer);
    }
}
