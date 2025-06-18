module;

#include <Windows.h>

export module EvidenceObject;

import Logging;
import Utils;
import Miscellaneous;
import XWUtils;
import std;
import EvidenceAndCase;
import XTension;

/// Functions of Interest:
///		- INT64 XWF_GetEvObjProp(HANDLE hEvidence, DWORD nPropType, PVOID lpBuffer);
///		- LPVOID XWF_GetEvObjReportTableAssocs(HANDLE hEvidence, LONG nFlags, PLONG lpValue);
namespace Models
{
	/// <summary>
	/// EvidenceObject
	/// </summary>
	export class EvidenceObject
	{
	private:
	public:
		/// <summary>
		/// 
		/// </summary>
		std::optional<HANDLE> hEvidence = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<WORD> number = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<DWORD> ID = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<DWORD> parentID = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<WORD> IDShort = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> title = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> titleExtended = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> titleExtendedAbbreviated = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> internalName = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> description = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> examinerComments = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> internallyUsedDirectory = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> outputDirectory = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<INT64> sizeInBytes = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<DWORD> volumeSnapshotID = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<DWORD> volumeSnapshotFileCount = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<INT64> flags = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<XWF::Miscellaneous::XW_FileSystemType> fileSystem = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<XWF::Miscellaneous::XW_HashType> hashOneType = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> hashOneValue = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<XWF::Miscellaneous::XW_HashType> hashTwoType = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> hashTwoValue = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<SYSTEMTIME> creationTime = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> creationTimeFriendly = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<SYSTEMTIME> modifiedTime = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<std::wstring> modifiedTimeFriendly = std::nullopt;

		/// <summary>
		/// 
		/// </summary>
		std::optional<WORD> dataWindow = std::nullopt;

		/// <summary>
		/// Constructor of an Evidence Object Model. defaults to get all the property values as well.
		/// </summary>
		/// <param name="hEvidence"></param>
		/// <param name="initialise">If <c>true</c> then populate all the property values (may be expensive). False, leave them all as <c>std::nullopt</c>.</param>
		EvidenceObject(std::optional<HANDLE> hEvidence, bool initialise = true)
		{
			this->hEvidence = hEvidence;

			ID = std::nullopt;
			parentID = std::nullopt;
			IDShort = std::nullopt;
			number = std::nullopt;
			fileSystem = std::nullopt;
			creationTime = std::nullopt;
			modifiedTime = std::nullopt;
			dataWindow = std::nullopt;
			flags = std::nullopt;
			hashOneType = std::nullopt;
			hashOneValue = std::nullopt;
			hashTwoType = std::nullopt;
			hashTwoValue = std::nullopt;
			sizeInBytes = std::nullopt;
			volumeSnapshotFileCount = std::nullopt;
			volumeSnapshotID = std::nullopt;

			if (initialise)
			{
				JCS::Logging::Log("Initialising Evidence object.", JCS::Logging::LogLevel::Debug);
				Initialise();
			}
			else
			{
				JCS::Logging::Log("Evidence object is initialised to default values. Be aware some may be invalid.", JCS::Logging::LogLevel::Warning);
			}
		}

		/// <summary>
		/// 
		/// </summary>
		~EvidenceObject()
		{
		}

		/// <summary>
		/// Populates all of the associated properties of an Evidence Object by calling each of its respective XWF_* function.
		/// This may be expensive, but provides a complete object to perform actions on.
		/// </summary>
		void Initialise()
		{
			ID = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_EvidenceObjectID(hEvidence);
			parentID = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_EvidenceObjectParentID(hEvidence);
			IDShort = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_EvidenceObjectShortID(hEvidence);

			title = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_EvidenceObjectTitle(hEvidence);
			titleExtended = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_EvidenceObjectTitle(hEvidence);
			titleExtendedAbbreviated = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_EvidenceObjectExtendedAbbreviatedTitle(hEvidence);
			description = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_Description(hEvidence);
			internalName = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_InternalName(hEvidence);
			examinerComments = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_ExaminerComments(hEvidence);

			internallyUsedDirectory = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_InternallyUsedDirectory(hEvidence);
			outputDirectory = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_OutputDirectory(hEvidence);

			volumeSnapshotID = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_VolumeSnapshotID(hEvidence);
			volumeSnapshotFileCount = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_VolumeSnapshotFileCount(hEvidence);

			creationTime = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_CreationTime(hEvidence);
			creationTimeFriendly = JCS::Utils::SystemTimeToWString(creationTime);

			modifiedTime = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_ModifiedTime(hEvidence);
			modifiedTimeFriendly = JCS::Utils::SystemTimeToWString(modifiedTime);

			dataWindow = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_DataWindow(hEvidence);
			GetHashes();

			if (parentID && parentID.value() == 0)
			{
				GetHashes();
			}
			else
			{
				JCS::Logging::Log("Could not get the hashes of a Volume, need an evidence object.", JCS::Logging::LogLevel::Warning);
			}

			sizeInBytes = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_SizeInBytes(hEvidence);

			std::optional<INT64> fileSystemIdentifier = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_FileSystemIdentifier(hEvidence);
			if (fileSystemIdentifier)
			{
				fileSystem = static_cast<XWF::Miscellaneous::XW_FileSystemType>(fileSystemIdentifier.value());
			}
		}

		/// <summary>
		/// Note during testing:
		///     The hashes are only populated when running the XTensions directly within X-Ways.
		///     Using the CLI X-Ways, the hashes are not populated.
		/// may need to open the evidence object
		///  HANDLE XWF_OpenEvObj(HANDLE hEvidence,DWORD nFlags);
		/// 
		/// Scratch that, you don't need to open the evidence object.
		/// This can work if the case is closed with the evidence (read E01) object is open and not the volumes.
		/// </summary>
		void GetHashes()
		{
			std::optional<DWORD> hashOneTypeRaw = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_HashOneType(hEvidence);
			hashOneValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_HashOneValue(hEvidence);

			if (hashOneTypeRaw && hashOneValue)
			{
				hashOneType = static_cast<XWF::Miscellaneous::XW_HashType>(hashOneTypeRaw.value());
			}
			else
			{
				JCS::Logging::Log("Hash Type One is not set/invalid.", JCS::Logging::LogLevel::Warning);
			}

			std::optional<DWORD> hashTwoTypeRaw = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_HashTwoType(hEvidence);
			hashTwoValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp_HashTwoValue(hEvidence);

			if (hashTwoTypeRaw && hashTwoValue)
			{
				hashTwoType = static_cast<XWF::Miscellaneous::XW_HashType>(hashTwoTypeRaw.value());
			}
			else
			{
				JCS::Logging::Log("Hash Type Two is not set/invalid.", JCS::Logging::LogLevel::Warning);
			}
		}

		void Log()
		{
			JCS::Logging::Log("Evidence Details:");
			JCS::Logging::Log(std::format(L"\tID:\t\t\t{}", JCS::Utils::OptionalValueToString(ID)));

			if (parentID)
			{
				if (parentID.value() == 0)
				{
					JCS::Logging::Log(std::format(L"\tParent ID:\t\t\t{} (This is a root evidence object)", JCS::Utils::OptionalValueToString(parentID)));
				}
				else
				{
					JCS::Logging::Log(std::format(L"\tParent ID:\t\t\t{}", JCS::Utils::OptionalValueToString(parentID)));
				}
			}
			else
			{
				JCS::Logging::Log(std::format(L"\tParent ID:\t\t\t{}", JCS::Utils::OptionalValueToString(parentID)), JCS::Logging::LogLevel::Warning);
			}

			if (IDShort)
			{
				JCS::Logging::Log(std::format(L"\tID Short:\t\t\t{}", JCS::Utils::OptionalValueToString(IDShort)));
			}
			else
			{
				JCS::Logging::Log(std::format(L"\tID Short:\t\t\t{}", JCS::Utils::OptionalValueToString(IDShort)), JCS::Logging::LogLevel::Warning);
			}

			JCS::Logging::Log(std::format(L"\tTitle:\t\t\t{}", JCS::Utils::OptionalValueToString(title)));
			JCS::Logging::Log(std::format(L"\tTitle Extended:\t\t{}", JCS::Utils::OptionalValueToString(titleExtended)));
			JCS::Logging::Log(std::format(L"\tTitle Abbreviated:\t\t{}", JCS::Utils::OptionalValueToString(titleExtendedAbbreviated)));
			JCS::Logging::Log(std::format(L"\tInternal Name:\t\t{}", JCS::Utils::OptionalValueToString(internalName)));
			JCS::Logging::Log(std::format(L"\tCreation Time:\t\t{}", JCS::Utils::OptionalValueToString(creationTimeFriendly)));
			JCS::Logging::Log(std::format(L"\tModified Time:\t\t{}", JCS::Utils::OptionalValueToString(modifiedTimeFriendly)));
			JCS::Logging::Log(std::format(L"\tDescription:\t\t{}", JCS::Utils::OptionalValueToString(description)));
			JCS::Logging::Log(std::format(L"\tExaminer's Comments:\t{}", JCS::Utils::OptionalValueToString(examinerComments)));

			JCS::Logging::Log(std::format(L"\tInternally Used Directory:\t{}", JCS::Utils::OptionalValueToString(internallyUsedDirectory)));
			JCS::Logging::Log(std::format(L"\tOutput Directory:\t\t{}", JCS::Utils::OptionalValueToString(outputDirectory)));

			JCS::Logging::Log(std::format(L"\tVolume Snapshot ID:\t\t{}", JCS::Utils::OptionalValueToString(volumeSnapshotID)));
			JCS::Logging::Log(std::format(L"\tVolume Snapshot File Count:\t{}", JCS::Utils::OptionalValueToString(volumeSnapshotFileCount)));

			JCS::Logging::Log(std::format(L"\tSize in Bytes:\t\t{}", JCS::Utils::OptionalValueToString(sizeInBytes)));

			if (fileSystem)
			{
				JCS::Logging::Log(std::format(L"\tFile System:\t\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::FileSystemTypeToWString(fileSystem))));
			}


			if (dataWindow == 0)
			{
				JCS::Logging::Log(std::format(L"\tData Window:\t\t{} (Data window is not open/invalid.)", JCS::Utils::OptionalValueToString(dataWindow)), JCS::Logging::LogLevel::Warning);
			}
			else
			{
				JCS::Logging::Log(std::format(L"\tData Window:\t\t{}", JCS::Utils::OptionalValueToString(dataWindow)));
			}

			JCS::Logging::Log(std::format(L"\tHash Type #1:\t\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::HashTypeToWString(hashOneType))));
			JCS::Logging::Log(std::format(L"\tHash Value #1:\t\t{}", JCS::Utils::OptionalValueToString(hashOneValue)));

			JCS::Logging::Log(std::format(L"\tHash Type #2:\t\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::HashTypeToWString(hashTwoType))));
			JCS::Logging::Log(std::format(L"\tHash Value #2:\t\t{}", JCS::Utils::OptionalValueToString(hashTwoValue)));
		}
	};
}
