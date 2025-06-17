module;

/// Support wide characters for spdlog.
#ifndef SPDLOG_WCHAR_TO_UTF8_SUPPORT
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#endif // !SPDLOG_WCHAR_TO_UTF8_SUPPORT

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

module Logging;

import Build;
import Utils;
import Miscellaneous;
import XTension;
import ItemObject;
import std;

namespace JCS::Logging
{
	std::shared_ptr<spdlog::logger> file_logger = nullptr;

	enum struct LogLevel
	{
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Critical
	};

	std::wstring XWLogGenerateMessage(std::wstring message, LogLevel logLevel)
	{
		std::wstring logLevelString = std::wstring();
		switch (logLevel)
		{
			case JCS::Logging::LogLevel::Trace:
				logLevelString = L"[TRACE      ]";
				break;
			case JCS::Logging::LogLevel::Debug:
				logLevelString = L"[DEBUG     ]";
				break;
			case JCS::Logging::LogLevel::Info:
				logLevelString = L"[INFO          ]";
				break;
			case JCS::Logging::LogLevel::Warning:
				logLevelString = L"[WARNING]";
				break;
			case JCS::Logging::LogLevel::Error:
				logLevelString = L"[ERROR     ]";
				break;
			case JCS::Logging::LogLevel::Critical:
				logLevelString = L"[CRITICAL  ]";
				break;
			default:
				logLevelString = L"[INFO         ]";
				break;
		}

		std::wstring dateTime = JCS::Utils::s2ws(JCS::Utils::GetTimeAsString());
		std::wstring formattedMessage = std::format(L"[{}] [{}] {} {}", dateTime, Build::BuildInfo::appName, logLevelString, message);

		return formattedMessage;
	}

	void LogToStandardOutput(std::wstring message)
	{
		std::wcout << message << std::endl;
	}

	/// <summary>
	/// Outputs a message to the XWays 'Messages' window.
	/// </summary>
	/// <param name="message">Message to display.</param>
	/// <param name="logLevel">Logging level.</param>
	/// <param name="XWOutput">Whether to output the message to XWays 'Messages' window.</param>
	void XWLogOutput(std::wstring message, LogLevel logLevel, bool XWOutput)
	{
		if (Build::BuildInfo::executableMode)
		{
			return; // Do not output to X-Ways in executable mode.
		}

		if (!XWOutput || (Build::BuildInfo::releaseMode && (int)logLevel < (int)spdlog::get_level()))
		{
			return;
		}

		switch (logLevel)
		{
			case (LogLevel::Trace):
			case (LogLevel::Debug):
				return;
				break;
			default:
				break;
		}

		JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage(message, XWF::Miscellaneous::XWF_OutputMessage_Flag_Default);
	}

	/// <summary>
	/// Logs the message to X-Ways output window and to a file.
	/// </summary>
	/// <param name="message">Message to display.</param>
	/// <param name="logLevel">Logging level.</param>
	/// <param name="XWOutput">Whether to output the message to XWays 'Messages' window.</param>
	void Log(const std::wstring& message, JCS::Logging::LogLevel logLevel, bool XWOutput)
	{
		if (Build::BuildInfo::releaseMode && (int)logLevel < (int)spdlog::get_level())
		{
			return;
		}

		switch (logLevel)
		{
			case JCS::Logging::LogLevel::Trace:
				JCS::Logging::file_logger->trace(message);
				break;
			case JCS::Logging::LogLevel::Debug:
				JCS::Logging::file_logger->debug(message);
				break;
			case JCS::Logging::LogLevel::Info:
				JCS::Logging::file_logger->info(message);
				break;
			case JCS::Logging::LogLevel::Warning:
				JCS::Logging::file_logger->warn(message);
				break;
			case JCS::Logging::LogLevel::Error:
				JCS::Logging::file_logger->error(message);
				break;
			case JCS::Logging::LogLevel::Critical:
				JCS::Logging::file_logger->critical(message);
				break;
			default:
				JCS::Logging::file_logger->info(message);
				break;
		}

		JCS::Logging::file_logger->flush();

		std::wstring logMessage = XWLogGenerateMessage(message, logLevel);
		JCS::Logging::LogToStandardOutput(logMessage);
		JCS::Logging::XWLogOutput(logMessage, logLevel, XWOutput);

	}

	/// <summary>
	/// Logs the message to X-Ways output window and to a file.
	/// </summary>
	/// <param name="message">Message to display.</param>
	/// <param name="logLevel">Logging level.</param>
	/// <param name="XWOutput">Whether to output the message to XWays 'Messages' window.</param>
	void Log(const std::string& message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true)
	{
		std::wstring wMessage = JCS::Utils::s2ws(message);
		JCS::Logging::Log(wMessage, logLevel, XWOutput);
	}

	/// <summary>
	/// Logs the message to X-Ways output window and to a file.
	/// </summary>
	/// <param name="message">Message to display.</param>
	/// <param name="logLevel">Logging level.</param>
	/// <param name="XWOutput">Whether to output the message to XWays 'Messages' window.</param>
	void Log(const char* message, JCS::Logging::LogLevel logLevel = JCS::Logging::LogLevel::Info, bool XWOutput = true)
	{
		std::wstring wMessage = JCS::Utils::StringToWideString(message);
		JCS::Logging::Log(wMessage, logLevel, XWOutput);
	}

	/// <summary>
	/// Setup a file logger with the name of the current date time.
	/// </summary>
	void SetupFileLogger()
	{
		try
		{
			if (JCS::Logging::file_logger)
			{
				JCS::Logging::Log("File logging has already been setup.");
				return;
			}

			std::string datetime = JCS::Utils::GetTimeAsString(true);
			std::string file_name = std::format("logs/{} - {}.log", JCS::Utils::ws2s(Build::BuildInfo::appName), datetime);

			JCS::Logging::file_logger = spdlog::basic_logger_mt("file_logger", file_name);

			if (Build::BuildInfo::releaseMode)
			{
				spdlog::set_level(spdlog::level::info);
			}
			else
			{
				spdlog::set_level(spdlog::level::trace);
			}

			JCS::Logging::Log("Logging Setup");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage("Log init failed:", XWF::Miscellaneous::XWF_OutputMessage_Flag_Default);
			JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage("ERROR MESSAGE:", XWF::Miscellaneous::XWF_OutputMessage_Flag_Default);
			JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage(ex.what(), XWF::Miscellaneous::XWF_OutputMessage_Flag_Default);
		}
	}

	void DestroyFileLogger()
	{
		if (JCS::Logging::file_logger)
		{
			JCS::Logging::Log("Destroying file logger.");
			JCS::Logging::file_logger->flush();

			spdlog::drop("file_logger");
			JCS::Logging::file_logger.reset();
		}
		else
		{
			JCS::Logging::Log("File logger was not initialized, nothing to destroy.");
		}
		spdlog::shutdown();
	}
}
