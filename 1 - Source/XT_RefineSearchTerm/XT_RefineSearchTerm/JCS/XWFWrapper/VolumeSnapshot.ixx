module;

#include <Windows.h>

export module VolumeSnapshot;

import XTension;
import std;

/// <summary>
/// Volume Snapshot Management Functions
/// </summary>
export namespace JCS::XWFWrapper::VolumeSnapshot
{
    LONG XWF_SelectVolumeSnapshot(HANDLE hVolume)
    {
        return XWF::VolumeSnapshot::XWF_SelectVolumeSnapshot(hVolume);
    }

    std::optional<INT64> XWF_GetVSProp(LONG nPropType, PVOID pBuffer)
    {
        auto returnedValue = XWF::VolumeSnapshot::XWF_GetVSProp(nPropType, pBuffer);

        if (returnedValue == -1)
        {
            return std::nullopt;
        }

        return returnedValue;
    }

    std::optional<INT64> XWF_GetVSProp_GetSpecialItemID(XWF::VolumeSnapshot::XWF_GetVSProp_SpecialItem specialItem)
    {
        auto returnedValue = JCS::XWFWrapper::VolumeSnapshot::XWF_GetVSProp(XWF::VolumeSnapshot::XWF_GetVSProp_PropType_GetSpecialItemID, &specialItem);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        return returnedValue;
    }

    std::optional<XWF::Miscellaneous::XW_HashType> XWF_GetVSProp_GetHashOneType()
    {
        auto returnedValue = JCS::XWFWrapper::VolumeSnapshot::XWF_GetVSProp(XWF::VolumeSnapshot::XWF_GetVSProp_PropType_GetHashOneType, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        std::optional<XWF::Miscellaneous::XW_HashType> hashType = static_cast<XWF::Miscellaneous::XW_HashType>(returnedValue.value());

        return hashType;
    }

    std::optional<XWF::Miscellaneous::XW_HashType> XWF_GetVSProp_GetHashTwoType()
    {
        auto returnedValue = JCS::XWFWrapper::VolumeSnapshot::XWF_GetVSProp(XWF::VolumeSnapshot::XWF_GetVSProp_PropType_GetHashTwoType, nullptr);

        if (!returnedValue)
        {
            return std::nullopt;
        }

        std::optional<XWF::Miscellaneous::XW_HashType> hashType = static_cast<XWF::Miscellaneous::XW_HashType>(returnedValue.value());

        return hashType;
    }

    DWORD XWF_GetItemCount(LPVOID pTarget)
    {
        return XWF::VolumeSnapshot::XWF_GetItemCount(pTarget);
    }

    DWORD XWF_GetFileCount(LONG nDirID)
    {
        return XWF::VolumeSnapshot::XWF_GetFileCount(nDirID);
    }

    LONG XWF_GetSpecialItemID(DWORD nSpecialItem)
    {
        return XWF::VolumeSnapshot::XWF_GetSpecialItemID(nSpecialItem);
    }

    LONG XWF_CreateItem(LPWSTR lpName, DWORD nCreationFlags)
    {
        return XWF::VolumeSnapshot::XWF_CreateItem(lpName, nCreationFlags);
    }

    LONG XWF_CreateFile(LPWSTR pName, DWORD nCreationFlags, LONG nParentItemID, PVOID pSourceInfo)
    {
        return XWF::VolumeSnapshot::XWF_CreateFile(pName, nCreationFlags, nParentItemID, pSourceInfo);
    }

    LONG XWF_FindItem1(LONG nParentItemID, LPWSTR lpName, DWORD nFlags, LONG nSearchStartItemID)
    {
        return XWF::VolumeSnapshot::XWF_FindItem1(nParentItemID, lpName, nFlags, nSearchStartItemID);
    }

    BOOL XWF_Mount(LONG nDirID, LPWSTR lpMountPath, LPVOID lpReserved)
    {
        return XWF::VolumeSnapshot::XWF_Mount(nDirID, lpMountPath, lpReserved);
    }

    BOOL XWF_Unmount(LPWSTR lpMountPath)
    {
        return XWF::VolumeSnapshot::XWF_Unmount(lpMountPath);
    }
}