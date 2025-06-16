module;

#include <Windows.h>

export module CaseObject;

import Utils;
import Logging;
import EvidenceAndCase;
import std;

namespace Models
{
	export class CaseObject
	{
	private:
	public:
		/// <summary>
		/// Unique 64-bit ID of the case (v19.7 and later).
		/// -1 is invalid.
		/// </summary>
		std::optional<INT64> ID = std::nullopt;
		/// <summary>
		/// Case title.
		/// </summary>
		std::optional<std::wstring> title = std::nullopt;
		/// <summary>
		/// Creation time (v19.7 and later).
		/// </summary>
		std::optional<SYSTEMTIME> creationTime = std::nullopt;
		std::optional<std::wstring> creationTimeFriendly = std::nullopt;
		/// <summary>
		/// Examiner name
		/// </summary>
		std::optional<std::wstring> examiner = std::nullopt;
		/// <summary>
		/// '.xfc' Case file path.
		/// </summary>
		std::optional<std::wstring> caseFilePath = std::nullopt;
		/// <summary>
		/// Case directory.
		/// </summary>
		std::optional<std::wstring> caseDirectory = std::nullopt;

		CaseObject(bool initialise = true)
		{
			if (initialise)
			{
				JCS::Logging::Log("Initialising Case Object.");
				Initialise();
			}
		}

		void Initialise()
		{
			this->ID = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp_ID();

			this->creationTime = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp_Creation();

			if (creationTime.has_value())
			{
				this->creationTimeFriendly = JCS::Utils::SystemTimeToWString(creationTime.value());
			}

			this->title = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp_Title();

			this->caseFilePath = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp_CaseFilePath();

			this->caseDirectory = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp_CaseDirPath();

			this->examiner = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp_Examiner();
		}

		void Log()
		{
			// Logging Case Details:
			JCS::Logging::Log("Case Details:");

			// Case Details:
			JCS::Logging::Log(std::format(L"\tID:\t\t{}", JCS::Utils::OptionalValueToString(ID)));
			JCS::Logging::Log(std::format(L"\tCreation Time:\t{}", JCS::Utils::OptionalValueToString(creationTimeFriendly)));
			JCS::Logging::Log(std::format(L"\tCase Title:\t{}", JCS::Utils::OptionalValueToString(title)));
			JCS::Logging::Log(std::format(L"\tCase File:\t\t{}", JCS::Utils::OptionalValueToString(caseFilePath)));
			JCS::Logging::Log(std::format(L"\tCase Directory:\t{}", JCS::Utils::OptionalValueToString(caseDirectory)));
			JCS::Logging::Log(std::format(L"\tCase Examiner:\t{}", JCS::Utils::OptionalValueToString(examiner)));
		}
	};
}
