module;

#include <Windows.h>

export module IO;

import Utils;
import Logging;
import XTension;
import std;

/// <summary>
/// Disk and general IO functions
/// </summary>
export namespace JCS::XWFWrapper::IO
{
    /// <summary>
    /// Retrieves the name of the volume in UTF-16, 255 characters at most. 3 types of names are available (1, 2 or 3). For example, 3 can be more generic than 2 ("Hard disk 1" instead of "WD12345678"). 
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="lpBuffer"></param>
    /// <param name="nType"></param>
    /// <returns></returns>
    VOID XWF_GetVolumeName(HANDLE hVolume, LPWSTR lpBuffer, DWORD nType)
    {
        return XWF::IO::XWF_GetVolumeName(hVolume, lpBuffer, nType);
    }

    /// <summary>
    /// Gets the volume name.
    /// </summary>
    /// <param name="hVolume"></param>
    /// <returns></returns>
    export std::optional<std::wstring> GetVolumeName(std::optional<HANDLE> hVolume, DWORD type = 0x1)
    {
        if (!hVolume || hVolume.value() == nullptr)
        {
            return std::nullopt;
        }

        std::unique_ptr<WCHAR[]> volume_name_buffer = std::make_unique<WCHAR[]>(255);

        JCS::XWFWrapper::IO::XWF_GetVolumeName(hVolume.value(), volume_name_buffer.get(), type);

        std::wstring volume_name = JCS::Utils::WCharPointerToWString(volume_name_buffer.get());

        return volume_name;
    }

    /// <summary>
    /// Retrieves various information about the volume. All parameters are optional, and most are self-explanatory. 
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="lpFileSystem"></param>
    /// <param name="lpBytesPerSector"></param>
    /// <param name="lpSectorsPerCluster"></param>
    /// <param name="lpClusterCount"></param>
    /// <param name="lpFirstClusterSectorNo"></param>
    /// <returns>False if the values are to be discarded/error prone.</returns>
    bool XWF_GetVolumeInformation(std::optional<HANDLE> hVolume, LPLONG lpFileSystem, LPDWORD lpBytesPerSector, LPDWORD lpSectorsPerCluster, PINT64 lpClusterCount, PINT64 lpFirstClusterSectorNo)
    {
        if (!hVolume)
        {
            return false;
        }

        XWF::IO::XWF_GetVolumeInformation(hVolume.value(), lpFileSystem, lpBytesPerSector, lpSectorsPerCluster, lpClusterCount, lpFirstClusterSectorNo);

        return true;
    }

    /// <summary>
    /// Available in v19.9 SR-7 and later. Retrieves information about the specified volume or item, either through the buffer or the return value, depending on what kind of information you require (nPropType). If through the return value, you may need to cast it to the appropriate type in order to correctly interpret/understand it. 
    /// </summary>
    /// <param name="hVolumeOrItem"></param>
    /// <param name="nPropType"></param>
    /// <param name="lpBuffer"></param>
    /// <returns></returns>
    std::optional<INT64> XWF_GetProp(std::optional<HANDLE> hVolumeOrItem, DWORD nPropType, PVOID lpBuffer)
    {
        if (!hVolumeOrItem || hVolumeOrItem.value() == nullptr)
        {
            JCS::Logging::Log("Volume or Item handle is null.", JCS::Logging::LogLevel::Error);
            return std::nullopt;
        }

        return XWF::IO::XWF_GetProp(hVolumeOrItem.value(), nPropType, lpBuffer);
    }

    /// <summary>
    /// Gets the physical size of a volume or disk.
    /// </summary>
    /// <param name="hVolumeOrItem"></param>
    /// <returns></returns>
    std::optional<INT64> XWF_GetProp_PhysicalSize(std::optional<HANDLE> hVolumeOrItem)
    {
        return JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_PhysicalSize, nullptr);
    }

    std::optional<INT64> XWF_GetProp_LogicalSize(std::optional<HANDLE> hVolumeOrItem)
    {
        return JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_LogicalSize, nullptr);
    }

    std::optional<INT64> XWF_GetProp_ValidDataLength(std::optional<HANDLE> hVolumeOrItem)
    {
        return JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_ValidDataLength, nullptr);
    }

    std::optional<DWORD> XWF_GetProp_FileAttributes(std::optional<HANDLE> hVolumeOrItem)
    {
        auto returnedValue = JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_FileAttributes, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        std::optional<DWORD> fileAttributes = static_cast<DWORD>(returnedValue.value());

        return fileAttributes;
    }

    std::optional<std::wstring> XWF_GetProp_FilePathOrName(std::optional<HANDLE> hVolumeOrItem)
    {
        auto returnedValue = JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_FilePathOrName, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        LPWSTR pFilePathOrName = reinterpret_cast<LPWSTR>(returnedValue.value());

        if (pFilePathOrName == nullptr)
        {
            return std::nullopt;
        }

        std::wstring filePathOrName = JCS::Utils::LPWStrToWString(pFilePathOrName);
        return filePathOrName;
    }

    std::optional<std::wstring> XWF_GetProp_PureName(std::optional<HANDLE> hVolumeOrItem)
    {
        auto returnedValue = JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_PureName, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        LPWSTR pPureName = reinterpret_cast<LPWSTR>(returnedValue.value());

        if (pPureName == nullptr)
        {
            return std::nullopt;
        }

        std::wstring pureName = JCS::Utils::LPWStrToWString(pPureName);
        return pureName;
    }

    std::optional<HANDLE> XWF_GetProp_ParentVolume(std::optional<HANDLE> hVolumeOrItem)
    {
        auto returnedValue = JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_ParentVolume, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        HANDLE parentVolume = reinterpret_cast<HANDLE>(returnedValue.value());

        return parentVolume;
    }

    std::optional<WORD> XWF_GetProp_DataWindow(std::optional<HANDLE> hVolumeOrItem)
    {
        auto returnedValue = JCS::XWFWrapper::IO::XWF_GetProp(hVolumeOrItem, XWF::IO::XWF_GetProp_PropType_DataWindow, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        WORD dataWindow = static_cast<WORD>(returnedValue.value());

        return dataWindow;
    }

    /// <summary>
    /// Retrieves information about a certain sector on a volume. Returns FALSE if the sector belongs to an unused/free cluster, otherwise TRUE.
    /// lpDescr: Retrieves a textual description of what this sector is used for.Can be the name and path of a file or something like "FAT 1".May be language specific.Use a buffer that has space for 511 characters and a terminating null.
    /// lpItemID : Optional.Retrieves the ID of the item in the volume snapshot that the sector is allocated to, if any, otherwise - 1.
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="nSectorNo"></param>
    /// <param name="lpDescr"></param>
    /// <param name="lpItemID"></param>
    /// <returns></returns>
    BOOL XWF_GetSectorContents(HANDLE hVolume, INT64 nSectorNo, LPWSTR lpDescr, LPLONG lpItemID)
    {
        return XWF::IO::XWF_GetSectorContents(hVolume, nSectorNo, lpDescr, lpItemID);
    }

    /// <summary>
    /// Available in v16.5 and later. Opens the file or directory that is contained in the specified volume and that has the specified ID for reading and returns a handle to it, or 0 if unsuccessful. nFlags values are supported by v17.5 SR-11, v17.6 SR-7, v17.7 and later unless specified otherwise:
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="nItemID"></param>
    /// <param name="nFlags"></param>
    /// <returns></returns>
    HANDLE XWF_OpenItem(HANDLE hVolume, LONG nItemID, DWORD nFlags)
    {
        return XWF::IO::XWF_OpenItem(hVolume, nItemID, nFlags);
    }

    /// <summary>
    /// Available in v16.5 and later. Closes a volume that was opened with the XWF_OpenEvObj function or an item that was opened with the XWF_OpenItem function.
    /// </summary>
    /// <param name="hVolumeOrItem"></param>
    /// <returns></returns>
    VOID XWF_Close(HANDLE hVolumeOrItem)
    {
        return XWF::IO::XWF_Close(hVolumeOrItem);
    }

    /// <summary>
    /// Reads the specified number of bytes from the specified position in the specified volume or item into the specified buffer. Returns the number of bytes read. 
    /// </summary>
    /// <param name="hVolumeOrItem"></param>
    /// <param name="nOffset"></param>
    /// <param name="lpBuffer"></param>
    /// <param name="nNumberOfBytesToRead"></param>
    /// <returns></returns>
    DWORD XWF_Read(HANDLE hVolumeOrItem, INT64 nOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToRead)
    {
        return XWF::IO::XWF_Read(hVolumeOrItem, nOffset, lpBuffer, nNumberOfBytesToRead);
    }

    /// <summary>
    /// Writes the specified number of bytes in the specified buffer at the specified position to the specified volume. Works only in WinHex, not in X-Ways Forensics. Returns the number of bytes written, or -1 if a complete failure occurred. Not currently implemented.
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="nOffset"></param>
    /// <param name="lpBuffer"></param>
    /// <param name="nNumberOfBytesToWrite"></param>
    /// <returns></returns>
    INT64 XWF_Write(HANDLE hVolume, INT64 nOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite)
    {
        return XWF::IO::XWF_Write(hVolume, nOffset, lpBuffer, nNumberOfBytesToWrite);
    }

    /// <summary>
    /// Not currently implemented. 
    /// </summary>
    /// <param name="pDInfo"></param>
    /// <returns></returns>
    LPVOID XWF_GetDriveInfo(struct XWF::IO::DriveInfo* pDInfo)
    {
        return XWF::IO::XWF_GetDriveInfo(pDInfo);
    }

    /// <summary>
    /// Reads or writes the specified sectors number from or to the specified disk or image or partition or volume or RAID. May be called when processing XT_SectorIO(). Returns the number of sectors read/written/covered. nDrive is a device/disk/partition/volume/image/RAID identifier. nFlags may be NULL if you do not wish to specify or receive any flags. Available from v18.4. 
    /// </summary>
    /// <param name="nDrive"></param>
    /// <param name="nSector"></param>
    /// <param name="nCount"></param>
    /// <param name="lpBuffer"></param>
    /// <param name="nFlags"></param>
    /// <returns></returns>
    DWORD XWF_SectorIO(LONG nDrive, INT64 nSector, DWORD nCount, LPVOID lpBuffer, LPDWORD nFlags)
    {
        return XWF::IO::XWF_SectorIO(nDrive, nSector, nCount, lpBuffer, nFlags);
    }

    /// <summary>
    /// Available in v17.7 and later. Retrieves the boundaries of the currently selected block in the window that represents the specified volume, if any. Returns FALSE if there no block is defined. 
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="lpStartOfs"></param>
    /// <param name="lpEndOfs"></param>
    /// <returns></returns>
    BOOL XWF_GetBlock(HANDLE hVolume, PINT64 lpStartOfs, PINT64 lpEndOfs)
    {
        return XWF::IO::XWF_GetBlock(hVolume, lpStartOfs, lpEndOfs);
    }

    /// <summary>
    /// Available in v17.7 and later. Sets the boundaries of the currently selected block, if any. Returns FALSE if the boundaries that you specify exceed the size of the volume. Set nEndOfs to -1 to clear any currently defined block. If you wish to refresh the display, you can for example call the Windows API function InvalidateRect() for the current data window's hex window. 
    /// </summary>
    /// <param name="hVolume"></param>
    /// <param name="nStartOfs"></param>
    /// <param name="nEndOfs"></param>
    /// <returns></returns>
    BOOL XWF_SetBlock(HANDLE hVolume, INT64 nStartOfs, INT64 nEndOfs)
    {
        return XWF::IO::XWF_SetBlock(hVolume, nStartOfs, nEndOfs);
    }
}