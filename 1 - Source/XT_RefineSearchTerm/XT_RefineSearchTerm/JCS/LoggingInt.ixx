module;

export module Logging;

import std;

namespace JCS::Logging
{
    export enum struct LogLevel
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

	void XWLogOutput(std::wstring message, LogLevel logLevel, bool XWOutput);

	export void Log(const std::wstring& message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true);
	export void Log(const std::string& message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true);
	export void Log(const char* message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true);

    export void SetupFileLogger();

    export void DestroyFileLogger();
}