module;

#include <boost/json.hpp>

export module Configuration;

import Logging;
import std;

export namespace Models::Configuration
{
	bool configured = false;
	double printablePercentRequired = 90;
	int hitContextLength = 30;
	bool appendNumbersToSearchTerm = true;
	std::wstring searchTermRenameSuffix = L" - RST";

	void Setup()
	{
		JCS::Logging::Log("Configuration Setup.", JCS::Logging::LogLevel::Debug);

		boost::json::object obj;
		obj["pi"] = 3.141;
	}

	void LogConfiguration()
	{
		JCS::Logging::Log(std::format(L"Configured: {}", configured));
		JCS::Logging::Log(std::format(L"Printable Percent Required: {}", printablePercentRequired));
		JCS::Logging::Log(std::format(L"Hit Context Length: {}", hitContextLength));
		JCS::Logging::Log(std::format(L"Append Numbers to Search Term: {}", appendNumbersToSearchTerm));
		JCS::Logging::Log(std::format(L"Search Term Rename Suffix: {}", searchTermRenameSuffix));
	}

}
