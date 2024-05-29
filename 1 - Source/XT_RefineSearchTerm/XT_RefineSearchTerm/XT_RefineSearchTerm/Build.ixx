export module Build;

import std;

export namespace Build::BuildInfo
{
#ifdef NDEBUG
    const bool releaseMode = true;
#else
    const bool releaseMode = false;
#endif // DEBUG
    const std::wstring author = std::wstring(L"Jamie Sharpe");
    const std::wstring appName = std::wstring(L"XT_RefineSearchTerm");
    const std::wstring appVersion = std::wstring(L"2024.05.29.1004");

    const std::wstring appReleaseMode = releaseMode ? std::wstring(L"Release") : std::wstring(L"Debug");

    const std::wstring title = std::format(L"{} v{} ({} Mode) - Author: {}", appName, appVersion, appReleaseMode, author);
}
