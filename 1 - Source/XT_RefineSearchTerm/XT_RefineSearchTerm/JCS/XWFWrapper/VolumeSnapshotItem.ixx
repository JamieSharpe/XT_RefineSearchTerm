module;

#include <Windows.h>

export module VolumeSnapshotItem;

import Logging;
import Utils;
import XWUtils;
import XTension;
import std;

/// <summary>
/// Volume Snapshot Item Property Functions
/// </summary>
export namespace JCS::XWFWrapper::VolumeSnapshotItem
{
	std::optional<LPWSTR> XWF_GetItemName(DWORD nItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetItemName, L"XWF_GetItemName"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetItemName(nItemID);
	}

	std::optional<std::wstring> XWF_GetItemNameOpt(DWORD nItemID)
	{
		auto pWideStringName = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemName(nItemID);

		if (!pWideStringName.has_value() || pWideStringName.value() == nullptr)
		{
			JCS::Logging::Log(std::format("Could not retrieve item name for ID: {}", nItemID), JCS::Logging::LogLevel::Error);
			return std::nullopt;
		}

		std::wstring itemName = JCS::Utils::WCharPointerToWString(pWideStringName.value());
		return itemName;
	}

	VOID XWF_SetItemName(LONG nItemID, LPWSTR lpName)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemName, L"XWF_SetItemName"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemName(nItemID, lpName);
	}

	std::optional<INT64> XWF_GetItemSize(LONG nItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetItemSize, L"XWF_GetItemSize"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetItemSize(nItemID);
	}

	VOID XWF_SetItemSize(LONG nItemID, INT64 nSize)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemSize, L"XWF_SetItemSize"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemSize(nItemID, nSize);
	}

	VOID XWF_GetItemOfs(LONG nItemID, INT64* lpDefOfs, INT64* lpStartSector)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetItemOfs, L"XWF_GetItemOfs"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_GetItemOfs(nItemID, lpDefOfs, lpStartSector);
	}

	VOID XWF_SetItemOfs(LONG nItemID, INT64 nDefOfs, INT64 nStartSector)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemOfs, L"XWF_SetItemOfs"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemOfs(nItemID, nDefOfs, nStartSector);
	}

	std::optional<INT64> XWF_GetItemInformation(LONG nItemID, LONG nInfoType, LPBOOL lpSuccess)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetItemInformation, L"XWF_GetItemInformation"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetItemInformation(nItemID, nInfoType, lpSuccess);
	}

	std::optional<INT64> XWF_GetItemInformation_Flags(LONG nItemID)
	{
		std::unique_ptr<BOOL> success = std::make_unique<BOOL>();
		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation(nItemID, XWF::VolumeSnapshotItem::XWF_GetItemInformation_InfoTypeFlag_Flags, success.get());

		if (!returnedValue.has_value() || !*success)
		{
			return std::nullopt;
		}

		return returnedValue;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_IsDirectory(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_Directory;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_HasChildObjects(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_ChildObjects;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_HasSubDirectories(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_SubDirectories;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_IsVirtualItem(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_VirtualItem;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_IsHiddenByExaminer(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_HiddenByExaminer;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_IsTagged(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_Tagged;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_IsTaggedPartially(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_TaggedPartially;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_IsViewedByExaminer(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_ViewedByExaminer;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// Note: May need casting to Windows FILETIME
	/// </summary>
	/// <param name="flags"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_FileSystemTimestampNotUTC(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileSystemTimestampNotUTC;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// Note: May need casting to Windows FILETIME
	/// </summary>
	/// <param name="flags"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_InternalCreationTimestampNotUTC(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_InternalCreationTimestampNotUTC;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// Note: May need casting to Windows FILETIME
	/// </summary>
	/// <param name="flags"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_FATTimestamps(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FATTimestamps;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_OriginatesFromNTFS(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_OriginatesFromNTFS;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_UnixPermissions(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_UNIXPermissions;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_HasExaminerComment(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_HasExaminerComment;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_HasExtractedMetadata(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_HasExtractedMetadata;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileContentsUnknown(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileContentsUnknown;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileContentsPartiallyUnknown(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileContentsPartiallyUnknown;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_ReservedFlag(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_Reserved;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// Returns true is the primary hash value is calculated.
	/// </summary>
	/// <param name="nItemID"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_IsHashOneCalculated(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 isHashOneFlagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_HashOneComputed;

		if (isHashOneFlagSet)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// This is expensive, consider using <c>XWF_GetItemInformation_Flags_IsHashOneCalculated(std::optional&lt;INT64&gt; flags)</c>.
	/// </summary>
	/// <param name="nItemID"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_IsHashOneCalculated(LONG nItemID)
	{
		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_Flags(nItemID);

		if (!returnedValue)
		{
			return false;
		}

		std::optional<bool> hashOneCalculated = XWF_GetItemInformation_Flags_IsHashOneCalculated(returnedValue);

		if (hashOneCalculated.has_value() && hashOneCalculated.value())
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// Returns true is the secondary hash value is calculated.
	/// </summary>
	/// <param name="nItemID"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_IsHashTwoCalculated(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 isHashTwoFlagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_HashTwoComputed;

		if (isHashTwoFlagSet)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// This is expensive, consider using <c>XWF_GetItemInformation_Flags_IsHashTwoCalculated(std::optional&lt;INT64&gt; flags)</c>.
	/// </summary>
	/// <param name="flags"></param>
	/// <returns></returns>
	std::optional<bool> XWF_GetItemInformation_Flags_IsHashTwoCalculated(LONG nItemID)
	{
		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_Flags(nItemID);

		if (!returnedValue)
		{
			return false;
		}

		INT64 isHashTwoFlagSet = returnedValue.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_HashTwoComputed;

		if (isHashTwoFlagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_CategorisedIrrelevant(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_CategorisedIrrelevant;

		if (flagSet)
		{
			return true;
		}

		return false;
	}


	std::optional<bool> XWF_GetItemInformation_Flags_CategorisedNotable(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_CategorisedNotable;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_UncategorisedButKnown(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_UncategorisedButKnown;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_VolumeShadowCopy(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_VolumeShadowCopy;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_DeletedFilesButKnownContents(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_DeletedButKnownContents;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileConsistencyOk(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileConsistencyOk;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileConsistencyNotOk(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileConsistencyNotOk;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileArchiveExplored(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileArchivedExplored;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_EmailArchiveProcessed(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_EmailArchiveProcessed;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_EmbeddedDataUncovered(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_EmbeddedDataUncovered;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_MetadataExtracted(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_MetadataExtracted;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileEmbeddedInAnotherFileLinearly(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileEmbeddedInOtherFileLinearly;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_FileContentStoredExternally(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_FileContentStoredExternally;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<bool> XWF_GetItemInformation_Flags_AlternativeData(std::optional<INT64> flags)
	{
		if (!flags)
		{
			return false;
		}

		INT64 flagSet = flags.value() & XWF::VolumeSnapshotItem::XWF_Item_Info_Flags_return_AlternativeData;

		if (flagSet)
		{
			return true;
		}

		return false;
	}

	std::optional<INT64> XWF_GetItemInformation_DeletionStatusWrapper(LONG nItemID)
	{
		std::unique_ptr<BOOL> success = std::make_unique<BOOL>();
		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation(nItemID, XWF::VolumeSnapshotItem::XWF_GetItemInformation_InfoTypeFlag_Deletion, success.get());

		if (!*success)
		{
			return std::nullopt;
		}

		return returnedValue;
	}

	std::optional<XWF::Miscellaneous::XWF_Item_Info_Deletion_Status> XWF_GetItemInformation_DeletionStatus(LONG nItemID)
	{
		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_DeletionStatusWrapper(nItemID);

		if (!returnedValue)
		{
			return std::nullopt;
		}

		XWF::Miscellaneous::XWF_Item_Info_Deletion_Status deletionStatus = static_cast<XWF::Miscellaneous::XWF_Item_Info_Deletion_Status>(returnedValue.value());

		return deletionStatus;
	}

	std::optional<BOOL> XWF_SetItemInformation(LONG nItemID, LONG nInfoType, INT64 nInfoValue)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemInformation, L"XWF_SetItemInformation"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemInformation(nItemID, nInfoType, nInfoValue);
	}

	std::optional<LONG> XWF_GetItemType(LONG nItemID, LPWSTR lpTypeDescr, DWORD nBufferLenAndFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetItemType, L"XWF_GetItemType"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetItemType(nItemID, lpTypeDescr, nBufferLenAndFlags);
	}

	/// <summary>
	/// Returns a string representation of the file type.
	/// Example:
	///		Pictures
	///		Video
	/// 
	/// An available list may be found when doing a Type filter within the X-Ways item view.
	/// </summary>
	/// <param name="nItemID"></param>
	/// <returns></returns>
	std::optional<std::wstring> GetFileType(LONG nItemID)
	{
		std::unique_ptr<WCHAR[]> type = std::make_unique<WCHAR[]>(128);
		type.get()[0] = L'\0'; // Why? Test this again.
		DWORD length = 0x40000080; // receive a textual designation of the category that the file type belongs to instead (e.g. "Pictures" or "Programs")

		JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemType(nItemID, type.get(), length);

		std::wstring fileType = JCS::Utils::WCharPointerToWString(type.get());

		return fileType;
	}

	VOID XWF_SetItemType(LONG nItemID, LPWSTR lpTypeDescr, LONG nTypeStatus)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemType, L"XWF_SetItemType"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemType(nItemID, lpTypeDescr, nTypeStatus);
	}

	std::optional<LONG> XWF_GetItemParent(LONG nItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetItemParent, L"XWF_GetItemParent"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetItemParent(nItemID);
	}

	VOID XWF_SetItemParent(LONG nChildItemID, LONG nParentItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemParent, L"XWF_SetItemParent"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemParent(nChildItemID, nParentItemID);
	}

	std::optional<LONG> XWF_GetHashSetAssocs(LONG nItemID, LPWSTR lpBuffer, LONG nBufferLen)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetHashSetAssocs, L"XWF_GetHashSetAssocs"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetHashSetAssocs(nItemID, lpBuffer, nBufferLen);
	}

	std::optional<DWORD> XWF_GetReportTableAssocs(LONG nItemID, LPWSTR lpBuffer, LONG nBufferLen)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetReportTableAssocs, L"XWF_GetReportTableAssocs"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetReportTableAssocs(nItemID, lpBuffer, nBufferLen);
	}

	std::optional<LONG> XWF_AddToReportTable(LONG nItemID, LPWSTR lpReportTableName, DWORD nFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_AddToReportTable, L"XWF_AddToReportTable"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_AddToReportTable(nItemID, lpReportTableName, nFlags);
	}

	std::optional<LPWSTR> XWF_GetComment(LONG nItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetComment, L"XWF_GetComment"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetComment(nItemID);
	}

	std::optional<BOOL> XWF_AddComment(LONG nItemID, LPWSTR lpComment, DWORD nFlagsHowToAdd)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_AddComment, L"XWF_AddComment"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_AddComment(nItemID, lpComment, nFlagsHowToAdd);
	}

	std::optional<LPWSTR> XWF_GetExtractedMetadata(LONG nItemID)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetExtractedMetadata, L"XWF_GetExtractedMetadata"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetExtractedMetadata(nItemID);
	}

	std::optional<BOOL> XWF_AddExtractedMetadata(LONG nItemID, LPWSTR lpComment, DWORD nFlagsHowToAdd)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_AddExtractedMetadata, L"XWF_AddExtractedMetadata"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_AddExtractedMetadata(nItemID, lpComment, nFlagsHowToAdd);
	}

	std::optional<BOOL> XWF_GetHashValue(LONG nItemID, LPVOID lpBuffer)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetHashValue, L"XWF_GetHashValue"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetHashValue(nItemID, lpBuffer);
	}

	std::optional<std::wstring> XWF_GetHashValueOne(LONG nItemID, XWF::Miscellaneous::XW_HashType hashType)
	{
		if (!JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_Flags_IsHashOneCalculated(nItemID))
		{
			return std::nullopt;
		}

		int hashSize = JCS::XWUtils::HashTypeSize(hashType);

		if (hashSize <= 0)
		{
			return std::nullopt;
		}

		std::unique_ptr<BYTE[]> pHash = std::make_unique<BYTE[]>(hashSize);
		pHash[0] = 1; // Retrieve primary hash value, but don't compute if missing.

		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetHashValue(nItemID, pHash.get());

		if (!returnedValue)
		{
			return std::nullopt;
		}

		std::wstring hashValue = JCS::Utils::BytesToHex(pHash.get(), hashSize);
		return hashValue;
	}

	std::optional<std::wstring> XWF_GetHashValueTwo(LONG nItemID, XWF::Miscellaneous::XW_HashType hashType)
	{
		if (!JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemInformation_Flags_IsHashTwoCalculated(nItemID))
		{
			return std::nullopt;
		}

		int hashSize = JCS::XWUtils::HashTypeSize(hashType);

		if (hashSize <= 0)
		{
			return std::nullopt;
		}

		std::unique_ptr<BYTE[]> pHash = std::make_unique<BYTE[]>(hashSize);
		pHash[0] = 2; // Retrieve secondary hash value, but don't compute if missing.

		auto returnedValue = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetHashValue(nItemID, pHash.get());

		if (!returnedValue)
		{
			return std::nullopt;
		}

		std::wstring hashValue = JCS::Utils::BytesToHex(pHash.get(), hashSize);
		return hashValue;
	}

	std::optional<BOOL> XWF_SetHashValue(LONG nItemID, LPVOID lpHash, DWORD nParam)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetHashValue, L"XWF_SetHashValue"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_SetHashValue(nItemID, lpHash, nParam);
	}

	std::optional<LONG> XWF_GetCellText(LONG nItemID, LPVOID lpPointer, DWORD nFlags, WORD nColIndex, LPWSTR lpBuffer, DWORD nBufferLen)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_GetCellText, L"XWF_GetCellText"))
		{
			return std::nullopt;
		}

		return XWF::VolumeSnapshotItem::XWF_GetCellText(nItemID, lpPointer, nFlags, nColIndex, lpBuffer, nBufferLen);
	}

	VOID XWF_SetItemDataRuns(LONG nItemID, LPVOID lpBuffer)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::VolumeSnapshotItem::XWF_SetItemDataRuns, L"XWF_SetItemDataRuns"))
		{
			return;
		}

		return XWF::VolumeSnapshotItem::XWF_SetItemDataRuns(nItemID, lpBuffer);
	}

	/// <summary>
	/// Builds up the full file path of a given item.
	/// </summary>
	/// <param name="nItemID"></param>
	/// <returns></returns>
	std::optional<std::wstring> GetFilePathOpt(LONG nItemID)
	{
		std::optional<std::wstring> file_path = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemNameOpt(nItemID);

		if (!file_path)
		{
			return std::nullopt;
		}

		std::optional<LONG> parent_ID = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemParent(nItemID);

		if (!parent_ID.has_value())
		{
			return std::nullopt;
		}

		while (file_path && parent_ID != XWF::VolumeSnapshotItem::XWF_XWF_GetItemParent_RootObject)
		{
			std::optional<std::wstring> parent_name = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemNameOpt(parent_ID.value());

			if (!parent_name)
			{
				return file_path;
			}

			// TODO: Depending on the file system, change the path separator.
			std::wstring path_separator = L"\\";

			file_path = std::format(L"{}{}{}", parent_name.value(), path_separator, file_path.value());
			parent_ID = JCS::XWFWrapper::VolumeSnapshotItem::XWF_GetItemParent(parent_ID.value());
		}

		return file_path;
	}
}