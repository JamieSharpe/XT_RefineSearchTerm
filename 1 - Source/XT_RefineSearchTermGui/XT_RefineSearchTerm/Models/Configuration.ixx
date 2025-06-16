module;

#include <boost/json.hpp>

export module Configuration;

import Logging;
import std;

export namespace Models::Configuration
{
	std::wstring selectedFilePath = L"";
	std::wstring selectedFolderPath = L"";
	std::wstring userInput = L"";
	std::wstring searchTermRenameSuffix = L"";
	int readPrePostCount = 0;
	double printablePercentRequired = 60;

	void Setup()
	{
		JCS::Logging::Log("Configuration Setup.", JCS::Logging::LogLevel::Debug);

		boost::json::object obj;
		obj["pi"] = 3.141;
	}

}
