module;

#include <Windows.h>

export module ItemObject;

import Logging;
import VolumeObject;
import Utils;
import IO;
import Miscellaneous;
import XWUtils;
import XTension;
import VolumeSnapshotItem;
import VolumeSnapshot;
import std;

namespace Models
{
	export class ItemObject
	{
	private:
		std::mutex fileExportLock;
	public:
		LONG ID = -1;
		std::optional<std::wstring> name = std::nullopt;
		std::optional<std::wstring> path = std::nullopt;
		std::optional<std::wstring> fileType = std::nullopt;
		std::optional<INT64> size = std::nullopt;

		std::optional<std::wstring> hashOneValue = std::nullopt;
		std::optional<XWF::Miscellaneous::XW_HashType> hashOneType = std::nullopt;
		std::optional<std::wstring> hashTwoValue = std::nullopt;
		std::optional<XWF::Miscellaneous::XW_HashType> hashTwoType = std::nullopt;

		std::optional<INT64> informationFlags = std::nullopt;
		std::optional<XWF::Miscellaneous::XWF_Item_Info_Deletion_Status> deletionStatus = std::nullopt;

		/// <summary>
		/// The parent volume this item belongs to.
		/// ItemObject has ownership of this item to get data and make changes if required.
		/// </summary>
		std::shared_ptr<Models::VolumeObject> ParentVolume;
		std::optional<HANDLE> ItemHandle = std::nullopt;
		std::optional<HANDLE> parent = std::nullopt;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="nItemID"></param>
		/// <param name="volume"></param>
		/// <param name="initialise"></param>
		ItemObject(LONG nItemID, std::shared_ptr<Models::VolumeObject> volume, bool initialise = true)
		{
			ID = nItemID;
			ParentVolume = volume;

			if (initialise)
			{
				this->name = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemNameOpt(nItemID);
				this->path = JCS::XWFWrapper::VolumeSnapshotItem::GetFilePathOpt(nItemID);
				this->fileType = JCS::XWFWrapper::VolumeSnapshotItem::GetFileType(nItemID);
				this->size = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemSize(nItemID);

				this->informationFlags = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_Flags(nItemID);
				this->deletionStatus = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_DeletionStatus(nItemID);

				GetHashes();
			}
		}

		/// <summary>
		/// Destructor
		/// </summary>
		~ItemObject()
		{
			//JCS::Logging::Log(std::format("Destroyed Item: {}", reinterpret_cast<std::uintptr_t>(ItemHandle.value())), JCS::Logging::LogLevel::Trace);
		}

		void GetHashes()
		{
			hashOneType = JCS::XWFWrapper::VolumeSnapshot::XWF_GetVSProp_GetHashOneType();

			if (hashOneType)
			{
				hashOneValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetHashValueOne(ID, hashOneType.value());
			}

			hashTwoType = JCS::XWFWrapper::VolumeSnapshot::XWF_GetVSProp_GetHashTwoType();

			if (hashTwoType)
			{
				hashTwoValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetHashValueTwo(ID, hashTwoType.value());
			}
		}

		/// <summary>
		/// Check if a file is categorised as multimedia.
		/// </summary>
		/// <returns><c>true</c> if it's a multimedia file, <c>false</c> otherwise.</returns>
		bool IsMultimedia()
		{
			if (!fileType)
			{
				return false;
			}

			if (
				fileType.value() == L"Pictures" ||
				fileType.value() == L"Video" ||
				fileType.value() == L"Audio"
			)
			{
				return true;
			}

			return false;
		}

		/// <summary>
		/// Generic debug logging function.
		/// </summary>
		void Log()
		{
			// Logging Volume Details:
			JCS::Logging::Log("Item Details:");

			JCS::Logging::Log(std::format("\tItem ID:\t\t{}", ID));
			JCS::Logging::Log(std::format(L"\tFile Name:\t{}", JCS::Utils::OptionalValueToString(name)));
			JCS::Logging::Log(std::format(L"\tFile Path:\t\t{}", JCS::Utils::OptionalValueToString(path)));
			JCS::Logging::Log(std::format(L"\tItem Type:\t\t{}", JCS::Utils::OptionalValueToString(fileType)));
			JCS::Logging::Log(std::format(L"\tFile Size:\t\t{}", JCS::Utils::OptionalValueToString(size)));
			JCS::Logging::Log(std::format(L"\tDeletion Status:\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::DeletionStatusToWString(deletionStatus))));

			JCS::Logging::Log(std::format(L"\tHash Type #1:\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::HashTypeToWString(hashOneType))));
			JCS::Logging::Log(std::format(L"\tHash Value #1:\t{}", JCS::Utils::OptionalValueToString(hashOneValue)));

			JCS::Logging::Log(std::format(L"\tHash Type #2:\t{}", JCS::Utils::OptionalValueToString(JCS::XWUtils::HashTypeToWString(hashTwoType))));
			JCS::Logging::Log(std::format(L"\tHash Value #2:\t{}", JCS::Utils::OptionalValueToString(hashTwoValue)));
		}

		/// <summary>
		/// Gets the file size including the slack space.
		/// Note: This may be expensive as it needs to continuously read until the end of the file slack to determine the size.
		/// Calculate the slack size by taking the returned value of this function from <c>this->size</c>.
		/// </summary>
		/// <returns></returns>
		std::optional<INT64> GetFileSizeWithSlack()
		{
			INT64 fileSizeWithSlack = this->size.value();

			if (!this->OpenFile(XWF::IO::XWF_OpenItem_Flag_FileSlack))
			{
				JCS::Logging::Log("Could not open file to get excerpt.", JCS::Logging::LogLevel::Error);
				return 0;
			}

			std::optional<INT64> readBytesCount = 0;
			DWORD readSize = 4096;
			std::unique_ptr<char[]> fileContentBuffer = std::make_unique<char[]>(readSize);

			do
			{
				readBytesCount = JCS::XWFWrapper::IO::XWF_Read(ItemHandle.value(), fileSizeWithSlack, fileContentBuffer.get(), readSize);

				if (!readBytesCount)
				{
					return std::nullopt;
				}

				fileSizeWithSlack += readBytesCount.value();

			} while (readBytesCount != 0);

			this->CloseFile();

			return fileSizeWithSlack;
		}

		/// <summary>
		/// Gets the data from a file at the specified location and length.
		/// Note: No checks are done to ensure the bounds are valid, this should be done on the caller side.
		/// The reasoning is this function accesses the file's content and slack space. Determining the slack
		/// space may be expensive, thus it is down to the caller to perform these checks. Rather than have 
		/// this function always get the slack space size when it's not typically needed.
		/// </summary>
		/// <param name="startOffset"></param>
		/// <param name="readLength"></param>
		/// <returns></returns>
		std::unique_ptr<char[]> GetFileExcerpt(INT64 startOffset, INT64 readLength)
		{
			if (!this->OpenFile(XWF::IO::XWF_OpenItem_Flag_FileSlack))
			{
				JCS::Logging::Log("Could not open file to get excerpt.", JCS::Logging::LogLevel::Error);
				return nullptr;
			}

			std::unique_ptr<char[]> fileContentBuffer = std::make_unique<char[]>(readLength);

			auto readBytesCount = JCS::XWFWrapper::IO::XWF_Read(ItemHandle.value(), startOffset, fileContentBuffer.get(), static_cast<DWORD>(readLength));

			this->CloseFile();

			if (!readBytesCount || readBytesCount.value() == 0)
			{
				return nullptr;
			}

			return fileContentBuffer;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		std::optional<std::wstring> ExportFile()
		{
			const std::lock_guard<std::mutex> lock(fileExportLock);

			JCS::Logging::Log(std::format("Exporting File: {}", std::to_string(ItemObject::ID)), JCS::Logging::LogLevel::Debug);

			if (!this->OpenFile(XWF::IO::XWF_OpenItem_Flag_Content))
			{
				return std::nullopt;;
			}

			DWORD readSize = 4096;
			std::unique_ptr<char[]> fileContentBuffer = std::make_unique<char[]>(readSize);

			std::optional<DWORD> readBytesCount = 0;
			INT64 readOffset = 0;

			std::wstring outputFileName = L"ExampleXWFExport.bin";

			std::ofstream outputFileStream;
			outputFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try
			{
				outputFileStream.open(outputFileName, std::ios::binary);

				do
				{
					readBytesCount = JCS::XWFWrapper::IO::XWF_Read(ItemHandle.value(), readOffset, fileContentBuffer.get(), readSize);

					if (!readBytesCount)
					{
						return std::nullopt;
					}

					outputFileStream.write(fileContentBuffer.get(), readBytesCount.value());

					readOffset += readSize;
				} while (readBytesCount != 0);

				outputFileStream.close();
			}
			catch (std::ofstream::failure e)
			{
				JCS::Logging::Log(std::format("Could not write file. ID: {}", std::to_string(ID)), JCS::Logging::LogLevel::Error);
			}

			this->CloseFile();

			JCS::Logging::Log(std::format("Exported File: {}", ItemObject::ID), JCS::Logging::LogLevel::Debug);

			return outputFileName;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="nFlags"></param>
		/// <returns></returns>
		bool OpenFile(DWORD nFlags)
		{
			JCS::Logging::Log(std::format("Opening Item ID: {}", ID), JCS::Logging::LogLevel::Debug);

			/// TODO: The item handle may need mutex exclusivity.
			if (!ItemHandle || ItemHandle.value() == nullptr)
			{
				std::optional<HANDLE> xwItemHandle = JCS::XWFWrapper::IO::XWF_OpenItem(ParentVolume->hVolume.value(), ID, nFlags);

				if (!xwItemHandle.has_value() || !xwItemHandle.value())
				{
					JCS::Logging::Log(std::format("Could not open the file Item ID: {}", ID), JCS::Logging::LogLevel::Error);

					return false;
				}

				JCS::Logging::Log(std::format("File opened. Item ID: {}", ID), JCS::Logging::LogLevel::Debug);

				ItemHandle = xwItemHandle;
			}
			else
			{
				JCS::Logging::Log(std::format("File is already open. Use 'Models::ItemObject.ItemHandle' on Item ID: {}", ID), JCS::Logging::LogLevel::Debug);
			}

			return true;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool CloseFile()
		{
			JCS::Logging::Log(std::format("Closing Item ID: {}", ID), JCS::Logging::LogLevel::Debug);

			if (!ItemHandle || ItemHandle.value() == nullptr)
			{
				JCS::Logging::Log(std::format("File is already closed. Item ID: {}", ID), JCS::Logging::LogLevel::Debug);
				return true;
			}

			JCS::XWFWrapper::IO::XWF_Close(ItemHandle.value());

			ItemHandle = std::nullopt;

			JCS::Logging::Log(std::format("Closed Item ID: {}", ID), JCS::Logging::LogLevel::Debug);

			return true;
		}
	};
}
