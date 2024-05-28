export module Build;

import std;

export namespace Build
{
    class BuildInfo
    {
    public:
#ifdef NDEBUG
        static inline bool releaseMode = true;
#else
        static inline bool releaseMode = false;
#endif // DEBUG
        static inline std::wstring author = std::wstring(L"Jamie Sharpe");
        static inline std::wstring appName = std::wstring(L"XT_RefineSearchTerm");
        static inline std::wstring appVersion = std::wstring(L"2024.05.28.1359");

        static inline std::wstring appReleaseMode = releaseMode ? std::wstring(L"Release") : std::wstring(L"Debug");

        static inline std::wstring title = std::format(L"{} v{} ({} Mode) - Author: {}", appName, appVersion, appReleaseMode, author);
    private:
    };
}
