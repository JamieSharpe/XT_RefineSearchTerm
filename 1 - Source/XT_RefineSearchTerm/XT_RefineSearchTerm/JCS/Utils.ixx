module;

#include <Windows.h>

export module Utils;

import Logging;
import Build;
import XTension;
import std;

namespace JCS::Utils
{
	std::wstring nullOutputString = std::wstring(L"[NULL]");

	/// <summary>
	/// Given a collection of function meta data, logs the found and not found functions.
	/// </summary>
	/// <param name="functionMetaData"></param>
	export void LogExportedFunctions(const std::vector <XWF::Other::XWFFunctionMetaData>& functionMetaData)
	{
		JCS::Logging::Log("Functions Exported by X-Ways:", JCS::Logging::LogLevel::Trace);
		for (auto functionMetaDataFound : std::ranges::views::filter(functionMetaData, [](auto functionMetaData)
		{
			return functionMetaData.found;
		}))
		{
			JCS::Logging::Log(std::format(L"\t{}", functionMetaDataFound.functionName), JCS::Logging::LogLevel::Trace);
		};

		JCS::Logging::Log("Functions Not Exported by X-Ways:", JCS::Logging::LogLevel::Trace);
		for (auto functionMetaDataNotFound : std::ranges::views::filter(functionMetaData, [](auto functionMetaData)
		{
			return !functionMetaData.found;
		}))
		{
			JCS::Logging::Log(std::format(L"\t{}", functionMetaDataNotFound.functionName), JCS::Logging::LogLevel::Trace);
		};
	}

	/// <summary>
	/// Check if the passed in function pointer exists.
	/// </summary>
	/// <param name="function_ptr">Pointer to a function, typically one exported by X-Ways.</param>
	/// <param name="function_name">Function name to display in the error message.</param>
	/// <returns></returns>
	export bool FunctionPointerIsNull(void* function_ptr, std::wstring function_name)
	{
		if (function_ptr == nullptr)
		{
			JCS::Logging::Log(std::format(L"Function pointer to '{}' is null.", function_name), JCS::Logging::LogLevel::Critical, false);
			return true;
		}

		return false;
	}

	/// <summary>
	/// Converts a byte pointer to user friendly hex.
	/// </summary>
	/// <param name="data"></param>
	/// <param name="len"></param>
	/// <returns></returns>
	export std::wstring BytesToHex(BYTE* data, INT64 len)
	{
		if (data == nullptr || len == 0)
		{
			return L"";
		}

		std::wstringstream ss;
		ss << std::hex;

		for (int i(0); i < len; ++i)
		{
			ss << std::setw(2) << std::setfill(L'0') << (int)data[i];
		}

		std::wstring hash_value = ss.str();

		std::transform(hash_value.begin(), hash_value.end(), hash_value.begin(), ::towupper);

		return hash_value;
	}

	/// <summary>
	/// Converts a wchar_t* to a std::wstring.
	/// </summary>
	/// <param name="chars"></param>
	/// <returns></returns>
	export std::wstring WCharPointerToWString(const wchar_t* chars)
	{
		if (chars == nullptr || chars[0] == '\0')
		{
			return std::wstring();
		}

		return std::wstring(chars);
	}

	/// <summary>
	/// Convert std::string to std::wstring in UTF8 codec.
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	export std::wstring s2ws(const std::string& str, int codePage = CP_UTF8)
	{
		int convertResult = MultiByteToWideChar(codePage, 0, str.data(), -1, NULL, 0);
		if (convertResult == 0)
		{
			JCS::Logging::Log("Conversion of string failed.", JCS::Logging::LogLevel::Error);
			return std::wstring();
		}

		std::unique_ptr<wchar_t[]> wideChars = std::make_unique<wchar_t[]>(convertResult);
		convertResult = MultiByteToWideChar(codePage, 0, str.data(), -1, wideChars.get(), convertResult);

		if (convertResult == 0)
		{
			JCS::Logging::Log("Placing converted string into wstring failed.", JCS::Logging::LogLevel::Error);
			return std::wstring();
		}

		std::wstring wideString = WCharPointerToWString(wideChars.get());
		return wideString;
	}

	/// <summary>
	/// Convert std::string to std::wstring in UTF8 codec.
	/// </summary>
	/// <param name="wstr"></param>
	/// <returns></returns>
	export std::string ws2s(const std::wstring& wstr)
	{
		std::vector<char> buf(wstr.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());

		return std::string(buf.data(), buf.size());
	}

	/// <summary>
	/// Converts binary data to the bes representation of a string.
	/// </summary>
	/// <param name="str"></param>
	/// <param name="codePage"></param>
	/// <returns></returns>
	export std::wstring b2ws(const char* str, int codePage)
	{
		JCS::Logging::Log("Attempting to convert byte array to wide string:", JCS::Logging::LogLevel::Trace);
		JCS::Logging::Log(std::format("{}", codePage), JCS::Logging::LogLevel::Trace);
		JCS::Logging::Log(str, JCS::Logging::LogLevel::Trace);

		JCS::Logging::Log("", JCS::Logging::LogLevel::Trace);
		int convertResult = MultiByteToWideChar(codePage, 0, str, -1, NULL, 0);
		if (convertResult == 0)
		{
			JCS::Logging::Log("Conversion of string failed.", JCS::Logging::LogLevel::Error);
			return std::wstring();
		}

		std::unique_ptr<wchar_t[]> wideChars = std::make_unique<wchar_t[]>(convertResult);
		convertResult = MultiByteToWideChar(codePage, 0, str, -1, wideChars.get(), convertResult);

		if (convertResult == 0)
		{
			JCS::Logging::Log("Placing converted string into wstring failed.", JCS::Logging::LogLevel::Error);
			return std::wstring();
		}

		std::wstring wideString = WCharPointerToWString(wideChars.get());
		return wideString;
	}

	/// <summary>
	/// Converts a char* to a std::wstring.
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	export std::wstring StringToWideString(const char* c)
	{
		if (c == nullptr || c[0] == '\0')
		{
			return std::wstring();
		}

		std::string s = std::string(c);
		return s2ws(s);
	}

	/// <summary>
	/// Converts a LPWSTR to a std::wstring.
	/// </summary>
	/// <param name="lpWideString">Pointer to Wide String.</param>
	/// <returns>std::wstring or empty string.</returns>
	export std::wstring LPWStrToWString(LPWSTR lpWideString)
	{
		if (lpWideString == nullptr || (INT64)lpWideString < 0)
		{
			return std::wstring();
		}

		return std::wstring(lpWideString);
	}

	/// <summary>
	/// Gets the current date time as a string.
	/// Note: there are no seconds returned.
	/// </summary>
	/// <returns></returns>
	export std::string GetTimeAsString(bool fileNameFriendly = false)
	{
		const auto now = std::chrono::system_clock::now();

		auto t = std::format("{:%Y-%m-%d} ", now);

		if (fileNameFriendly)
		{
			t += std::format("{:%H-%M}-", now);
		}
		else
		{
			t += std::format("{:%H:%M}:", now);
		}
		t += std::format("{:%S}", now).substr(0, 6);
		t += std::format("{:%z}", now);

		return t;
	}

	/// <summary>
	/// Convert
	/// </summary>
	/// <param name="fileTime"></param>
	/// <returns></returns>
	export SYSTEMTIME Int64FileTimeToSystemTime(INT64 fileTime)
	{
		SYSTEMTIME systemTimeStructure{};

		if (fileTime <= 0)
		{
			systemTimeStructure.wYear = 1601;
		}
		else
		{
			FILETIME f{};
			*(INT64*)&f = fileTime;
			FileTimeToSystemTime(&f, &systemTimeStructure);
		}

		return systemTimeStructure;
	}

	/// <summary>
	/// Converts a 'SYSTEMTIME' to a string.
	/// </summary>
	/// <returns></returns>
	export std::optional<std::wstring> SystemTimeToWString(std::optional<SYSTEMTIME> systemTime)
	{
		if (!systemTime)
		{
			return std::nullopt;
		}

		if (systemTime.value().wYear == 1601 || systemTime.value().wYear == 0)
		{
			JCS::Logging::Log("Invalid date.", JCS::Logging::LogLevel::Warning);
			return std::nullopt;
		}

		std::wstring wsSystemTime = std::format(L"{}-{}-{} {}:{}:{}", systemTime.value().wYear, systemTime.value().wMonth, systemTime.value().wDay, systemTime.value().wHour, systemTime.value().wMinute, systemTime.value().wSecond);
		return wsSystemTime;
	}

	/// <summary>
	/// https://stackoverflow.com/a/38220498
	/// Method to handle catch all (...) exceptions.
	/// See how it's used in new.cpp
	/// </summary>
	/// <param name="exceptionPtr">Pointer to an exception.</param>
	/// <returns>true if an exception was handled (read logged), false if there were no exceptions.</returns>
	export bool HandleExceptionPtr(std::exception_ptr exceptionPtr)
	{
		try
		{
			if (exceptionPtr)
			{
				std::rethrow_exception(exceptionPtr);
			}
		}
		catch (const std::exception& e)
		{
			std::wstring message = std::format(L"FATAL ERROR: {}", JCS::Utils::StringToWideString(e.what()));
			std::wcout << message << std::endl;
			JCS::Logging::Log(message, JCS::Logging::LogLevel::Critical);
			return true;
		}

		return false;
	}

	/// <summary>
	/// Converts an <c>std::optional</c> value to a friendly string.
	/// 
	/// This function is only for logging/debug purposes.
	/// 
	/// Do not use this function for actually testing a value of an object. You should explicitly use the <c>T.has_value()</c>!
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="t"></param>
	/// <returns></returns>

	export template<typename T>
		std::wstring OptionalValueToString(const std::optional<T>& t)
	{
		std::wstring valueString;
		if (t)
		{
			valueString = std::to_wstring(t.value());
		}
		else
		{
			valueString = JCS::Utils::nullOutputString;
		}
		return valueString;
	}


	/// <summary>
	/// Same as <c>OptionalValueToString(const std::optional<T>& t)</c> but specifically for <c>std::wstring</c> overloading.
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	export std::wstring OptionalValueToString(const std::optional<std::wstring>& t)
	{
		return t.value_or(JCS::Utils::nullOutputString);
	}

	/// <summary>
	/// Same as <c>OptionalValueToString(const std::optional<T>& t)</c> but specifically for <c>void*</c> overloading.
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	export std::wstring OptionalValueToString(const std::optional<void*>& t)
	{
		if (t)
		{
			std::optional<INT64> valOpt = reinterpret_cast<INT64>(t.value());
			return JCS::Utils::OptionalValueToString(valOpt);
		}

		return JCS::Utils::nullOutputString;
	}

	std::wstring replaceAll(std::wstring const& original, std::wstring const& before, std::wstring const& after)
	{
		std::wstring retval;
		std::wstring::const_iterator end = original.end();
		std::wstring::const_iterator current = original.begin();
		std::wstring::const_iterator next =
			std::search(current, end, before.begin(), before.end());
		while (next != end)
		{
			retval.append(current, next);
			retval.append(after);
			current = next + before.size();
			next = std::search(current, end, before.begin(), before.end());
		}
		retval.append(current, next);
		return retval;
	}

	/// <summary>
	/// Reads the entire content of a file and returns it as a wstring.
	/// </summary>
	/// <param name="filePath">The path to the file.</param>
	/// <returns>File content as wstring, or empty if error.</returns>
	export std::wstring ReadFileToWString(const std::wstring& filePath)
	{
		std::filesystem::path absolutePath = std::filesystem::absolute(filePath);
		JCS::Logging::Log(std::format(L"Reading contents of file: {}", absolutePath.wstring()), JCS::Logging::LogLevel::Trace);

		if (absolutePath.empty())
		{
			JCS::Logging::Log(L"File path is empty.", JCS::Logging::LogLevel::Error);
			return L"";
		}

		if (!std::filesystem::exists(absolutePath))
		{
			JCS::Logging::Log(std::format(L"File does not exist: {}", absolutePath.wstring()), JCS::Logging::LogLevel::Error);
			return L"";
		}

		std::wifstream file(absolutePath, std::ios::binary);
		if (!file)
		{
			JCS::Logging::Log(std::format(L"Failed to open file: {}", absolutePath.wstring()), JCS::Logging::LogLevel::Error);
			return L"";
		}

		std::wstringstream wss;
		wss << file.rdbuf();
		return wss.str();
	}

	export std::wstring GetHelpText()
	{
		std::wstring helpTextFileContent = ReadFileToWString(L"./Resources/Help.rtf");

		helpTextFileContent = replaceAll(helpTextFileContent, L"$build_info:appTitle", Build::BuildInfo::appTitle);
		helpTextFileContent = replaceAll(helpTextFileContent, L"$build_info:appUrl", Build::BuildInfo::appUrl);
		helpTextFileContent = replaceAll(helpTextFileContent, L"$build_info:authorUrl", Build::BuildInfo::authorUrl);
		helpTextFileContent = replaceAll(helpTextFileContent, L"$build_info:author", Build::BuildInfo::author);

		return helpTextFileContent;
	}
}
