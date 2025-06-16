module;

#include <Windows.h>

export module Build;

import std;

export namespace Build::BuildInfo
{
	HINSTANCE XW_HANDLEMain = nullptr;

#ifdef XT_RELEASE
	const bool releaseMode = true;
#else
	const bool releaseMode = false;
#endif // XT_RELEASE

#ifdef XT_DEBUG_EXE
	const bool executableMode = true;
#else
	const bool executableMode = false;
#endif // XT_DEBUG_EXE

	const std::wstring author = std::wstring(L"Jamie Sharpe");
	const std::wstring appName = std::wstring(L"XT_RefineSearchTerm");
	const std::wstring appVersion = std::wstring(L"2025.06.16.2136");
	const std::wstring appReleaseMode = releaseMode ? std::wstring(L"Release") : std::wstring(L"Debug");
	const std::wstring title = std::format(L"{} v{} ({} Mode)", appName, appVersion, appReleaseMode);
	const std::wstring titleExtended = std::format(L"{} v{} ({} Mode) - Author: {}", appName, appVersion, appReleaseMode, author);
}
