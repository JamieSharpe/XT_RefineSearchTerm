module;

#include <Windows.h>

export module VolumeObject;

import EvidenceObject;
import Miscellaneous;
import XWUtils;
import IO;
import Utils;
import XTension;
import Logging;
import std;

namespace Models
{
	export class VolumeObject
	{
	private:
	public:
		/// <summary>
		/// Handle to the volume object.
		/// </summary>
		std::optional<HANDLE> hVolume = std::nullopt;

		/// <summary>
		/// Raw handle to the Evidence Object.
		/// </summary>
		std::optional<HANDLE> hEvidence = std::nullopt;

		/// <summary>
		/// A populated Evidence Object model created from them evidence handle.
		/// </summary>
		std::optional<std::unique_ptr<Models::EvidenceObject>> evidenceObject = std::nullopt;

		//std::unique_ptr<ItemObject> currentItem;

		std::optional<std::wstring> volumeName1 = std::nullopt;
		std::optional<std::wstring> volumeName2 = std::nullopt;
		std::optional<std::wstring> volumeName3 = std::nullopt;

		std::optional<XWF::Miscellaneous::XW_FileSystemType> fileSystem = std::nullopt;
		std::optional<DWORD> bytesPerSector = std::nullopt;
		std::optional<DWORD> sectorsPerCluster = std::nullopt;
		std::optional<INT64> clusterCount = std::nullopt;
		std::optional<INT64> firstClusterSectorNumber = std::nullopt;

		std::optional<INT64> physicalSize = std::nullopt;
		std::optional<INT64> logicalSize = std::nullopt;
		std::optional<INT64> validDataLength = std::nullopt;
		std::optional<DWORD> attributes = std::nullopt;
		std::optional<std::wstring> filePath = std::nullopt;
		std::optional<std::wstring> pureName = std::nullopt;
		std::optional<HANDLE> parentVolume = std::nullopt;
		std::optional<WORD> dataWindow = std::nullopt;

		/// <summary>
		/// Constructor for a VolumeObject.
		/// </summary>
		/// <param name="hVolume">Handle to the volume. Required.</param>
		/// <param name="hEvidence">Handle to the evidence object which holds the volume. Required.</param>
		/// <param name="initialise">True: Slow, but initialise the object by collecting all the information about it. False: Fast, no meta data is initialised.</param>
		VolumeObject(std::optional<HANDLE> hVolume, std::optional<HANDLE> hEvidence, bool initialise = true)
		{
			this->hVolume = hVolume;
			this->hEvidence = hEvidence;

			volumeName1 = std::nullopt;
			volumeName2 = std::nullopt;
			volumeName3 = std::nullopt;

			fileSystem = std::nullopt;
			bytesPerSector = std::nullopt;
			sectorsPerCluster = std::nullopt;
			clusterCount = std::nullopt;
			firstClusterSectorNumber = std::nullopt;

			physicalSize = std::nullopt;
			logicalSize = std::nullopt;
			validDataLength = std::nullopt;
			attributes = std::nullopt;
			filePath = std::nullopt;
			pureName = std::nullopt;
			parentVolume = std::nullopt;
			dataWindow = std::nullopt;

			if (initialise)
			{
				JCS::Logging::Log("Initialising Volume Object.", JCS::Logging::LogLevel::Debug);
				Initialise();
			}
			else
			{
				JCS::Logging::Log("Volume object is initialised to default values. Be aware some may be invalid.", JCS::Logging::LogLevel::Warning);
			}
		}

		void Log()
		{
			// Logging Volume Details:
			JCS::Logging::Log("Volume Details:");

			// Volume Name
			JCS::Logging::Log(std::format(L"\tName #1:\t\t\t{}", JCS::Utils::OptionalValueToString(volumeName1)));
			JCS::Logging::Log(std::format(L"\tName #2:\t\t\t{}", JCS::Utils::OptionalValueToString(volumeName2)));
			JCS::Logging::Log(std::format(L"\tName #3:\t\t\t{}", JCS::Utils::OptionalValueToString(volumeName3)));

			// Info
			JCS::Logging::Log(std::format(L"\tFile System:\t\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::FileSystemTypeToWString(fileSystem))));
			JCS::Logging::Log(std::format(L"\tBytes Per Sector:\t\t{}", JCS::Utils::OptionalValueToString(bytesPerSector)));
			JCS::Logging::Log(std::format(L"\tSectors Per Cluster:\t\t{}", JCS::Utils::OptionalValueToString(sectorsPerCluster)));
			JCS::Logging::Log(std::format(L"\tCluster Count:\t\t{}", JCS::Utils::OptionalValueToString(clusterCount)));
			JCS::Logging::Log(std::format(L"\tFirst Cluster Sector Number:\t{}", JCS::Utils::OptionalValueToString(firstClusterSectorNumber)));

			JCS::Logging::Log(std::format(L"\tPhysical Size:\t\t{}", JCS::Utils::OptionalValueToString(physicalSize)));
			JCS::Logging::Log(std::format(L"\tLogical Size:\t\t{}", JCS::Utils::OptionalValueToString(logicalSize)));
			JCS::Logging::Log(std::format(L"\tValid Data Length:\t\t{}", JCS::Utils::OptionalValueToString(validDataLength)));
			JCS::Logging::Log(std::format(L"\tAttributes:\t\t\t{}", JCS::Utils::OptionalValueToString(attributes)));
			JCS::Logging::Log(std::format(L"\tFile Path:\t\t\t{}", JCS::Utils::OptionalValueToString(filePath)));
			JCS::Logging::Log(std::format(L"\tPure Name:\t\t{}", JCS::Utils::OptionalValueToString(pureName)));
			JCS::Logging::Log(std::format(L"\tParent Volume:\t\t{}", JCS::Utils::OptionalValueToString(parentVolume)));
			JCS::Logging::Log(std::format(L"\tData Window:\t\t{}", JCS::Utils::OptionalValueToString(dataWindow)));
		}

		/// <summary>
		/// Initialise the fields for Volume and Names and Information.
		/// Warning: This may be expensive.
		/// </summary>
		void Initialise()
		{
			//this->evidenceObject = std::make_unique<Models::EvidenceObject>(this->hEvidence);

			InitialiseVolumeNames();
			InitialiseVolumeInformation();
			physicalSize = JCS::XWFWrapper::IO::XWF_GetProp_PhysicalSize(hVolume);
			logicalSize = JCS::XWFWrapper::IO::XWF_GetProp_LogicalSize(hVolume);
			validDataLength = JCS::XWFWrapper::IO::XWF_GetProp_ValidDataLength(hVolume);
			attributes = JCS::XWFWrapper::IO::XWF_GetProp_FileAttributes(hVolume);
			filePath = JCS::XWFWrapper::IO::XWF_GetProp_FilePathOrName(hVolume);
			pureName = JCS::XWFWrapper::IO::XWF_GetProp_PureName(hVolume);
			parentVolume = JCS::XWFWrapper::IO::XWF_GetProp_ParentVolume(hVolume);
			dataWindow = JCS::XWFWrapper::IO::XWF_GetProp_DataWindow(hVolume);
		}

		/// <summary>
		/// Initialise all the volume name fields:
		///		- Generic to specific.
		/// </summary>
		void InitialiseVolumeNames()
		{
			volumeName1 = JCS::XWFWrapper::IO::GetVolumeName(hVolume, XWF::IO::XWF_GetVolumeName_FullName);
			volumeName2 = JCS::XWFWrapper::IO::GetVolumeName(hVolume, XWF::IO::XWF_GetVolumeName_Simple);
			volumeName3 = JCS::XWFWrapper::IO::GetVolumeName(hVolume, XWF::IO::XWF_GetVolumeName_Minified);
		}

		/// <summary>
		/// Initialise all the volume information fields:
		///		- File System
		///		- Bytes Per Sector
		///		- Sectors Per Cluster
		///		- Cluster Count
		///		- First Cluster Sector Number
		/// </summary>
		void InitialiseVolumeInformation()
		{
			std::unique_ptr<LONG> lpFileSystem = std::make_unique<LONG>(0L);
			std::unique_ptr<DWORD> lpBytesPerSector = std::make_unique<DWORD>(0UL);
			std::unique_ptr<DWORD> lpSectorsPerCluster = std::make_unique<DWORD>(0UL);
			std::unique_ptr<INT64> lpClusterCount = std::make_unique<INT64>(0LL);
			std::unique_ptr<INT64> lpFirstClusterSectorNo = std::make_unique<INT64>(0LL);

			bool getVolumeInformationSuccess = JCS::XWFWrapper::IO::XWF_GetVolumeInformation(hVolume, lpFileSystem.get(), lpBytesPerSector.get(), lpSectorsPerCluster.get(), lpClusterCount.get(), lpFirstClusterSectorNo.get()).value_or(false);

			if (getVolumeInformationSuccess)
			{
				fileSystem = static_cast<XWF::Miscellaneous::XW_FileSystemType>(*lpFileSystem);
				bytesPerSector = *lpBytesPerSector;
				sectorsPerCluster = *lpSectorsPerCluster;
				clusterCount = *lpClusterCount;
				firstClusterSectorNumber = *lpFirstClusterSectorNo;
			}
			else
			{
				fileSystem = std::nullopt;
				bytesPerSector = std::nullopt;
				sectorsPerCluster = std::nullopt;
				clusterCount = std::nullopt;
				firstClusterSectorNumber = std::nullopt;
			}
		}
	};
}
