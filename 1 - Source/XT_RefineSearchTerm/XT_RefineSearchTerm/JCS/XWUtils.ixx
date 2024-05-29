module;

#include <Windows.h>

export module XWUtils;

import XTension;
import Miscellaneous;
import Utils;
import std;

namespace JCS::XWUtils
{
    export std::optional<std::wstring> DeletionStatusToWString(std::optional<XWF::Miscellaneous::XWF_Item_Info_Deletion_Status> deletionStatus)
    {
        if (!deletionStatus)
        {
            return std::nullopt;
        }

        switch (deletionStatus.value())
        {
            case XWF::Miscellaneous::XWF_Item_Info_Deletion_Status::Existing:
                return L"Existing";
                break;
            case XWF::Miscellaneous::XWF_Item_Info_Deletion_Status::PreviouslyExistingPossiblyRecoverable:
                return L"Previously Existing; Possibly Recoverable";
                break;
            case XWF::Miscellaneous::XWF_Item_Info_Deletion_Status::PreviouslyExistingFirstClusterOverwritten:
                return L"Previously Existing; First Cluster Overwritten";
                break;
            case XWF::Miscellaneous::XWF_Item_Info_Deletion_Status::RenamedOrMovedPossiblyRecoverable:
                return L"Renamed or Moved; Possibly Recoverable";
                break;
            case XWF::Miscellaneous::XWF_Item_Info_Deletion_Status::RenamedOrMovedFirstClusterOverwritten:
                return L"Renamed or Moved; First Cluster Overwritten";
                break;
            case XWF::Miscellaneous::XWF_Item_Info_Deletion_Status::CarvedFile:
                return L"Carved File";
                break;
            default:
                return L"Undefined";
                break;
        }
    }
    /// <summary>
    /// Converts an X-Ways hash type to a user friendly string.
    /// </summary>
    /// <param name="hashType">X-Ways hash type.</param>
    /// <returns>User friendly string of the hash type.</returns>
    export std::optional<std::wstring> HashTypeToWString(std::optional<XWF::Miscellaneous::XW_HashType> hashType)
    {
        if (!hashType)
        {
            return std::nullopt;
        }

        switch (hashType.value())
        {
            case XWF::Miscellaneous::XW_HashType::undefined:
                return L"Undefined";
                break;
            case XWF::Miscellaneous::XW_HashType::CS8:
                return L"CS8";
                break;
            case XWF::Miscellaneous::XW_HashType::CS16:
                return L"CS16";
                break;
            case XWF::Miscellaneous::XW_HashType::CS32:
                return L"CS32";
                break;
            case XWF::Miscellaneous::XW_HashType::CS64:
                return L"CS64";
                break;
            case XWF::Miscellaneous::XW_HashType::CRC16:
                return L"CRC16";
                break;
            case XWF::Miscellaneous::XW_HashType::CRC32:
                return L"CRC32";
                break;
            case XWF::Miscellaneous::XW_HashType::MD5:
                return L"MD5";
                break;
            case XWF::Miscellaneous::XW_HashType::SHA1:
                return L"SHA-1";
                break;
            case XWF::Miscellaneous::XW_HashType::SHA256:
                return L"SHA-256";
                break;
            case XWF::Miscellaneous::XW_HashType::RIPEMD128:
                return L"RIPEMD-128";
                break;
            case XWF::Miscellaneous::XW_HashType::RIPEMD160:
                return L"RIPEMD-160";
                break;
            case XWF::Miscellaneous::XW_HashType::MD4:
                return L"MD4";
                break;
            case XWF::Miscellaneous::XW_HashType::ED2K:
                return L"ED2K";
                break;
            case XWF::Miscellaneous::XW_HashType::Adler32:
                return L"Adler 32";
                break;
            case XWF::Miscellaneous::XW_HashType::TigerTreeHash:
                return L"Tiger Tree Hash (TTH)";
                break;
            case XWF::Miscellaneous::XW_HashType::Tiger128:
                return L"Tiger-128";
                break;
            case XWF::Miscellaneous::XW_HashType::Tiger160:
                return L"Tiger-160";
                break;
            case XWF::Miscellaneous::XW_HashType::Tiger192:
                return L"Tiger-192";
                break;
            case XWF::Miscellaneous::XW_HashType::MD5folded:
                return L"MD5 Folded";
                break;
            default:
                return L"Undefined";
                break;
        }
    }

    /// <summary>
    /// Given a hash type, will return the standard byte count of that algorithm
    /// </summary>
    /// <param name="hashType"></param>
    /// <returns></returns>
    export int HashTypeSize(XWF::Miscellaneous::XW_HashType hashType)
    {
        switch (hashType)
        {
            case XWF::Miscellaneous::XW_HashType::undefined:
                return 0;
                break;
            case XWF::Miscellaneous::XW_HashType::CS8:
                return 1;
                break;
            case XWF::Miscellaneous::XW_HashType::CS16:
                return 2;
                break;
            case XWF::Miscellaneous::XW_HashType::CS32:
                return 4;
                break;
            case XWF::Miscellaneous::XW_HashType::CS64:
                return 8;
                break;
            case XWF::Miscellaneous::XW_HashType::CRC16:
                return 2;
                break;
            case XWF::Miscellaneous::XW_HashType::CRC32:
                return 4;
                break;
            case XWF::Miscellaneous::XW_HashType::MD5:
                return 16;
                break;
            case XWF::Miscellaneous::XW_HashType::SHA1:
                return 20;
                break;
            case XWF::Miscellaneous::XW_HashType::SHA256:
                return 32;
                break;
            case XWF::Miscellaneous::XW_HashType::RIPEMD128:
                return 16;
                break;
            case XWF::Miscellaneous::XW_HashType::RIPEMD160:
                return 20;
                break;
            case XWF::Miscellaneous::XW_HashType::MD4:
                return 16;
                break;
            case XWF::Miscellaneous::XW_HashType::ED2K:
                return 16;
                break;
            case XWF::Miscellaneous::XW_HashType::Adler32:
                return 4;
                break;
            case XWF::Miscellaneous::XW_HashType::TigerTreeHash:
                return 128;
                break;
            case XWF::Miscellaneous::XW_HashType::Tiger128:
                return 16;
                break;
            case XWF::Miscellaneous::XW_HashType::Tiger160:
                return 20;
                break;
            case XWF::Miscellaneous::XW_HashType::Tiger192:
                return 24;
                break;
            case XWF::Miscellaneous::XW_HashType::MD5folded:
                return 16;
                break;
            default:
                return 0;
                break;
        }
    }

    /// <summary>
    /// Convert an X-Ways file system type to a user friendly string.
    /// </summary>
    /// <param name="fileSystemType">X-Ways File System Type.</param>
    /// <returns>User friendly File System Type.</returns>
    export std::optional<std::wstring> FileSystemTypeToWString(std::optional<XWF::Miscellaneous::XW_FileSystemType> fileSystemType)
    {
        if (!fileSystemType)
        {
            return std::nullopt;
        }

        switch (fileSystemType.value())
        {
            case XWF::Miscellaneous::XW_FileSystemType::UnknownFS:
                return L"Unknown";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::FAT12:
                return L"FAT 12";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::FAT16:
                return L"FAT 16";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::FAT32:
                return L"FAT 32";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::exFAT:
                return L"exFAT";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::UDF:
                return L"UDF";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::XWFS:
                return L"XWFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::OSDirectoryListing:
                return L"OS Directory Listing";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::CDFS:
                return L"CDFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::MainMemory:
                return L"Main Memory";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::ReFS:
                return L"ReFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::BitLocker:
                return L"BitLocker";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::APFS:
                return L"APFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::NTFS:
                return L"NTFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::Ext2:
                return L"Ext 2";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::Ext3:
                return L"Ext 3";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::ReiserFS:
                return L"Reiser FS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::Reiser4:
                return L"Reiser 4";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::Ext4:
                return L"Ext 4";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::JFS:
                return L"JFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::XFS:
                return L"XFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::UFS:
                return L"UFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::HFS:
                return L"HFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::HFSPlus:
                return L"HFSPlus";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::NTFSBitLocker:
                return L"NTFS BitLocker";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::PhysicalDiskPotentiallyPartitioned:
                return L"Physical Disk (Potentially Partitioned)";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::Btrfs:
                return L"BtrFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::QNX:
                return L"QNX";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::LDMMetadata:
                return L"LDM Meta Data";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::LDMData:
                return L"LDM Data";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::LinuxSwap:
                return L"Linux Swap";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::LVM2Container:
                return L"LVM2 Container";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::MDRAIDHeader:
                return L"MD RAID Header";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::StoragePoolContainer:
                return L"Storage Pool Container";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::WindowsPhoneContainer:
                return L"Windows Phont Container";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::VMFS:
                return L"VMFS";
                break;
            case XWF::Miscellaneous::XW_FileSystemType::ZFS:
                return L"ZFS";
                break;
            default:
                return L"Unknown";
                break;
        }
    }

    /// <summary>
    /// Convert an X-Ways operation type to a user friendly string.
    /// </summary>
    /// <param name="nOpType">X-Ways operation type.</param>
    /// <returns>User friendly operation type.</returns>
    export std::wstring XTensionOperationTypeToWString(DWORD nOpType)
    {
        switch (nOpType)
        {
            case XWF::Ordinary::XT_Action_MainMenu:
                return L"Main Menu";
                break;
            case XWF::Ordinary::XT_Action_RefineVolumeSnapshot:
                return L"Refine Volume Snapshot";
                break;
            case XWF::Ordinary::XT_Action_LogicalSearchStarting:
                return L"Logical Simultaneous Search";
                break;
            case XWF::Ordinary::XT_Action_PhysicalSearchStarting:
                return L"Physical Simultaneous Search";
                break;
            case XWF::Ordinary::XT_Action_DirectoryBrowserContextMenu:
                return L"Directory Browser Context Menu";
                break;
            case XWF::Ordinary::XT_Action_SearchHitContextMenu:
                return L"Search Hit Context Menu";
                break;
            case XWF::Ordinary::XT_Action_EventListContextMenu:
                return L"Event List Context Menu";
                break;
            case XWF::Ordinary::XT_Action_PrepareSimultaneousSearch:
                return L"Prepare Simultaneous Search";
                break;
            default:
                return L"Unknown";
                break;
        }
    }

    /// <summary>
    /// Request the user to enter a textual value.
    /// </summary>
    /// <param name="description">Description of what text is requested.</param>
    /// <returns>The value provided by the user. Empty string otherwise.</returns>
    export std::wstring GetUserInputText(const std::wstring& description = L"Please enter a value:", std::wstring defaultInput = std::wstring())
    {
        std::wstring userData;
        unsigned long inputStringSize = MAX_PATH;

        if (defaultInput.length() == 0)
        {
            userData = std::wstring(inputStringSize, L'\0');
        }
        else
        {
            userData = defaultInput;
            userData.reserve(inputStringSize);
        }

        INT64 returnedStringSize = JCS::XWFWrapper::Miscellaneous::XWF_GetUserInput(
            (LPWSTR)description.data(),
            (LPWSTR)userData.data(),
            inputStringSize,
            XWF::Miscellaneous::XWF_GetUserInput_AllowEmpty
        );

        return userData;
    }

    /// <summary>
    /// Request the user to enter a positive integer value.
    /// Note: Integer requests can not have a default value provided to the end user.
    /// </summary>
    /// <param name="description">Description of what positive integer is requested.</param>
    /// <returns>The positive integer value provided by the user. -1 otherwise</returns>
    export INT64 GetUserInputNumber(const std::wstring& description = L"Please enter a value:")
    {
        INT64 returnedNumber = JCS::XWFWrapper::Miscellaneous::XWF_GetUserInput(
            (LPWSTR)description.data(),
            NULL,
            NULL,
            XWF::Miscellaneous::XWF_GetUserInput_PositiveInteger
        );

        return returnedNumber;
    }
}
