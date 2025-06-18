module;

#include <Windows.h>

export module VolumeSnapshot;

import Utils;
import XTension;
import std;

/// <summary>
/// Volume Snapshot Management Functions
/// </summary>
export namespace JCS::XWFWrapper::VolumeSnapshot
{
	std::optional<LONG> XWF_SelectVolumeSnapshot(HANDLE hVolume)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_SelectVolumeSnapshot, L"XWF_SelectVolumeSnapshot"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_SelectVolumeSnapshot(hVolume);
	}

	std::optional<INT64> XWF_GetVSProp(LONG nPropType, PVOID pBuffer)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_GetVSProp, L"XWF_GetVSProp"))
		{
			return std::nullopt;
		}

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

	std::optional<DWORD> XWF_GetItemCount(LPVOID pTarget)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_GetItemCount, L"XWF_GetItemCount"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_GetItemCount(pTarget);
	}

	std::optional<DWORD> XWF_GetFileCount(LONG nDirID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_GetFileCount, L"XWF_GetFileCount"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_GetFileCount(nDirID);
	}

	std::optional<LONG> XWF_GetSpecialItemID(DWORD nSpecialItem)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_GetSpecialItemID, L"XWF_GetSpecialItemID"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_GetSpecialItemID(nSpecialItem);
	}

	std::optional<LONG> XWF_CreateItem(LPWSTR lpName, DWORD nCreationFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_CreateItem, L"XWF_CreateItem"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_CreateItem(lpName, nCreationFlags);
	}

	std::optional<LONG> XWF_CreateFile(LPWSTR pName, DWORD nCreationFlags, LONG nParentItemID, PVOID pSourceInfo)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_CreateFile, L"XWF_CreateFile"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_CreateFile(pName, nCreationFlags, nParentItemID, pSourceInfo);
	}

	std::optional<LONG> XWF_FindItem1(LONG nParentItemID, LPWSTR lpName, DWORD nFlags, LONG nSearchStartItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_FindItem1, L"XWF_FindItem1"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_FindItem1(nParentItemID, lpName, nFlags, nSearchStartItemID);
	}

	std::optional<BOOL> XWF_Mount(LONG nDirID, LPWSTR lpMountPath, LPVOID lpReserved)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_Mount, L"XWF_Mount"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_Mount(nDirID, lpMountPath, lpReserved);
	}

	std::optional<BOOL> XWF_Unmount(LPWSTR lpMountPath)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshot::XWF_Unmount, L"XWF_Unmount"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshot::XWF_Unmount(lpMountPath);
	}
}