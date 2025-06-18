module;

#include <Windows.h>

export module Miscellaneous;

import Logging;
import Utils;
import XTension;
import std;

/// <summary>
/// Miscellaneous Functions
/// </summary>
export namespace JCS::XWFWrapper::Miscellaneous
{
	VOID XWF_OutputMessage(LPWSTR lpMessage, DWORD nFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_OutputMessage, L"XWF_OutputMessage"))
		{
			return;
		}

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

	std::optional<INT64> XWF_GetUserInput(LPWSTR lpMessage, LPWSTR lpBuffer, DWORD nBufferLen, DWORD nFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_GetUserInput, L"XWF_GetUserInput"))
		{
			return std::nullopt;
		}

		return XWF::Miscellaneous::XWF_GetUserInput(lpMessage, lpBuffer, nBufferLen, nFlags);
	}

	VOID XWF_ShowProgress(LPWSTR lpCaption, DWORD nFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_ShowProgress, L"XWF_ShowProgress"))
		{
			return;
		}

		return XWF::Miscellaneous::XWF_ShowProgress(lpCaption, nFlags);
	}

	VOID XWF_SetProgressPercentage(DWORD nPercent)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_SetProgressPercentage, L"XWF_SetProgressPercentage"))
		{
			return;
		}

		return XWF::Miscellaneous::XWF_SetProgressPercentage(nPercent);
	}

	VOID XWF_SetProgressDescription(LPWSTR lpStr)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_SetProgressDescription, L"XWF_SetProgressDescription"))
		{
			return;
		}

		return XWF::Miscellaneous::XWF_SetProgressDescription(lpStr);
	}

	std::optional<BOOL> XWF_ShouldStop()
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_ShouldStop, L"XWF_ShouldStop"))
		{
			return std::nullopt;
		}

		return XWF::Miscellaneous::XWF_ShouldStop();
	}

	VOID XWF_HideProgress()
	{
		return XWF::Miscellaneous::XWF_HideProgress();
	}

	std::optional<BOOL> XWF_ReleaseMem(PVOID lpBuffer)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Miscellaneous::XWF_ReleaseMem, L"XWF_ReleaseMem"))
		{
			return std::nullopt;
		}

		return XWF::Miscellaneous::XWF_ReleaseMem(lpBuffer);
	}
}
