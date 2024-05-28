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

    /// <summary>
    /// Outputs a message to the XWays 'Messages' window.
    /// </summary>
    /// <param name="message">Message to display.</param>
    /// <param name="logLevel">Logging level.</param>
    /// <param name="XWOutput">Whether to output the message to XWays 'Messages' window.</param>
    void XWLogOutput(std::wstring message, LogLevel logLevel, bool XWOutput);

    /// <summary>
    /// Logs the message to X-Ways output window and to a file.
    /// </summary>
    /// <param name="message">Message to display.</param>
    /// <param name="logLevel">Logging level.</param>
    /// <param name="XWOutput">Whether to output the message to XWays 'Messages' window.</param>
    export void Log(const std::wstring& message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true);
    export void Log(const std::string& message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true);
    export void Log(const char* message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true);

    /// <summary>
    /// Setup a file logger with the name of the current date time.
    /// </summary>
    export void SetupFileLogger();
}
