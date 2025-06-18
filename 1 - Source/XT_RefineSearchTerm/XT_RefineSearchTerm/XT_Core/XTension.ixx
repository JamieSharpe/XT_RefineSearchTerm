module;

#include "Windows.h"

export module XTension;

import std;

///////////////////////////////////////////////////////////////////////////////
// X-Tension API - Functions
// Copyright X-Ways Software Technology AG
// Originally downloaded from:
// https://www.x-ways.net/forensics/x-tensions/XT_C++.zip
//
// For current documentation, please consult:
// http://x-ways.com/forensics/x-tensions/api.html
// 
// This file has been heavily modified by Jamie Sharpe.
///////////////////////////////////////////////////////////////////////////////

#pragma region XWF_*
///////////////////////////////////////////////////////////////////////////////
// Functions that you may call
// See:
// https://www.x-ways.net/forensics/x-tensions/XWF_functions.html

#pragma region IO
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#A
/// </summary>
export namespace XWF::IO
{
	/// XWF_GetVolumeName
	using fptr_XWF_GetVolumeName = void(__stdcall*) (HANDLE hVolume, wchar_t* lpString, DWORD nType);
	fptr_XWF_GetVolumeName XWF_GetVolumeName;

	constexpr auto XWF_GetVolumeName_FullName = 0x1UL;
	constexpr auto XWF_GetVolumeName_Simple = 0x2UL;
	constexpr auto XWF_GetVolumeName_Minified = 0x4UL;

	/// XWF_GetVolumeInformation
	using fptr_XWF_GetVolumeInformation = void(__stdcall*) (HANDLE hVolume, LPLONG lpFileSystem, DWORD* nBytesPerSector, DWORD* nSectorsPerCluster, INT64* nClusterCount, INT64* nFirstClusterSectorNo);
	fptr_XWF_GetVolumeInformation XWF_GetVolumeInformation;

	/// XWF_GetProp
	using fptr_XWF_GetProp = INT64(__stdcall*)(HANDLE hVolumeOrItem, DWORD nPropType, void* lpBuffer);
	fptr_XWF_GetProp XWF_GetProp;

	/// The below defines are to be used with the following function:
	/// HANDLE XWF_GetProp(HANDLE hVolumeOrItem, DWORD nPropType, void* lpBuffer);
	/// nPropType                                        value   actual result type  pBuffer type    description
	constexpr auto XWF_GetProp_PropType_PhysicalSize = 0; 	// INT64            (unused)        physical size of a file or volume or disk
	constexpr auto XWF_GetProp_PropType_LogicalSize = 1; 	// INT64            (unused)        logical size of a file
	constexpr auto XWF_GetProp_PropType_ValidDataLength = 2; 	// INT64            (unused)        valid data length of a file(a.k.a.initialized size of the data stream, which may be available from NTFS, exFAT, XWFS, XWFS2)
	constexpr auto XWF_GetProp_PropType_FileAttributes = 4; 	// DWORD            (unused)        attributes of a file
	constexpr auto XWF_GetProp_PropType_FilePathOrName = 8; 	// LPWSTR           (unused)        pointer to the file path, if available, or just name
	constexpr auto XWF_GetProp_PropType_PureName = 9; 	// LPWSTR           (unused)        pointer to the pure name
	constexpr auto XWF_GetProp_PropType_ParentVolume = 10;   // HANDLE           (unused)        parent volume of a file
	constexpr auto XWF_GetProp_PropType_DataWindow = 16;   // WORD             (unused)        the 1 - based number of the data window that shows the specified volume or file, can be 0 in unusual cases to indicate an error

	/// XWF_GetSize
	using fptr_XWF_GetSize = INT64(__stdcall*) (HANDLE hVolumeOrItem, LPVOID lpOptional);
	fptr_XWF_GetSize XWF_GetSize;

	/// XWF_GetSectorContents
	using fptr_XWF_GetSectorContents = BOOL(__stdcall*) (HANDLE hVolume, INT64 nSectorNo, wchar_t* lpDescr, LPLONG lpItemID);
	fptr_XWF_GetSectorContents XWF_GetSectorContents;

	/// XWF_OpenItem
	using fptr_XWF_OpenItem = HANDLE(__stdcall*) (HANDLE hVolume, LONG nItemID, DWORD nFlags);
	fptr_XWF_OpenItem XWF_OpenItem;

	/// The below defines are to be used with the following function:
	/// HANDLE XWF_OpenItem(HANDLE hVolume, LONG nItemID, DWORD nFlags);
	/// Note: *You can find out the size in bytes of the result by calling XWF_GetSize().
	/// Flag (for nFlags)                                       Value       Description
	constexpr auto XWF_OpenItem_Flag_Content = 0x0000;   // Open for file content only.
	constexpr auto XWF_OpenItem_Flag_FileSlack = 0x0001;   // Open for access including file slack.
	constexpr auto XWF_OpenItem_Flag_SupressError = 0x0002;   // Suppress error messages in the program in case of failure.
	constexpr auto XWF_OpenItem_Flag_AlternativeData = 0x0008;   // Prefer alternative file data if available, e.g.a thumbnail created by X - Ways Forensics for a picture.
	constexpr auto XWF_OpenItem_Flag_AlternativeDataWithFailure = 0x0010;   // Open alternative file data if available, and fail if not (v17.7 SR - 3 and later).
	constexpr auto XWF_OpenItem_Flag_ExtCarvedFiles = 0x0080;   // Open carved files in Ext2 / 3 volumes without applying Ext block logic(at least v19.8 and later).
	constexpr auto XWF_OpenItem_Flag_PDFFormat = 0x0200;   // Convert to PDF format on the fly and open PDF data(v19.9 and later, not in WinHex Lab Edition useful for certain supported file formats).*
	constexpr auto XWF_OpenItem_Flag_PlainTextUTF8 = 0x0400;   // Extract plain text on the fly as UTF - 8 and open textual data(v20.0 and later, useful for certain supported file formats).*
	constexpr auto XWF_OpenItem_Flag_PlainTextUTF16 = 0x0800;   // Extract plain text on the fly as UTF - 16 and open textual data(v20.0 and later, useful for certain supported file formats).*
	constexpr auto XWF_OpenItem_Flag_PrependBOM = 0x1000;   // Prepend Byte Order Mark (for XWF_OpenItem_Flag_PlainTextUTF8 and XWF_OpenItem_Flag_PlainTextUTF16).

	/// Close item on a volume
	using fptr_XWF_Close = void(__stdcall*) (HANDLE hVolumeOrItem);
	fptr_XWF_Close XWF_Close;

	/// XWF_Read (tested)
	using  fptr_XWF_Read = DWORD(__stdcall*) (HANDLE hVolumeOrItem, INT64 nOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
	fptr_XWF_Read XWF_Read;

	/// XWF_Write - Not yet implemented
	using fptr_XWF_Write = DWORD(__stdcall*) (HANDLE hVolume, INT64 nOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite);
	fptr_XWF_Write XWF_Write;

#pragma pack(push, 2)
	struct DriveInfo
	{
		DWORD nSize;
		LONG nDrive;
		DWORD nBytesPerSector;
		INT64 nSectorCount;
	};
#pragma pack(pop)

	/// XWF_GetDriveInfo - Not yet implemented
	using fptr_XWF_GetDriveInfo = LPVOID(__stdcall*) (struct XWF::IO::DriveInfo* pDInfo);
	fptr_XWF_GetDriveInfo XWF_GetDriveInfo;

	/// XWF_SectorIO
	using fptr_XWF_SectorIO = DWORD(__stdcall*) (LONG nDrive, INT64 nSector, DWORD nCount, LPVOID lpBuffer, LPDWORD nFlags);
	fptr_XWF_SectorIO XWF_SectorIO;

	/// XWF_GetBlock
	using fptr_XWF_GetBlock = BOOL(__stdcall*) (HANDLE hVolume, INT64* lpStartOfs, INT64* lpEndOfs);
	fptr_XWF_GetBlock XWF_GetBlock;

	/// XWF_SetBlock
	using fptr_XWF_SetBlock = BOOL(__stdcall*) (HANDLE hVolume, INT64 nStartOfs, INT64 nEndOfs);
	fptr_XWF_SetBlock XWF_SetBlock;
}
#pragma endregion IO

#pragma region EvidenceAndCase
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#B
/// </summary>
export namespace XWF::EvidenceAndCase
{
	/// XWF_GetCaseProp
	using fptr_XWF_GetCaseProp = INT64(__stdcall*) (LPVOID pReserved, LONG nPropType, PVOID pBuffer, LONG nBufLen);
	fptr_XWF_GetCaseProp XWF_GetCaseProp;

	/// The below defines are to be used with the following function:
	/// INT64 XWF_GetCaseProp(LPVOID pReserved, LONG nPropType, PVOID pBuffer, LONG nBufLen);
	/// nPropType 	  	                                Value       pBuffer type     nBufLen    Description
	constexpr auto XWF_GetCaseProp_PropType_ID = 0;        // n / a         n / a      Returns a unique 64 - bit ID of the case (v19.7 and later).
	constexpr auto XWF_GetCaseProp_PropType_Title = 1;        // LPWSTR          ~        Case title.
	constexpr auto XWF_GetCaseProp_PropType_Creation = 2;        // n / a         n / a 	  	Returns the creation time as FILETIME(v19.7 and later).
	constexpr auto XWF_GetCaseProp_PropType_Examiner = 3;        // LPWSTR          ~        Examiner.
	constexpr auto XWF_GetCaseProp_PropType_File = 5;        // LPWSTR          ~        .xfc Case file path.
	constexpr auto XWF_GetCaseProp_PropType_Dir = 6;        // LPWSTR          ~        Case directory.

	/// XWF_GetFirstEvObj
	using fptr_XWF_GetFirstEvObj = HANDLE(__stdcall*) (LPVOID pReserved);
	fptr_XWF_GetFirstEvObj XWF_GetFirstEvObj;

	/// XWF_GetNextEvObj
	using fptr_XWF_GetNextEvObj = HANDLE(__stdcall*) (HANDLE hPrevEvidence, LPVOID pReserved);
	fptr_XWF_GetNextEvObj XWF_GetNextEvObj;

	/// XWF_DeleteEvObj
	using  fptr_XWF_DeleteEvObj = HANDLE(__stdcall*) (HANDLE hEvidence);
	fptr_XWF_DeleteEvObj XWF_DeleteEvObj;

	/// XWF_CreateEvObj
	using fptr_XWF_CreateEvObj = HANDLE(__stdcall*) (DWORD nType, LONG nDiskID, LPWSTR lpPath, PVOID pReserved);
	fptr_XWF_CreateEvObj XWF_CreateEvObj;

	/// XWF_OpenEvObj
	using  fptr_XWF_OpenEvObj = HANDLE(__stdcall*) (HANDLE hEvidence, DWORD nFlags);
	fptr_XWF_OpenEvObj XWF_OpenEvObj;

	/// XWF_CloseEvObj
	using fptr_XWF_CloseEvObj = VOID(__stdcall*) (HANDLE hEvidence);
	fptr_XWF_CloseEvObj XWF_CloseEvObj;

	/// XWF_GetEvObjProp
	using fptr_XWF_GetEvObjProp = INT64(__stdcall*) (HANDLE hEvidence, DWORD nPropType, PVOID pBuffer);
	fptr_XWF_GetEvObjProp XWF_GetEvObjProp;

	/// The below defines are to be used with the following function:
	/// INT64 XWF_GetEvObjProp( HANDLE hEvidence, DWORD nPropType, PVOID lpBuffer);
	/// nPropType                                                                   Value       actual result type  pBuffer type    description
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectNumber = 0;        // WORD             (unused)        Ev.obj.number(simply reflects the order of evidence objects in the case tree and thus may change).
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectID = 1;        // DWORD            (unused)        Ev.obj.ID(used to identify parent - child relationships between evidence objects).
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectParentID = 2;        // DWORD            (unused)        Parent ev.obj.ID(available for partitions, 0 if no parent).
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectShortID = 3;        // WORD             (unused)        Short ev.obj.ID(concatenated with the ID of items in the volume snapshot gives the so - called unique ID shown for items in the directory browser, available in v18.8 SR - 14, v18.9 SR - 12, v19.0 SR - 11 and later).
	constexpr auto XWF_GetEvObjProp_PropType_VolumeSnapshotID = 4;        // DWORD            (unused)        Volume snapshot ID(increments by 1 when a new volume snapshot is taken, available in v19.0 SR - 11 and later).
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectitle = 6;        // LPWSTR           (unused)        Evidence object title(e.g. "Partition 2").
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectitleExtended = 7;        // LONG             LPWSTR 	        Extended ev.obj.title(e.g. "HD123, Partition 2), buffer len: MAX_PATH, returns the string length.
	constexpr auto XWF_GetEvObjProp_PropType_EvidenceObjectitleExtendedAbbreviated = 8;        // LONG             LPWSTR 	        Abbreviated ext.ev.obj.title(e.g. "HD123, P2), buffer len: MAX_PATH, returns the string length.
	constexpr auto XWF_GetEvObjProp_PropType_InternalName = 9;        // LPWSTR           (unused)        Internal name.
	constexpr auto XWF_GetEvObjProp_PropType_Description = 10;       // LPWSTR           (unused)        Description.
	constexpr auto XWF_GetEvObjProp_PropType_ExaminerComments = 11;       // LPWSTR           (unused)        Examiner comments.
	constexpr auto XWF_GetEvObjProp_PropType_InternallyUsedDirectory = 12;       // LONG             LPWSTR 	        Internally used directory(buffer length : MAX_PATH), returns the string length.
	constexpr auto XWF_GetEvObjProp_PropType_OutputDirectory = 13;       // LONG             LPWSTR 	        Output directory(buffer length : MAX_PATH), returns the string length.
	constexpr auto XWF_GetEvObjProp_PropType_SizeInBytes = 16;       // INT64            (unused)        Size in bytes.
	constexpr auto XWF_GetEvObjProp_PropType_VolumeSnapshotFileCount = 17;       // DWORD            (unused)        Volume snapshot file count.
	constexpr auto XWF_GetEvObjProp_PropType_Flags = 18;       // INT64            (unused)        Flags *.
	constexpr auto XWF_GetEvObjProp_PropType_FileSystemIdentifier = 19;       // INT64            (unused)        File system identifier(see XWF_GetVolumeInformation for possible values).
	constexpr auto XWF_GetEvObjProp_PropType_HashTypeOne = 20;       // DWORD            (unused)        Hash type.
	constexpr auto XWF_GetEvObjProp_PropType_HashValueOne = 21;       // DWORD            LPVOID 	        Hash value (buffer size according to hash type), returns the hash size in bytes.
	constexpr auto XWF_GetEvObjProp_PropType_CreationTime = 32;       // FILETIME         (unused)        Creation time(when the ev.obj.was added to the case).
	constexpr auto XWF_GetEvObjProp_PropType_ModifiedTime = 33;       // FILETIME         (unused)        Modification time.
	constexpr auto XWF_GetEvObjProp_PropType_HashTypeTwo = 40;       // DWORD            (unused)        Hash type #2.
	constexpr auto XWF_GetEvObjProp_PropType_HashValueTwo = 41;       // DWORD            LPVOID 	        Hash value #2 (buffer size according to hash type), returns the hash size in bytes.
	constexpr auto XWF_GetEvObjProp_PropType_DataWindow = 50;       // WORD             LPVOID 	        The number of the data window that currently represents the evidence object, or 0 if the evidence object is not open, available in v19.9 SR - 7 and later.

	/// FLAGS *
	/// INT64 XWF_GetEvObjProp( HANDLE hEvidence, DWORD nPropType, PVOID lpBuffer);
	/// Flag                                                            Value       Description
	constexpr auto XWF_GetEvObjProp_FLAG_DataWindowActive = 0x000001; // Data window active yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_DataWindowOpen = 0x000002; // Data window open yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_Flagged = 0x000004; // Flagged yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_SelectedForOperations = 0x000008; // Selected for operations yes/no (in case of a physical, partitioned evidence object, the operation should be applied to the areas outside of explorable partitions only, as the partitions are their own evidence objects and selectable separately).
	constexpr auto XWF_GetEvObjProp_FLAG_SelectedForRecursive = 0x000010; // Selected for recursive view yes/no, in v19.9 SR-11, v20.0 SR-6 and later.
	constexpr auto XWF_GetEvObjProp_FLAG_ExpandedInCaseTree = 0x000020; // Expanded in case tree yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_HasNoChildren = 0x000040; // Has no children yes/no.

	constexpr auto XWF_GetEvObjProp_FLAG_IsEvidenceFileContainer = 0x000100; // Is an evidence file container yes / no.
	constexpr auto XWF_GetEvObjProp_FLAG_IsDeletedPartition = 0x000200; // Is a deleted partition yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_OpticalDiscIcon = 0x000400; // Optical disc icon yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_RAMIcon = 0x000800; // RAM icon yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_IsDynamicDisk = 0x001000; // Is dynamic disk yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_EvidenceFileIsSingleFile = 0x002000; // Evidence object is just a single file in the directory.

	constexpr auto XWF_GetEvObjProp_FLAG_IndexAvailable = 0x010000; // Index available yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_LoggingEnabled = 0x020000; // Logging enabled yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_AnnotationsHighlighted = 0x040000; // Annotations highlighted yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_WarnedOfWeirdImageFileSize = 0x080000; // Warned of weird image file size already yes/no.
	constexpr auto XWF_GetEvObjProp_FLAG_SupressSizeOfEvidenceChanged = 0x100000; // Suppress "size of evidence object has changed" yes/no.

	/// XWF_SetEvObjProp
	using fptr_XWF_SetEvObjProp = LONG(__stdcall*) (HANDLE hEvidence, LONG nPropType, PVOID pBuffer);
	fptr_XWF_SetEvObjProp XWF_SetEvObjProp;

	/// XWF_GetEvObj
	using  fptr_XWF_GetEvObj = HANDLE(__stdcall*) (DWORD nEvObjID);
	fptr_XWF_GetEvObj XWF_GetEvObj;

	/// XWF_GetReportTableInfo
	using  fptr_XWF_GetReportTableInfo = LPVOID(__stdcall*) (LPVOID pReserved, LONG nReportTableID, PLONG lpOptional);
	fptr_XWF_GetReportTableInfo XWF_GetReportTableInfo;

	/// XWF_GetEvObjReportTableAssocs
	using fptr_XWF_GetEvObjReportTableAssocs = LPVOID(__stdcall*) (HANDLE hEvidence, LONG nFlags, PLONG lpValue);
	fptr_XWF_GetEvObjReportTableAssocs XWF_GetEvObjReportTableAssocs;
}
#pragma endregion EvidenceAndCase

#pragma region VolumeSnapshot
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#C
/// </summary>
export namespace XWF::VolumeSnapshot
{
	/// XWF_SelectVolumeSnapshot
	using fptr_XWF_SelectVolumeSnapshot = LONG(__stdcall*) (HANDLE hVolume);
	fptr_XWF_SelectVolumeSnapshot XWF_SelectVolumeSnapshot;

	/// XWF_GetVSProp
	using fptr_XWF_GetVSProp = INT64(__stdcall*) (LONG nPropType, PVOID pBuffer);
	fptr_XWF_GetVSProp XWF_GetVSProp;

	/// Flag                                            Value   Description
	constexpr auto XWF_GetVSProp_PropType_GetSpecialItemID = 10;   // Used to get the ID of a special item in the volume snapshot.
	//constexpr auto XWF_GetVSProp_PropType_HASHTYPE    = 11;   // Hash type - Deprecated.
	constexpr auto XWF_GetVSProp_PropType_GetHashOneType = 20;   // Get the Primary hash type.
	constexpr auto XWF_GetVSProp_PropType_GetHashTwoType = 21;   // Get the Secondary hash type.
	constexpr auto XWF_GetVSProp_PropType_SetHashOneType = 25;   // Set the Primary hash type. Available from v19.7.
	constexpr auto XWF_GetVSProp_PropType_SetHashTwoType = 26;   // Set the Secondary hash type. Available from v19.7.

	enum struct XWF_GetVSProp_SpecialItem
	{
		RootDirectory = 1, // Root Directory.
		PathUnknownDirectory = 2, // Path Unknown Directory.
		CarvedFilesDirectory = 4, // Carved Files Directory.
		FreeSpaceFile = 5, // Free Space File.
		SystemVolumeInformationDirectory = 11, // System Volume Information Directory.
		WindowsEDBFile = 12 // Windows.edb file.
	};

	/// XWF_GetItemCount
	using fptr_XWF_GetItemCount = DWORD(__stdcall*) (LPVOID pReserved);
	fptr_XWF_GetItemCount XWF_GetItemCount;

	/// XWF_GetFileCount
	using fptr_XWF_GetFileCount = DWORD(__stdcall*) (LONG nDirID);
	fptr_XWF_GetFileCount XWF_GetFileCount;

	/// 	XWF_GetSpecialItemID
	using fptr_XWF_GetSpecialItemID = DWORD(__stdcall*) (LONG nDirID);
	fptr_XWF_GetSpecialItemID XWF_GetSpecialItemID;

	/// XWF_CreateItem
	using fptr_XWF_CreateItem = long int(__stdcall*) (wchar_t* lpName, DWORD nCreationFlags);
	fptr_XWF_CreateItem XWF_CreateItem;

	/// XWF_CreateFile
	using fptr_XWF_CreateFile = long int(__stdcall*) (LPWSTR pName, DWORD nCreationFlags, LONG nParentItemID, PVOID pSourceInfo);
	fptr_XWF_CreateFile XWF_CreateFile;

	/// XWF_FindItem1
	using  fptr_XWF_FindItem1 = long int(__stdcall*) (LONG nParentItemID, LPWSTR lpName, DWORD nFlags, LONG nSearchStartItemID);
	fptr_XWF_FindItem1 XWF_FindItem1;

	/// XWF_Mount
	using fptr_XWF_Mount = BOOL(__stdcall*) (LONG nDirID, LPWSTR lpMountPath, LPVOID lpReserved);
	fptr_XWF_Mount XWF_Mount;

	/// XWF_Unmount
	using fptr_XWF_Unmount = BOOL(__stdcall*) (LPWSTR lpMountPath);
	fptr_XWF_Unmount XWF_Unmount;
}
#pragma endregion VolumeSnapshot

#pragma region VolumeSnapshotItem
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#D
/// </summary>
export namespace XWF::VolumeSnapshotItem
{
	/// XWF_GetItemName
	using fptr_XWF_GetItemName = LPWSTR(__stdcall*) (LONG nItemID);
	fptr_XWF_GetItemName XWF_GetItemName;

	/// XWF_SetItemName
	using fptr_XWF_SetItemName = VOID(__stdcall*) (LONG nItemID, LPWSTR lpName);
	fptr_XWF_SetItemName XWF_SetItemName;

	/// XWF_GetItemSize (tested)
	using fptr_XWF_GetItemSize = INT64(__stdcall*) (LONG nItemID);
	fptr_XWF_GetItemSize XWF_GetItemSize;

	/// XWF_SetItemSize
	using fptr_XWF_SetItemSize = void(__stdcall*) (LONG nItemID, INT64 nSize);
	fptr_XWF_SetItemSize XWF_SetItemSize;

	/// XWF_GetItemOfs
	using fptr_XWF_GetItemOfs = void(__stdcall*) (LONG nItemID, INT64* lpDefOfs, INT64* lpStartSector);
	fptr_XWF_GetItemOfs XWF_GetItemOfs;

	/// XWF_SetItemOfs
	using fptr_XWF_SetItemOfs = void(__stdcall*) (LONG nItemID, INT64 nDefOfs, INT64 nStartSector);
	fptr_XWF_SetItemOfs XWF_SetItemOfs;

	/// XWF_GetItemInformation
	using fptr_XWF_GetItemInformation = INT64(__stdcall*) (LONG nItemID, LONG nInfoType, LPBOOL lpSuccess);
	fptr_XWF_GetItemInformation XWF_GetItemInformation;

	/// Flag                                                                    Value   Description
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_OriginalID = 1;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_Attribute = 2;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_Flags = 3;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_Deletion = 4;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_Classification = 5;    // E.g. extracted e-mail message, alternate data stream, etc.
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_LinkCount = 6;    // Hard-link count.
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_FileCount = 11;   // How many child objects exist recursively that are files.
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_CreationTime = 32;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_ModificationTime = 33;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_LastAccessTime = 34;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_EntryModificationTime = 35;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_DeletionTime = 36;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_InternalCreationTime = 37;
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_FLAGS_Set = 64;   // Indicates only flags that should be set, others remain unchanged.
	constexpr auto XWF_GetItemInformation_InfoTypeFlag_FLAGS_Remote = 65;   // Indicates flags that should be removed, others remain unchanged.

	/// Flag for returned value (INT64) when using XWF_GetItemInformation(nItemID, XWF::VolumeSnapshotItem::XWF_GetItemInformation_InfoTypeFlag_Flags, lpSuccess); 
	/// Flag                                                                Value           Description
	constexpr auto XWF_Item_Info_Flags_return_Directory = 1;            // Is a directory.
	constexpr auto XWF_Item_Info_Flags_return_ChildObjects = 2;            // Has child objects(for files only).
	constexpr auto XWF_Item_Info_Flags_return_SubDirectories = 4;            // Has subdirectories(for directories only).
	constexpr auto XWF_Item_Info_Flags_return_VirtualItem = 8;            // Is a virtual item.
	constexpr auto XWF_Item_Info_Flags_return_HiddenByExaminer = 10;           // Hidden by examiner.
	constexpr auto XWF_Item_Info_Flags_return_Tagged = 20;           // Tagged.
	constexpr auto XWF_Item_Info_Flags_return_TaggedPartially = 40;           // Tagged partially.
	constexpr auto XWF_Item_Info_Flags_return_ViewedByExaminer = 80;           // Viewed by examiner.

	constexpr auto XWF_Item_Info_Flags_return_FileSystemTimestampNotUTC = 0x100;        // file system timestamps not in UTC
	constexpr auto XWF_Item_Info_Flags_return_InternalCreationTimestampNotUTC = 0x200;        // internal creation timestamp not in UTC
	constexpr auto XWF_Item_Info_Flags_return_FATTimestamps = 0x400;        // FAT timestamps
	constexpr auto XWF_Item_Info_Flags_return_OriginatesFromNTFS = 0x800;        // originates from NTFS
	constexpr auto XWF_Item_Info_Flags_return_UNIXPermissions = 0x00001000;   // Unix permissions instead of Windows attributes
	constexpr auto XWF_Item_Info_Flags_return_HasExaminerComment = 0x00002000;   // has examiner comment
	constexpr auto XWF_Item_Info_Flags_return_HasExtractedMetadata = 0x00004000;   // has extracted metadata
	constexpr auto XWF_Item_Info_Flags_return_FileContentsUnknown = 0x00008000;   // file contents totally unknown

	constexpr auto XWF_Item_Info_Flags_return_FileContentsPartiallyUnknown = 0x00010000;   // file contents partially unknown
	constexpr auto XWF_Item_Info_Flags_return_Reserved = 0x00020000;   // reserved
	constexpr auto XWF_Item_Info_Flags_return_HashOneComputed = 0x00040000;   // hash 1 already computed
	constexpr auto XWF_Item_Info_Flags_return_HasDuplicates = 0x00080000;   // has duplicates
	constexpr auto XWF_Item_Info_Flags_return_HashTwoComputed = 0x00100000;   // hash 2 already computed(since v18.0)
	constexpr auto XWF_Item_Info_Flags_return_CategorisedIrrelevant = 0x00200000;   // categorized as irrelevant
	constexpr auto XWF_Item_Info_Flags_return_CategorisedNotable = 0x00400000;   // categorized as notable
	constexpr auto XWF_Item_Info_Flags_return_UncategorisedButKnown = 0x00600000;   // uncategorized, but known(both flags!, v18.9 + )
	constexpr auto XWF_Item_Info_Flags_return_VolumeShadowCopy = 0x00800000;   // if in NTFS : found in volume shadow copy

	constexpr auto XWF_Item_Info_Flags_return_DeletedButKnownContents = 0x01000000;   // deleted files with known original contents
	constexpr auto XWF_Item_Info_Flags_return_FileConsistencyOk = 0x02000000;   // file format consistency OK
	constexpr auto XWF_Item_Info_Flags_return_FileConsistencyNotOk = 0x04000000;   // file format consistency not OK
	constexpr auto XWF_Item_Info_Flags_return_FileArchivedExplored = 0x10000000;   // file archive already explored(v17.6 + )
	constexpr auto XWF_Item_Info_Flags_return_EmailArchiveProcessed = 0x20000000;   // e - mail archive already processed(v17.6 + )
	constexpr auto XWF_Item_Info_Flags_return_EmbeddedDataUncovered = 0x40000000;   // embedded data already uncovered(v17.6 + )
	constexpr auto XWF_Item_Info_Flags_return_MetadataExtracted = 0x80000000;   // metadata extraction already applied(v17.6 + )

	constexpr auto XWF_Item_Info_Flags_return_FileEmbeddedInOtherFileLinearly = 0x100000000;  // file embedded in other file linearly(v17.7 + ) *
	constexpr auto XWF_Item_Info_Flags_return_FileContentStoredExternally = 0x200000000;  // file whose contents is stored externally(v17.7 + ) *
	constexpr auto XWF_Item_Info_Flags_return_AlternativeData = 0x400000000;  // alternative data / a via XWF_OpenItem(v18.9 + ) *

	/// Flag for returned value (INT64) when using XWF_GetItemInformation(nItemID, XWF::VolumeSnapshotItem::XWF_GetItemInformation_InfoTypeFlag_Deletion, lpSuccess); 
	/// Flag                                             Value   Description
	constexpr auto XWF_Item_Info_Deletion_Existing = 0; //= existing
	/// > 0 = not existing                     
	constexpr auto XWF_Item_Info_Deletion_PreviouslyExistingPossiblyRecoverable = 1; //= previously existing, possibly recoverable
	constexpr auto XWF_Item_Info_Deletion_PreviouslyExistingFirstClusterOverwritten = 2; //= previously existing, first cluster overwritten or unknown
	constexpr auto XWF_Item_Info_Deletion_RenamedOrMovedPossiblyRecoverable = 3; //= renamed / moved, possibly recoverable
	constexpr auto XWF_Item_Info_Deletion_RenamedOrMovedFirstClusterOverwritten = 4; //= renamed / moved, first cluster overwritten or unknown
	constexpr auto XWF_Item_Info_Deletion_CarvedFile = 5; //= carved file(since v19.3 SR - 3, used to be 1)

	/// XWF_SetItemInformation
	using fptr_XWF_SetItemInformation = BOOL(__stdcall*) (LONG nItemID, LONG nInfoType, INT64 nInfoValue);
	fptr_XWF_SetItemInformation XWF_SetItemInformation;

	/// XWF_GetItemType
	using fptr_XWF_GetItemType = LONG(__stdcall*) (LONG nItemID, wchar_t* lpTypeDescr, DWORD nBufferLenAndFlags);
	fptr_XWF_GetItemType XWF_GetItemType;

	/// XWF_SetItemType
	using fptr_XWF_SetItemType = void(__stdcall*) (LONG nItemID, wchar_t* lpTypeDescr, LONG nTypeStatus);
	fptr_XWF_SetItemType XWF_SetItemType;

	/// XWF_GetItemParent
	using fptr_XWF_GetItemParent = LONG(__stdcall*) (LONG nItemID);
	fptr_XWF_GetItemParent XWF_GetItemParent;

	constexpr auto XWF_XWF_GetItemParent_RootObject = -1;

	/// XWF_SetItemParent
	using fptr_XWF_SetItemParent = void(__stdcall*) (LONG nChildItemID, LONG nParentItemID);
	fptr_XWF_SetItemParent XWF_SetItemParent;

	/// XWF_GetHashSetAssocs
	using fptr_XWF_GetHashSetAssocs = LONG(__stdcall*) (LONG nItemID, LPWSTR lpBuffer, LONG nBufferLen);
	fptr_XWF_GetHashSetAssocs XWF_GetHashSetAssocs;

	/// XWF_GetReportTableAssocs
	using fptr_XWF_GetReportTableAssocs = LONG(__stdcall*) (LONG nItemID, wchar_t* lpBuffer, LONG nBufferLen);
	fptr_XWF_GetReportTableAssocs XWF_GetReportTableAssocs;

	/// XWF_AddToReportTable
	using fptr_XWF_AddToReportTable = LONG(__stdcall*) (LONG nItemID, wchar_t* lpReportTableName, DWORD nFlags);
	fptr_XWF_AddToReportTable XWF_AddToReportTable;

	/// XWF_GetComment
	using fptr_XWF_GetComment = wchar_t* (__stdcall*) (LONG nItemID);
	fptr_XWF_GetComment XWF_GetComment;

	/// XWF_AddComment (tested)
	using fptr_XWF_AddComment = BOOL(__stdcall*) (LONG nItemID, wchar_t* lpComment, DWORD nFlagsHowToAdd);
	fptr_XWF_AddComment XWF_AddComment;

	/// XWF_GetExtractedMetadata
	using fptr_XWF_GetExtractedMetadata = LPWSTR(__stdcall*) (LONG nItemID);
	fptr_XWF_GetExtractedMetadata XWF_GetExtractedMetadata;

	/// XWF_AddExtractedMetadata
	using fptr_XWF_AddExtractedMetadata = BOOL(__stdcall*) (LONG nItemID, LPWSTR lpComment, DWORD nFlagsHowToAdd);
	fptr_XWF_AddExtractedMetadata XWF_AddExtractedMetadata;

	/// XWF_GetHashValue
	using fptr_XWF_GetHashValue = BOOL(__stdcall*) (LONG nItemID, LPVOID lpBuffer);
	fptr_XWF_GetHashValue XWF_GetHashValue;

	/// XWF_SetHashValue
	using fptr_XWF_SetHashValue = BOOL(__stdcall*) (LONG nItemID, LPVOID lpHash, DWORD nParam);
	fptr_XWF_SetHashValue XWF_SetHashValue;

	/// XWF_GetCellText
	using fptr_XWF_GetCellText = BOOL(__stdcall*) (LONG nItemID, LPVOID lpPointer, DWORD nFlags, WORD nColIndex, LPWSTR lpBuffer, DWORD nBufferLen);
	fptr_XWF_GetCellText XWF_GetCellText;

	/// XWF_SetItemDataRuns
	using fptr_XWF_SetItemDataRuns = VOID(__stdcall*) (LONG nItemID, LPVOID lpBuffer);
	fptr_XWF_SetItemDataRuns XWF_SetItemDataRuns;
}
#pragma endregion VolumeSnapshotItem

#pragma region FileContent
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#E
/// </summary>
export namespace XWF::FileContent
{
	/// XWF_GetMetadata
	using fptr_XWF_GetMetadata = LPWSTR(__stdcall*) (LONG nItemID, HANDLE hItem);
	fptr_XWF_GetMetadata XWF_GetMetadata;

	/// XWF_GetMetadataEx
	using fptr_XWF_GetMetadataEx = LPVOID(__stdcall*) (HANDLE hItem, PDWORD lpnFlags);
	fptr_XWF_GetMetadataEx XWF_GetMetadataEx;

	/// XWF_PrepareTextAccess
	using fptr_XWF_PrepareTextAccess = DWORD(__stdcall*) (DWORD nFlags, LPSTR lpLangs);
	fptr_XWF_PrepareTextAccess XWF_PrepareTextAccess;

	/// XWF_GetText
	using fptr_XWF_GetText = LPVOID(__stdcall*) (HANDLE hItem, DWORD nFlags, INT* lpnResult, PDWORD lpnBufUsedSize, PDWORD lpnBufAllocSize);
	fptr_XWF_GetText XWF_GetText;

#pragma pack(push, 2)
	/// <summary>
	/// nSize must be set to the size of the structure. nItemID and hItem must be provided as well. You may specify any combination of the below flags that makes sense for you. The dimensions of the picture in pixels (nWidth and nHeight) are returned, as well as the size in bytes (nResSize). If you specify a non-zero value for nWidth and/or nHeight for input, it will be interpreted as the maximum width or height that you would like for the resulting image, and the image will be shrunk accordingly (resized, not cropped), if its dimensions are not smaller than that anyway, while preserving the aspect ratio of the original picture.
	/// nFlags:
	/// 0x01 : get a memory buffer that starts with an appropriate Windows Bitmap header
	/// 0x02 : align line offsets at 4 - byte boundaries
	/// 0x04 : vertically flip image, physically(reverse the order of pixel lines in the memory buffer)
	/// 0x07 : create a standard Windows BMP image(suitable combination of flags 0x01, 0x02, and 0x04)
	/// 0x08 : vertically flip image, logically(only in conjunction with 0x01, using a negative height in the BMP header)
	/// 0x10 : horizontally flip image, physically(reverse the order of the pixels in each line in the memory buffer)
	/// </summary>
	struct RasterImageInfo
	{
		DWORD nSize;
		LONG nItemID;
		HANDLE hItem;
		DWORD nFlags;
		DWORD nWidth;
		DWORD nHeight;
		DWORD nResSize;
	};
#pragma pack(pop)

	/// XWF_GetRasterImage
	using fptr_XWF_GetRasterImage = LPVOID(__stdcall*) (struct RasterImageInfo* RIInfo);
	fptr_XWF_GetRasterImage XWF_GetRasterImage;
}
#pragma endregion FileContent

#pragma region Search
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#F
/// </summary>
export namespace XWF::Search
{
#pragma pack(push, 2)
	/// <summary>
	///  nSize must be set to the size of the respective structure in bytes and should cover at least all member variables up to nSearchWindow.
	/// 
	/// hVolume: Currently must be 0, function is always applied to the active volume
	/// 
	/// lpSearchTerms : Delimited by line breaks; will be added to the case if not yet existing.
	/// 
	/// nFlags: Can be combined only as known from the user interface.For example, the whole words options have no effect if GREP is selected.Otherwise the result is undefined.
	/// see: XWF_SEARCH_*
	/// 
	/// Only if the XWF_SEARCH_CALLPSH flag is specified, X - Ways Forensics will call XT_ProcessSearchHit(), if exported, for each hit.You may use that function to monitor and filter the search hits that you get, for example to prevent the output of irrelevant search hits or to keep knowledge of all search hits to yourself.Other X - Tensions' XT_ProcessSearchHit() function will not be called. Instead of using XT_ProcessSearchHit(), in later versions of the API only, you can traverse the list of all search hits after completion and check which ones are for the search terms that you had created/searched for.
	/// 
	/// nSearchWindow: 0 for standard search window length
	/// 
	/// lpLatin1Alphabet : Optional.Supported as of v20.0.If not NULL, points to a null - terminated sequence of letters of Western European languages(in the Latin 1 code page with 1 byte per character) that you consider to be part of words, which defines word boundaries and will change the alphabet settings in X - Ways Forensics.Up to 159 characters are currently utilized.The previously used alphabet will be lost.
	/// 
	/// lpNonLatin1Alphabet : Optional.Supported as of v20.0.If not NULL, points to a null - terminated sequence of characters(in UTF - 16) that you consider to be part of words, which defines word boundaries and will change the alphabet settings in X - Ways Forensics.Up to 99 characters are currently utilized.The previously used alphabet will be lost.
	/// </summary>
	struct SearchInfo
	{
		DWORD iSize;
		LPWSTR lpSearchTerms;
		DWORD nFlags;
		DWORD nSearchWindow;
	};
#pragma pack(pop)

#pragma pack(push, 2)
	/// <summary>
	/// See: https://learn.microsoft.com/en-gb/windows/win32/intl/code-page-identifiers?redirectedfrom=MSDN
	/// </summary>
	struct CodePages
	{
		DWORD iSize;
		WORD nCodePage1;
		WORD nCodePage2;
		WORD nCodePage3;
		WORD nCodePage4;
		WORD nCodePage5;
	};
#pragma pack(pop)

	/// XWF_Search
	using fptr_XWF_Search = LONG(__stdcall*) (SearchInfo* SInfo, CodePages* CPages);
	fptr_XWF_Search XWF_Search;

	/// Part of the flags for SearchInfo struct:
	/// nFlags: Can be combined only as known from the user interface. For example, the whole words options have no effect if GREP is selected. Otherwise the result is undefined.
	/// Flag                                            Value           Description
	constexpr auto XWF_SearchInfo_Flag_Logical = 0x00000001;   // Logical search instead of physical search (only logical search currently available).
	constexpr auto XWF_SearchInfo_Flag_TaggedObjects = 0x00000004;   // Tagged objects in volume snapshot only.
	constexpr auto XWF_SearchInfo_Flag_MatchCase = 0x00000010;   // Match case.
	constexpr auto XWF_SearchInfo_Flag_WholeWords = 0x00000020;   // Whole words only.
	constexpr auto XWF_SearchInfo_Flag_GREP = 0x00000040;   // GREP syntax.
	constexpr auto XWF_SearchInfo_Flag_Overlapped = 0x00000080;   // Allow overlapping hits.
	constexpr auto XWF_SearchInfo_Flag_CoverSlack = 0x00000100;   // Cover slack space.
	constexpr auto XWF_SearchInfo_Flag_CoverSlackFreeSpaceTransition = 0x00000200;   // Cover slack/free space transition.
	constexpr auto XWF_SearchInfo_Flag_DecodeText = 0x00000400;   // Decode text in standard file types.
	constexpr auto XWF_SearchInfo_Flag_DecodeTextEx = 0x00000800;   // Decode text in specified file types // not yet supported .
	constexpr auto XWF_SearchInfo_Flag_OneHitPerFile = 0x00001000;   // 1 Hit per file needed only.
	constexpr auto XWF_SearchInfo_Flag_WholeWordsTwo = 0x00004000;   // Whole words only for search terms that are specially marked.
	constexpr auto XWF_SearchInfo_Flag_GREPTwo = 0x00008000;   // GREP syntax only search terms that start with "grep:".
	constexpr auto XWF_SearchInfo_Flag_OmitIrrelevant = 0x00010000;   // Omit files classified as irrelevant.
	constexpr auto XWF_SearchInfo_Flag_OmitHidden = 0x00020000;   // Omit hidden files.
	constexpr auto XWF_SearchInfo_Flag_OmitFiltered = 0x00040000;   // Omit files that are filtered out.
	constexpr auto XWF_SearchInfo_Flag_DataReduction = 0x00080000;   // Recommendable data reduction.
	constexpr auto XWF_SearchInfo_Flag_OmitDirs = 0x00100000;   // Omit directories.
	constexpr auto XWF_SearchInfo_Flag_CallProcessSearchHit = 0x01000000;   // Only if the XWF_SEARCH_CALLPSH flag is specified, X-Ways Forensics will call XT_ProcessSearchHit(), if exported, for each hit. You may use that function to monitor and filter the search hits that you get, for example to prevent the output of irrelevant search hits or to keep knowledge of all search hits to yourself. Other X-Tensions' XT_ProcessSearchHit() function will not be called. Instead of using XT_ProcessSearchHit(), in later versions of the API only, you can traverse the list of all search hits after completion and check which ones are for the search terms that you had created/searched for.
	constexpr auto XWF_SearchInfo_Flag_DisplayHits = 0x04000000;   // Display search hit list when the search completes.

	/// XWF_GetSearchTerm
	using  fptr_XWF_GetSearchTerm = LPWSTR(__stdcall*) (LONG nSearchTermID, LPVOID pReserved);
	fptr_XWF_GetSearchTerm XWF_GetSearchTerm;

	/// XWF_AddSearchTerm
	using fptr_XWF_AddSearchTerm = LONG(__stdcall*) (LPWSTR lpSearchTermName, DWORD nFlags);
	fptr_XWF_AddSearchTerm XWF_AddSearchTerm;

	/// XWF_ManageSearchTerm - Available in v20.0 and later.
	/// <summary>
	/// 
	/// Set nProperty to 0 to delete the specified search term and all its search hits in all evidence objects. That is more efficient than deleting the search hits one by one.
	/// If nSearchTermID is -1, that deletes all search terms and all their search hits.
	/// pFlags should be set to NULL and is currently unused.
	/// The return value of the function is 1 for presumed success, 0 for failure.
	/// 
	/// Set nProperty to 1 to manage the flags that define the properties of the search terms whose ID you specify. See XWF_ManageSearchTerm_Flag_* for the available flags.
	/// You can retrieve these flags through the function return value (if pValue is NULL) or set those flags (if pValue is not NULL, but please know what you are doing).
	/// If you set the flags, a return value of 1 indicates success, 0 indicates failure.
	/// </summary>
	using  fptr_XWF_ManageSearchTerm = DWORD(__stdcall*)(LONG nSearchTermID, LONG nProperty, LPVOID pValue);
	fptr_XWF_ManageSearchTerm XWF_ManageSearchTerm;

	constexpr auto XWF_ManageSearchTerm_nProperty_Delete = 0x0000;   // Delete specified search term.
	constexpr auto XWF_ManageSearchTerm_nProperty_ManageFlags = 0x0001;   // Manage search term flags. Set `pValue` to NULL to retrieve the flags, or to a pointer to a DWORD value to set the flags.
	constexpr auto XWF_ManageSearchTerm_nProperty_Rename = 0x0002;   // Rename search term. Set `pValue` to a pointer to a null-terminated UTF-16 string with the new name.


	///
	/// Set nProperty to 2 to rename the search term, e.g. assign a more user-friendly name to a complicated regular expression.
	/// In that case pValue must point to a null-terminated UTF-16 string.
	/// Available in v20.3 and later. The null-terminated UTF-16 string pointed to by lpSearchTerm may be truncated in X-Ways Forensics.
	/// Currently, as of v20.3, up to 90 characters are supported. A return value of 1 indicates success, 0 indicates failure.
	///
	// Flag                                     Value       Description
	constexpr auto XWF_ManageSearchTerm_Flag_LastUsedCaseSensitive = 0x0002;   // Last used for a case-sensitive search.
	constexpr auto XWF_ManageSearchTerm_Flag_GREPButGotFriendly = 0x0004;   // Based on a GREP expression, but got a "friendly" name.
	constexpr auto XWF_ManageSearchTerm_Flag_ForcedANDCombination = 0x0010;   // Forced in an AND combination.
	constexpr auto XWF_ManageSearchTerm_Flag_SelectedInSearchTermList = 0x0040;   // Selected in the search term list.
	constexpr auto XWF_ManageSearchTerm_Flag_SearchHitsExcluded = 0x0080;   // Search hits are excluded.
	constexpr auto XWF_ManageSearchTerm_Flag_GREPExpression = 0x0100;   // GREP expression.
	constexpr auto XWF_ManageSearchTerm_Flag_SelectedForFilter = 0x0200;   // Selected for filter.
	constexpr auto XWF_ManageSearchTerm_Flag_CreatedResultOfDataComparison = 0x0400;   // Created as a result of data comparison.
	constexpr auto XWF_ManageSearchTerm_Flag_UserSearchHits = 0x0800;   // For user search hits (defined manually by the user).
	constexpr auto XWF_ManageSearchTerm_Flag_WordBoundaryStart = 0x1000;   // Search hits are checked for a word boundary at the start.
	constexpr auto XWF_ManageSearchTerm_Flag_WordBoundaryEnd = 0x2000;   // Search hits are checked for a word boundary at the end.
	constexpr auto XWF_ManageSearchTerm_Flag_BlockHashMatch = 0x4000;   // Search hit represents a data area with a block hash match.

#pragma pack(push, 2)
	/// <summary>
	/// <para>
	///     nSize:
	/// </para>
	///     <para>
	///         Size of the record. The record is packed.In future versions of the API the record may be larger if more
	///		    fields are provided.But even then you can still address the record components as you know them.
	///     </para>
	/// <para>
	///     nRelOfs:
	/// </para>
	///     <para>
	///         Relative offset of the search hit within its respective file, if applicable, otherwise -1.
	///			You may change the offset if that helps to improve the quality of the search hit.
	///     </para>
	/// <para>
	///     nAbsOfs:
	/// </para>
	///     <para>
	///         Absolute offset of the search hit from the point of the volume, if available, otherwise a negative value.
	///         You may change the offset if that helps to improve the quality of the search hit.
	///     </para>
	/// <para>
	///     lpFlags:
	/// </para>
	///     <para>
	///         Flags that define the properties of the search hit.You may change the flags,
	///	        for example to mark a hit as notable or to discard it. See XWF_SEARCHHITINFO_*
	///     </para>
	///	<para>
	///     lpOptionalHitPtr:
	/// </para>
	///     <para>
	///         Pointer to the search hit in a memory buffer with the original data that was searched.
	///			Provided only if XT_ProcessSearchHit() is called during a search, not necessarily when
	///			later applied to an existing search hit, and only for search hits of the simultaneous search,
	///			not for index searches.
	///			NULL if not provided.
	///			Do not make any assumption about how many bytes before or after the search hit can be read in memory.
	///     </para>
	///	<para>
	///     nSearchTermID:
	/// </para>
	///     <para>
	///         You may assign a search hit to a different search term by changing this ID.
	///     </para>
	///	<para>
	///     nLength:
	/// </para>
	///     <para>
	///         Size of the search hit in bytes.You may change that size if that helps to improve the quality of the search hit.
	///     </para>
	///	<para>
	///     nCodePage:
	/// </para>
	///     <para>
	///         See this web page for possible code page identifiers.
	///     </para>
	///	<para>
	///     hItemOrVolume:
	/// </para>
	///     <para>
	///         Part of the structure in v16.5 and later.Specifies the item(for a logical search) or volume(for a physical search)
	///			in which a search hit was found.Useful if you wish to read more data from this item.Provided only if
	///			XT_ProcessSearchHit() is called during a search, only for search hits of simultaneous search.
	///			0 for index searches,
	///			0 when later applied to an existing search hit.
	///     </para>
	/// </summary>
	struct SearchHitInfo
	{
		DWORD nSize;
		LONG nItemID;
		INT64 nRelOfs;
		INT64 nAbsOfs;
		PVOID lpOptionalHitPtr;
		WORD nSearchTermID;
		WORD nLength;
		WORD nCodePage;
		WORD nFlags;
		HANDLE hOptionalItemOrVolume;
	};
#pragma pack(pop)

	// Flag                                     Value       Description
	constexpr auto XWF_SearchHitInfo_Flag_IndexHit = 0x0001;   // Index search hit
	constexpr auto XWF_SearchHitInfo_Flag_AlternativeText = 0x0002;   // Resides in alternative text related to the file, and nRelOfs is based on that text, it's not an offset in the file
	constexpr auto XWF_SearchHitInfo_Flag_Notable = 0x0004;   // Notable
	constexpr auto XWF_SearchHitInfo_Flag_Deleted = 0x0008;   // Deleted, set this flag to discard the search hit
	constexpr auto XWF_SearchHitInfo_Flag_Special = 0x0020;   // Special search hit : found by user or block hash matching or comparison
	constexpr auto XWF_SearchHitInfo_Flag_Report = 0x0040;   // To be included in case report
	constexpr auto XWF_SearchHitInfo_Flag_SlackSpace = 0x0040;   // Contained in slack space or an uninitialized end portion of a file
	constexpr auto XWF_SearchHitInfo_Flag_TextExtracted = 0x0100;   // Flag 0x0001 is set, and the search hit was found in text extracted from the file via file format specific decoding(v20.3 and later)
	constexpr auto XWF_SearchHitInfo_Flag_TextOCR = 0x0200;   // Flag 0x0001 is set, and the search hit was found in text derived by OCR(v20.3 and later)
	constexpr auto XWF_SearchHitInfo_Flag_DirectoryMeta = 0x0400;   // Flag 0x0001 is set, and the search hit was found in a directory browser column such as Name, Owner, Author, Metadata etc. (v20.3 and later)

	/// XWF_AddSearchHit
	using fptr_XWF_AddSearchHit = LONG(__stdcall*) (struct SearchHitInfo* pInfo);
	fptr_XWF_AddSearchHit XWF_AddSearchHit;

	/// XWF_GetSearchHit
	using fptr_XWF_GetSearchHit = LONG(__stdcall*) (DWORD nSearchHitNo, struct SearchHitInfo* pInfo);
	fptr_XWF_GetSearchHit XWF_GetSearchHit;

	/// XWF_SetSearchHit
	using fptr_XWF_SetSearchHit = LONG(__stdcall*) (DWORD nSearchHitNo, struct SearchHitInfo* pInfo);
	fptr_XWF_SetSearchHit XWF_SetSearchHit;
}
#pragma endregion Search

#pragma region Event
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#G
/// </summary>
export namespace XWF::Event
{
#pragma pack(push, 2)
	/// <summary>
	///  nSize: Size of this structure. Must be properly initialized.
	/// 
	/// nEvtType: 0 for unknown.File system events : 100 + .File metadata events : 1000 + .Internet events : 8000 + .Messaging events : 10000 + .Operating system events : 14000 + .Windows event log events : 15000 + .Windows registry events : 20000 + .
	/// 
	/// nFlags :
	/// 0x04 : low timestamp precision, only seconds
	/// 0x08 : low timestamp precision, only even numbers of seconds
	/// 0x10 : very low timestamp precision, only date
	/// 0x20 : timestamp in local time, not UTC
	/// 0x40 : designates an outdated timestamp
	/// 
	/// nItemID : If the event is related to a particular object in the volume snapshot(file or directory), that object's ID, otherwise -1.
	/// 
	/// nOfs : Offset where the timestamp was found in the volume or (if nItemID unequal to - 1) within the object in the volume snapshot. - 1 if unknown.
	/// 
	/// lpDescr : Optional null - terminated textual description of the event, preferably in 7 - bit ASCII or else in UTF - 8. Will be truncated internally after 255 bytes.NULL if not provided.
	/// </summary>
	struct EventInfo
	{
		LONG iSize;
		HANDLE hEvidence;
		DWORD nEvtType;
		DWORD nFlags;
		FILETIME TimeStamp;
		LONG nItemID;
		INT64 nOfs;
		LPSTR lpDescr;
	};
#pragma pack(pop)

	/// XWF_AddEvent
	using fptr_XWF_AddEvent = LONG(__stdcall*) (struct EventInfo* Evt);
	fptr_XWF_AddEvent XWF_AddEvent;

	/// XWF_GetEvent
	using fptr_XWF_GetEvent = DWORD(__stdcall*) (DWORD nEventNo, struct EventInfo* Evt);
	fptr_XWF_GetEvent XWF_GetEvent;
}
#pragma endregion Event

#pragma region EvidenceContainer
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#H
/// </summary>
export namespace XWF::EvidenceContainer
{
	/// XWF_CreateContainer
	using fptr_XWF_CreateContainer = HANDLE(__stdcall*) (LPWSTR lpFileName, DWORD nFlags, LPVOID pReserved);
	fptr_XWF_CreateContainer XWF_CreateContainer;

	/// Flag                             Value           Description
	constexpr auto XWF_CreateContainer_Flag_Open = 0x00000001;   // Opens an existing container, all other flags ignored.
	constexpr auto XWF_CreateContainer_Flag_Reserved = 0x00000002;   // Do not use.
	//constexpr auto XWF_CreateContainer_Flag_XWFS2 = 0x00000002;   // Use new XWFS2 file system.
	constexpr auto XWF_CreateContainer_Flag_Secure = 0x00000004;   // Mark this container as to be filled indirectly/secure.
	constexpr auto XWF_CreateContainer_Flag_TopLevel = 0x00000008;   // Include evidence object names as top directory level.
	constexpr auto XWF_CreateContainer_Flag_IncludeDirectoryData = 0x00000010;   // Include directory data.
	constexpr auto XWF_CreateContainer_Flag_FileParents = 0x00000020;   // Allow files as parents of files.
	constexpr auto XWF_CreateContainer_Flag_UserReportTables = 0x00000100;   // Export associations with user-created report table.
	constexpr auto XWF_CreateContainer_Flag_SystemReportTables = 0x00000200;   // Export associations with system-created report tables (currently requires 0x100).
	constexpr auto XWF_CreateContainer_Flag_AllComments = 0x00000800;   // Pass on comments. v18.9 and earlier.
	constexpr auto XWF_CreateContainer_Flag_TopLevelDirectoryPartial = 0x00001000;   // Include direct evidence object name as top directory level.
	//constexpr auto XWF_CreateContainer_Flag_OPTIMIZE1 = 0x00001000;   // Optimize for > 1,000 items.
	//constexpr auto XWF_CreateContainer_Flag_OPTIMIZE2 = 0x00002000;   // Optimize for > 50,000 items.
	//constexpr auto XWF_CreateContainer_Flag_OPTIMIZE3 = 0x00004000;   // Optimize for > 250,000 items.
	//constexpr auto XWF_CreateContainer_Flag_OPTIMIZE4 = 0x00008000;   // Optimize for > 1 million items.

	/// XWF_CopyToContainer
	using  fptr_XWF_CopyToContainer = LONG(__stdcall*) (HANDLE hContainer, HANDLE hItem, DWORD nFlags, DWORD nMode, INT64 nStartOfs, INT64 nEndOfs, LPVOID pReserved);
	fptr_XWF_CopyToContainer XWF_CopyToContainer;

	/// XWF_CloseContainer
	using fptr_XWF_CloseContainer = LONG(__stdcall*) (HANDLE hContainer, LPVOID pReserved);
	fptr_XWF_CloseContainer XWF_CloseContainer;
}
#pragma endregion EvidenceContainer

#pragma region DataWindow
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#I
/// </summary>
export namespace XWF::DataWindow
{
	/// XWF_GetWindow
	using fptr_XWF_GetWindow = HWND(__stdcall*)(WORD nWndNo, WORD nWndIndex);
	fptr_XWF_GetWindow XWF_GetWindow;

	/// XWF_GetColumnTitle
	using fptr_XWF_GetColumnTitle = BOOL(__stdcall*)(WORD nWndNo, WORD nColIndex, LPWSTR lpBuffer);
	fptr_XWF_GetColumnTitle XWF_GetColumnTitle;
}
#pragma endregion DataWindow

#pragma region Miscellaneous
/// <summary>
/// See: https://www.x-ways.net/forensics/x-tensions/XWF_functions.html#J
/// </summary>
export namespace XWF::Miscellaneous
{
	/// XWF_OutputMessage (tested)
	using fptr_XWF_OutputMessage = void(__stdcall*)(LPWSTR lpMessage, DWORD nFlags);
	fptr_XWF_OutputMessage XWF_OutputMessage;

	/// The following flags are used by XWays to determine how the log should be outputted in the application.
	constexpr auto XWF_OutputMessage_Flag_Default = 0x0;
	constexpr auto XWF_OutputMessage_Flag_NoLineBreak = 0x01;
	constexpr auto XWF_OutputMessage_Flag_NoMsgLogEntry = 0x02;
	constexpr auto XWF_OutputMessage_Flag_AnsiMessage = 0x04;
	constexpr auto XWF_OutputMessage_Flag_NoMessageWindowOutput = 0x10;

	/// XWF_GetUserInput
	using fptr_XWF_GetUserInput = INT64(__stdcall*) (LPWSTR lpMessage, LPWSTR lpBuffer, DWORD nBufferLen, DWORD nFlags);
	fptr_XWF_GetUserInput XWF_GetUserInput;

	/// The below defines are to be used with the following function:
	/// INT64 XWF_GetUserInput(LPWSTR lpMessage, LPWSTR lpBuffer, DWORD nBufferLen, DWORD nFlags);
	/// Flag (for nFlags)                        Value           Description
	constexpr auto XWF_GetUserInput_PositiveInteger = 0x00000001;   // Requires the user to enter a positive integer number.That integer number is returned by this function.lpBuffer and nBufferLen must be NULL / zero.
	constexpr auto XWF_GetUserInput_AllowEmpty = 0x00000002;   // Empty user input allowed.Mutually exclusive with the previous flag.
	constexpr auto XWF_GetUserInput_RedactFromLog = 0x00000010;   // Gives X - Ways Forensics a hint that the X - Tension is requesting a password, so that for example no screenshot of the dialog window is taken for the log.Not yet implemented.

	/// XWF_ShowProgress
	using fptr_XWF_ShowProgress = void(__stdcall*) (wchar_t* lpCaption, DWORD nFlags);
	fptr_XWF_ShowProgress XWF_ShowProgress;

	/// The below defines are to be used with the following function:
	/// INT64 XWF_ShowProgress(wchar_t* lpCaption, DWORD nFlags);
	/// Flag (for nFlags)                        Value           Description
	constexpr auto XWF_XWF_ShowProgress_Flag_WindowOnly = 0x00000001; //show just the window, no actual progress bar
	constexpr auto XWF_XWF_ShowProgress_Flag_NoInterrupt = 0x00000002; // do not allow the user to interrupt the operation
	constexpr auto XWF_XWF_ShowProgress_Flag_ShowImmediately = 0x00000004; // show window immediately
	constexpr auto XWF_XWF_ShowProgress_Flag_DoubleConfirmAbort = 0x00000008; // double-confirm abort
	constexpr auto XWF_XWF_ShowProgress_Flag_PreventLogging = 0x00000010;  // prevent logging

	/// XWF_SetProgressPercentage
	using fptr_XWF_SetProgressPercentage = void(__stdcall*) (DWORD nPercent);
	fptr_XWF_SetProgressPercentage XWF_SetProgressPercentage;

	/// XWF_SetProgressDescription
	using fptr_XWF_SetProgressDescription = void(__stdcall*) (wchar_t* lpStr);
	fptr_XWF_SetProgressDescription XWF_SetProgressDescription;

	/// XWF_ShouldStop
	using fptr_XWF_ShouldStop = BOOL(__stdcall*) (void);
	fptr_XWF_ShouldStop XWF_ShouldStop;

	/// XWF_HideProgress
	using fptr_XWF_HideProgress = void(__stdcall*) (void);
	fptr_XWF_HideProgress XWF_HideProgress;

	/// XWF_ReleaseMem
	using fptr_XWF_ReleaseMem = BOOL(__stdcall*) (PVOID lpBuffer);
	fptr_XWF_ReleaseMem XWF_ReleaseMem;

	/// <summary>
	/// <para>
	///     Collection of Hash Types supported in X-Ways.
	/// </para>
	/// 
	/// <para>
	///     Use <c>JCS::XWUtils::HashTypeToWString(HashType hashType)</c> to convert this enum to a user friendly string.
	/// </para>
	/// </summary>
	enum struct XW_HashType
	{
		undefined = 0,
		CS8 = 1,
		CS16 = 2,
		CS32 = 3,
		CS64 = 4,
		CRC16 = 5,
		CRC32 = 6,
		MD5 = 7,
		SHA1 = 8,
		SHA256 = 9,
		RIPEMD128 = 10,
		RIPEMD160 = 11,
		MD4 = 12,
		ED2K = 13,
		Adler32 = 14,
		TigerTreeHash = 15,
		Tiger128 = 16,
		Tiger160 = 17,
		Tiger192 = 18,
		MD5folded = 19 // Subject to change.
	};

	/// <summary>
	/// <para>
	///     Collection of File System Types supported in X-Ways.
	/// </para>
	/// 
	/// <para>
	///     Use <c>JCS::XWUtils::FileSystemTypeToWString(XWFileSystemType fileSystemType)</c> to convert this enum to a user friendly string.
	/// </para>
	/// </summary>
	enum struct XW_FileSystemType
	{
		UnknownFS = 0,
		FAT12 = 1,
		FAT16 = 2,
		FAT32 = 3,
		exFAT = 4,
		UDF = 5,
		XWFS = 6,
		OSDirectoryListing = 7,
		CDFS = 8,
		MainMemory = 9,
		ReFS = 10,
		BitLocker = 11,
		APFS = 12,
		NTFS = -1,
		Ext2 = -3,
		Ext3 = -4,
		ReiserFS = -5,
		Reiser4 = -6,
		Ext4 = -7,
		JFS = -9,
		XFS = -10,
		UFS = -11,
		HFS = -12,
		HFSPlus = -13,
		NTFSBitLocker = -15,
		PhysicalDiskPotentiallyPartitioned = -16,
		Btrfs = -17,
		QNX = -18,
		LDMMetadata = -24,
		LDMData = -25,
		LinuxSwap = -29,
		LVM2Container = -30,
		MDRAIDHeader = -31,
		StoragePoolContainer = -32,
		WindowsPhoneContainer = -33,
		VMFS = -34,
		ZFS = -35
	};

	/// <summary>
	/// Deletion status of an item.
	/// To be used with XWF::VolumeSnapshotItem::XWF_GetItemInformation()
	/// </summary>
	enum struct XWF_Item_Info_Deletion_Status
	{
		Existing = 0,
		PreviouslyExistingPossiblyRecoverable = XWF::VolumeSnapshotItem::XWF_Item_Info_Deletion_PreviouslyExistingPossiblyRecoverable,
		PreviouslyExistingFirstClusterOverwritten = XWF::VolumeSnapshotItem::XWF_Item_Info_Deletion_PreviouslyExistingFirstClusterOverwritten,
		RenamedOrMovedPossiblyRecoverable = XWF::VolumeSnapshotItem::XWF_Item_Info_Deletion_RenamedOrMovedPossiblyRecoverable,
		RenamedOrMovedFirstClusterOverwritten = XWF::VolumeSnapshotItem::XWF_Item_Info_Deletion_RenamedOrMovedFirstClusterOverwritten,
		CarvedFile = XWF::VolumeSnapshotItem::XWF_Item_Info_Deletion_CarvedFile
	};
}
#pragma endregion Miscellaneous

#pragma region Other
export namespace XWF::Other
{
	/// <summary>
	/// Metadata on a function exported by X-Ways Forensics.
	/// </summary>
	class XWFFunctionMetaData
	{
	public:
		/// <summary>
		/// True if the function has been exported and available for use.
		/// </summary>
		bool found = false;
		/// <summary>
		/// Name of the function which may be called.
		/// </summary>
		std::wstring functionName = L"";
	private:
	};

	/// <summary>
	/// Given a module handle and function name, returns a function pointer which may be called.
	/// </summary>
	/// <param name="functionMetaDataList">Current list of exported functions. Used to add more functions to it.</param>
	/// <param name="Hdl"></param>
	/// <param name="functionName"></param>
	/// <returns></returns>
	void* GetXWFFunction(std::vector<XWF::Other::XWFFunctionMetaData>& functionMetaDataList, HMODULE Hdl, const char* functionName)
	{
		XWF::Other::XWFFunctionMetaData functionMetaData{};
		auto a = std::string(functionName);
		auto b = std::wstring().assign(a.begin(), a.end());
		functionMetaData.functionName = b;

		void* result = GetProcAddress(Hdl, functionName);

		if (result == nullptr)
		{
			functionMetaData.found = false;
		}
		else
		{
			functionMetaData.found = true;
		}
		functionMetaDataList.push_back(functionMetaData);

		return result;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// XT_RetrieveFunctionPointers - call this function before calling anything else
	/// <summary>
	/// Gets all the available functions.
	/// </summary>
	/// <returns>Meta data of the missing functions.</returns>
	std::vector<XWFFunctionMetaData> __stdcall XT_RetrieveFunctionPointers()
	{
		std::vector<XWF::Other::XWFFunctionMetaData> functionMetaDataList{};

		HMODULE Hdl = GetModuleHandle(NULL);

		/// IO
		XWF::IO::XWF_GetVolumeName = (XWF::IO::fptr_XWF_GetVolumeName)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetVolumeName");
		XWF::IO::XWF_GetVolumeInformation = (XWF::IO::fptr_XWF_GetVolumeInformation)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetVolumeInformation");
		XWF::IO::XWF_GetProp = (XWF::IO::fptr_XWF_GetProp)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetProp");
		XWF::IO::XWF_GetSize = (XWF::IO::fptr_XWF_GetSize)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetSize");
		XWF::IO::XWF_GetSectorContents = (XWF::IO::fptr_XWF_GetSectorContents)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetSectorContents");
		XWF::IO::XWF_OpenItem = (XWF::IO::fptr_XWF_OpenItem)GetXWFFunction(functionMetaDataList, Hdl, "XWF_OpenItem");
		XWF::IO::XWF_Close = (XWF::IO::fptr_XWF_Close)GetXWFFunction(functionMetaDataList, Hdl, "XWF_Close");
		XWF::IO::XWF_Read = (XWF::IO::fptr_XWF_Read)GetXWFFunction(functionMetaDataList, Hdl, "XWF_Read");
		XWF::IO::XWF_Write = (XWF::IO::fptr_XWF_Write)GetXWFFunction(functionMetaDataList, Hdl, "XWF_Write");
		XWF::IO::XWF_GetDriveInfo = (XWF::IO::fptr_XWF_GetDriveInfo)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetDriveInfo");
		XWF::IO::XWF_SectorIO = (XWF::IO::fptr_XWF_SectorIO)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SectorIO");
		XWF::IO::XWF_GetBlock = (XWF::IO::fptr_XWF_GetBlock)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetBlock");
		XWF::IO::XWF_SetBlock = (XWF::IO::fptr_XWF_SetBlock)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetBlock");
		/// EvidenceAndCase
		XWF::EvidenceAndCase::XWF_GetCaseProp = (XWF::EvidenceAndCase::fptr_XWF_GetCaseProp)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetCaseProp");
		XWF::EvidenceAndCase::XWF_GetFirstEvObj = (XWF::EvidenceAndCase::fptr_XWF_GetFirstEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetFirstEvObj");
		XWF::EvidenceAndCase::XWF_GetNextEvObj = (XWF::EvidenceAndCase::fptr_XWF_GetNextEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetNextEvObj");
		XWF::EvidenceAndCase::XWF_DeleteEvObj = (XWF::EvidenceAndCase::fptr_XWF_DeleteEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_DeleteEvObj");
		XWF::EvidenceAndCase::XWF_CreateEvObj = (XWF::EvidenceAndCase::fptr_XWF_CreateEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CreateEvObj");
		XWF::EvidenceAndCase::XWF_OpenEvObj = (XWF::EvidenceAndCase::fptr_XWF_OpenEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_OpenEvObj");
		XWF::EvidenceAndCase::XWF_CloseEvObj = (XWF::EvidenceAndCase::fptr_XWF_CloseEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CloseEvObj");
		XWF::EvidenceAndCase::XWF_GetEvObjProp = (XWF::EvidenceAndCase::fptr_XWF_GetEvObjProp)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetEvObjProp");
		XWF::EvidenceAndCase::XWF_GetEvObj = (XWF::EvidenceAndCase::fptr_XWF_GetEvObj)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetEvObj");
		XWF::EvidenceAndCase::XWF_GetReportTableInfo = (XWF::EvidenceAndCase::fptr_XWF_GetReportTableInfo)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetReportTableInfo");
		XWF::EvidenceAndCase::XWF_GetEvObjReportTableAssocs = (XWF::EvidenceAndCase::fptr_XWF_GetEvObjReportTableAssocs)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetEvObjReportTableAssocs");
		/// VolumeSnapshot
		XWF::VolumeSnapshot::XWF_SelectVolumeSnapshot = (XWF::VolumeSnapshot::fptr_XWF_SelectVolumeSnapshot)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SelectVolumeSnapshot");
		XWF::VolumeSnapshot::XWF_GetVSProp = (XWF::VolumeSnapshot::fptr_XWF_GetVSProp)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetVSProp");
		XWF::VolumeSnapshot::XWF_GetItemCount = (XWF::VolumeSnapshot::fptr_XWF_GetItemCount)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemCount");
		XWF::VolumeSnapshot::XWF_GetFileCount = (XWF::VolumeSnapshot::fptr_XWF_GetFileCount)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetFileCount");
		XWF::VolumeSnapshot::XWF_GetSpecialItemID = (XWF::VolumeSnapshot::fptr_XWF_GetSpecialItemID)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetSpecialItemID");
		XWF::VolumeSnapshot::XWF_CreateItem = (XWF::VolumeSnapshot::fptr_XWF_CreateItem)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CreateItem");
		XWF::VolumeSnapshot::XWF_CreateFile = (XWF::VolumeSnapshot::fptr_XWF_CreateFile)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CreateFile");
		XWF::VolumeSnapshot::XWF_FindItem1 = (XWF::VolumeSnapshot::fptr_XWF_FindItem1)GetXWFFunction(functionMetaDataList, Hdl, "XWF_FindItem1");
		XWF::VolumeSnapshot::XWF_Mount = (XWF::VolumeSnapshot::fptr_XWF_Mount)GetXWFFunction(functionMetaDataList, Hdl, "XWF_Mount");
		XWF::VolumeSnapshot::XWF_Unmount = (XWF::VolumeSnapshot::fptr_XWF_Unmount)GetXWFFunction(functionMetaDataList, Hdl, "XWF_Unmount");
		/// VolumeSnapshotItem
		XWF::VolumeSnapshotItem::XWF_GetItemName = (XWF::VolumeSnapshotItem::fptr_XWF_GetItemName)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemName");
		XWF::VolumeSnapshotItem::XWF_SetItemName = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemName)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemName");
		XWF::VolumeSnapshotItem::XWF_GetItemSize = (XWF::VolumeSnapshotItem::fptr_XWF_GetItemSize)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemSize");
		XWF::VolumeSnapshotItem::XWF_SetItemSize = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemSize)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemSize");
		XWF::VolumeSnapshotItem::XWF_GetItemOfs = (XWF::VolumeSnapshotItem::fptr_XWF_GetItemOfs)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemOfs");
		XWF::VolumeSnapshotItem::XWF_SetItemOfs = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemOfs)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemOfs");
		XWF::VolumeSnapshotItem::XWF_GetItemInformation = (XWF::VolumeSnapshotItem::fptr_XWF_GetItemInformation)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemInformation");
		XWF::VolumeSnapshotItem::XWF_SetItemInformation = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemInformation)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemInformation");
		XWF::VolumeSnapshotItem::XWF_GetItemType = (XWF::VolumeSnapshotItem::fptr_XWF_GetItemType)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemType");
		XWF::VolumeSnapshotItem::XWF_SetItemType = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemType)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemType");
		XWF::VolumeSnapshotItem::XWF_GetItemParent = (XWF::VolumeSnapshotItem::fptr_XWF_GetItemParent)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetItemParent");
		XWF::VolumeSnapshotItem::XWF_SetItemParent = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemParent)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemParent");
		XWF::VolumeSnapshotItem::XWF_GetHashSetAssocs = (XWF::VolumeSnapshotItem::fptr_XWF_GetHashSetAssocs)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetHashSetAssocs");
		XWF::VolumeSnapshotItem::XWF_GetReportTableAssocs = (XWF::VolumeSnapshotItem::fptr_XWF_GetReportTableAssocs)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetReportTableAssocs");
		XWF::VolumeSnapshotItem::XWF_AddToReportTable = (XWF::VolumeSnapshotItem::fptr_XWF_AddToReportTable)GetXWFFunction(functionMetaDataList, Hdl, "XWF_AddToReportTable");
		XWF::VolumeSnapshotItem::XWF_GetComment = (XWF::VolumeSnapshotItem::fptr_XWF_GetComment)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetComment");
		XWF::VolumeSnapshotItem::XWF_AddComment = (XWF::VolumeSnapshotItem::fptr_XWF_AddComment)GetXWFFunction(functionMetaDataList, Hdl, "XWF_AddComment");
		XWF::VolumeSnapshotItem::XWF_GetExtractedMetadata = (XWF::VolumeSnapshotItem::fptr_XWF_GetExtractedMetadata)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetExtractedMetadata");
		XWF::VolumeSnapshotItem::XWF_AddExtractedMetadata = (XWF::VolumeSnapshotItem::fptr_XWF_AddExtractedMetadata)GetXWFFunction(functionMetaDataList, Hdl, "XWF_AddExtractedMetadata");
		XWF::VolumeSnapshotItem::XWF_GetHashValue = (XWF::VolumeSnapshotItem::fptr_XWF_GetHashValue)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetHashValue");
		XWF::VolumeSnapshotItem::XWF_SetHashValue = (XWF::VolumeSnapshotItem::fptr_XWF_SetHashValue)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetHashValue");
		XWF::VolumeSnapshotItem::XWF_GetCellText = (XWF::VolumeSnapshotItem::fptr_XWF_GetCellText)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetCellText");
		XWF::VolumeSnapshotItem::XWF_SetItemDataRuns = (XWF::VolumeSnapshotItem::fptr_XWF_SetItemDataRuns)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetItemDataRuns");
		/// FileContent
		XWF::FileContent::XWF_GetMetadata = (XWF::FileContent::fptr_XWF_GetMetadata)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetMetadata");
		XWF::FileContent::XWF_GetMetadataEx = (XWF::FileContent::fptr_XWF_GetMetadataEx)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetMetadataEx");
		XWF::FileContent::XWF_PrepareTextAccess = (XWF::FileContent::fptr_XWF_PrepareTextAccess)GetXWFFunction(functionMetaDataList, Hdl, "XWF_PrepareTextAccess");
		XWF::FileContent::XWF_GetText = (XWF::FileContent::fptr_XWF_GetText)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetText");
		XWF::FileContent::XWF_GetRasterImage = (XWF::FileContent::fptr_XWF_GetRasterImage)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetRasterImage");
		/// Search
		XWF::Search::XWF_Search = (XWF::Search::fptr_XWF_Search)GetXWFFunction(functionMetaDataList, Hdl, "XWF_Search");
		XWF::Search::XWF_GetSearchTerm = (XWF::Search::fptr_XWF_GetSearchTerm)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetSearchTerm");
		XWF::Search::XWF_AddSearchTerm = (XWF::Search::fptr_XWF_AddSearchTerm)GetXWFFunction(functionMetaDataList, Hdl, "XWF_AddSearchTerm");
		XWF::Search::XWF_ManageSearchTerm = (XWF::Search::fptr_XWF_ManageSearchTerm)GetXWFFunction(functionMetaDataList, Hdl, "XWF_ManageSearchTerm");
		XWF::Search::XWF_AddSearchHit = (XWF::Search::fptr_XWF_AddSearchHit)GetXWFFunction(functionMetaDataList, Hdl, "XWF_AddSearchHit");
		XWF::Search::XWF_GetSearchHit = (XWF::Search::fptr_XWF_GetSearchHit)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetSearchHit");
		XWF::Search::XWF_SetSearchHit = (XWF::Search::fptr_XWF_SetSearchHit)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetSearchHit");
		/// Event
		XWF::Event::XWF_AddEvent = (XWF::Event::fptr_XWF_AddEvent)GetXWFFunction(functionMetaDataList, Hdl, "XWF_AddEvent");
		XWF::Event::XWF_GetEvent = (XWF::Event::fptr_XWF_GetEvent)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetEvent");
		/// EvidenceContainer
		XWF::EvidenceContainer::XWF_CreateContainer = (XWF::EvidenceContainer::fptr_XWF_CreateContainer)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CreateContainer");
		XWF::EvidenceContainer::XWF_CopyToContainer = (XWF::EvidenceContainer::fptr_XWF_CopyToContainer)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CopyToContainer");
		XWF::EvidenceContainer::XWF_CloseContainer = (XWF::EvidenceContainer::fptr_XWF_CloseContainer)GetXWFFunction(functionMetaDataList, Hdl, "XWF_CloseContainer");
		/// DataWindow
		XWF::DataWindow::XWF_GetWindow = (XWF::DataWindow::fptr_XWF_GetWindow)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetWindow");
		XWF::DataWindow::XWF_GetColumnTitle = (XWF::DataWindow::fptr_XWF_GetColumnTitle)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetColumnTitle");
		/// Miscellaneous
		XWF::Miscellaneous::XWF_OutputMessage = (XWF::Miscellaneous::fptr_XWF_OutputMessage)GetXWFFunction(functionMetaDataList, Hdl, "XWF_OutputMessage");
		XWF::Miscellaneous::XWF_GetUserInput = (XWF::Miscellaneous::fptr_XWF_GetUserInput)GetXWFFunction(functionMetaDataList, Hdl, "XWF_GetUserInput");
		XWF::Miscellaneous::XWF_ShowProgress = (XWF::Miscellaneous::fptr_XWF_ShowProgress)GetXWFFunction(functionMetaDataList, Hdl, "XWF_ShowProgress");
		XWF::Miscellaneous::XWF_SetProgressPercentage = (XWF::Miscellaneous::fptr_XWF_SetProgressPercentage)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetProgressPercentage");
		XWF::Miscellaneous::XWF_SetProgressDescription = (XWF::Miscellaneous::fptr_XWF_SetProgressDescription)GetXWFFunction(functionMetaDataList, Hdl, "XWF_SetProgressDescription");
		XWF::Miscellaneous::XWF_ShouldStop = (XWF::Miscellaneous::fptr_XWF_ShouldStop)GetXWFFunction(functionMetaDataList, Hdl, "XWF_ShouldStop");
		XWF::Miscellaneous::XWF_HideProgress = (XWF::Miscellaneous::fptr_XWF_HideProgress)GetXWFFunction(functionMetaDataList, Hdl, "XWF_HideProgress");
		XWF::Miscellaneous::XWF_ReleaseMem = (XWF::Miscellaneous::fptr_XWF_ReleaseMem)GetXWFFunction(functionMetaDataList, Hdl, "XWF_ReleaseMem");

		return functionMetaDataList;
	}

#pragma pack(push, 2)
	/// <summary>
	/// This is an unknow structure. It is no longer on the API website.
	/// It originates from the sample C++ template.
	/// pSourceInfo:
	/// 
	/// More information about the source of the file's data. Exact meaning depends on the flags.
	/// </summary>
	struct SrcInfo
	{
		DWORD nStructSize;
		INT64 nBufSize;
		LPVOID pBuffer;
	};
#pragma pack(pop)
}
#pragma endregion Other

#pragma endregion XWF_*

#pragma region XT_*
///////////////////////////////////////////////////////////////////////////////
// Functions that X-Ways Forensics or WinHex may call
// 
// Note:    Some of the function definitions are commented out as they are defined in the main .cpp file.
//          The functions are kept here for future reference if they are changed or need adding.
// 
// See:
// https://www.x-ways.net/forensics/x-tensions/XT_functions.html

#pragma region Core
/// <summary>
/// These are core functions every X-Tensions must implement. X-Ways will call this on initialisation and completion.
/// </summary>
export namespace XWF::Core
{
	constexpr auto XT_Init_Return_Abort = -1;
	constexpr auto XT_Init_Return_SingleThread = 1;
	constexpr auto XT_Init_Return_ThreadSafe = 2;

#pragma pack(push, 2)
	/// <summary>
	/// <para>
	///     Points to a structure that contains information about the license.
	///     Provided by v18.1 and later.
	///     NULL in older releases.
	/// </para>
	/// 
	/// <para>
	///     nSize:
	/// </para>
	///     <para>
	///         Size of the structure provided.
	///     </para>
	/// <para>
	///     nLicFlags:
	/// </para>
	///     <para>
	///         See XWF_LICENSEINFO_NLICFLAGS_*
	///     </para>
	/// <para>
	///     nUsers:
	/// </para>
	///     <para>
	///         Specifies how many different users may use the same license file/dongle simultaneously.
	///         For BYOD this is currently always 1.
	///         0 means unknown.
	///     </para>
	/// <para>
	///     nExpDate:
	/// </para>
	///     <para>
	///         Indicates the date when either access to updates will end or has
	///         ended (for a perpetual license) or when the ability to use the software
	///         will end (for a non - perpetual license).
	///     </para>
	/// <para>
	///     nLicID:
	/// </para>
	///     <para>
	///         A hash value that uniquely identifies the license file/dongle/BYOD license.
	///         You could license your X - Tension based on that ID and only allow users to run
	///         your X - Tension if the ID matches your expectations (if the ID is in your unlock
	///         list). Since v20.5, users can find this ID if they first click the version number
	///         in the upper right corner and then the button labeled "nLicID", in hex ASCII notation.
	///         This could be useful if the purchase of a license for your X - Tension requires that ID.
	///         Please note that the actual dongle ID or BYOD license ID cannot be derived from nLicID.
	///     </para>
	/// </summary>
	struct LicenseInfo
	{
		DWORD nSize;
		DWORD nLicFlags;
		DWORD nUsers;
		FILETIME nExpDate;
		BYTE nLicID[16];
	};
#pragma pack(pop)

	/// Flag                                             Value       Description
	constexpr auto LicenseInfo_LicFlag_Unlocked = 0x01;     // Running unlocked / licensed
	constexpr auto LicenseInfo_LicFlag_ExpirationDate = 0x02;     // Expiration date field nExpDate is populated(this flag set in releases from 2024 - 02 - 22)
	constexpr auto LicenseInfo_LicFlag_NonPerpetual = 0x04;     // Non - perpetual license, i.e. not only access to updates, but the license(the right to use the software) itself will expire eventually
	constexpr auto LicenseInfo_LicFlag_Hardware = 0x10;     // The software uses a hardware - based copy protection method(dongle or BYOD)
	constexpr auto LicenseInfo_LicFlag_Dongle = 0x20;     // The hardware device is a dongle(if 0x10 is set and 0x20 is not, then it's BYOD)
	constexpr auto LicenseInfo_LicFlag_Network = 0x40;     // The dongle is a network dongle that is accessed remotely
	constexpr auto LicenseInfo_LicFlag_BYOD = 0x80;     // The BYOD device is a remote web server(i.e.BYOD + ), flag supported by v19.3 SR - 7 and later

	/// <summary>
	/// No longer used - inherited from the original XT-C++ download template.
	/// This is no replaced by the nVersion parameter.
	/// </summary>
	struct CallerInfo
	{
		byte lang, ServiceRelease;
		WORD version;
	};

	/// XT_Init - mandatory export
	//LONG __stdcall XT_Init(DWORD nVersion, DWORD nFlags, HANDLE hMainWnd, struct LicenseInfo* pLicInfo);

	/// INIT FLAGS
	/// Flag                     Value         Description
	constexpr auto XT_Init_XWaysForensics = 0x00000001; // X-Ways Forensics // X-Ways Forensics (flag used reliably in releases from 2015).
	constexpr auto XT_Init_WinHex = 0x00000002; // WinHex // WinHex (flag used reliably in releases from 2015, either WinHex Lab Edition or X-Ways Forensics run as WinHex).
	constexpr auto XT_Init_XWaysInvestigator = 0x00000004; // X-Ways Investigator // other application besides X-Ways Forensics and WinHex (just theoretical).
	constexpr auto XT_Init_Beta = 0x00000008; // Beta version // pre-release version.
	constexpr auto XT_Init_QuickCheck = 0x00000020; // Called just to check whether the API accepts the calling application (used by v16.5 and later) // called just to check whether the X-Tension accepts the calling application (used by v16.5 and later).
	constexpr auto XT_Init_AboutOnly = 0x00000040; // Called just to prepare for XT_About (used by v16.5 and later) // called just to prepare for XT_About() or XT_PrepareSearch() (used by v16.5 and later).

	/// XT_Done
	//LONG __stdcall XT_Done(PVOID lpReserved);
	constexpr auto XT_Done_NoAction = 0; // Should always return this.
}
#pragma endregion Core

#pragma region Ordinary
/// <summary>
/// Functions which are called by an 'ordinary' extension.
/// </summary>
export namespace XWF::Ordinary
{
	// The following functions are optional for export.
	// In order to implement the functions, implement them and activate them in the module definition file.

	/// XT_About
	// LONG __stdcall XT_About(HANDLE hParentWnd, PVOID lpReserved);
	constexpr auto XT_About_NoAction = 0; // Default value that should be returned.

	/// XT_Prepare
	// LONG __stdcall XT_Prepare(HANDLE hVolume, HANDLE hEvidence, DWORD nOpType, PVOID lpReserved);

	/// PREPARE FLAGS to return.
	// Flag                                 Value       Description
	constexpr auto XT_Prepare_NoAction = 0x00; // If you just want XT_Finalize() to be called. Will also be assumed if you do not export XT_Prepare().
	constexpr auto XT_Prepare_CallProcessItem = 0x01; // If you want X-Ways Forensics to call your implementation of XT_ProcessItem[Ex]() (whichever is exported) for each item this volume snapshot (not if the volume snapshot is not targeted, e.g. in case of XT_ACTION_RUN).
	constexpr auto XT_Prepare_CallProcessItemLate = 0x02; // For XT_ACTION_RVS specify this flag in addition to XT_PREPARE_CALLPI if you wish to receive calls of XT_ProcessItem() (not Ex), if actually exported, after all other individual item refinement operations instead of before (preferable for example so that you do not get called for ignorable files that were recognized as such by hash database matching during the same volume snapshot refinement run).
	constexpr auto XT_Prepare_ExpectMoreItems = 0x04; // In case of XT_ACTION_RVS, to signal XWF that you may create more items in the volume snapshot, so that for example the user will definitely be informed of how many item were added (v16.5 and later only).
	constexpr auto XT_Prepare_DontOmit = 0x08; // In case of XT_ACTION_RVS, to signal XWF that you wish to receive calls for XT_ProcessItem[Ex]() even for files that the user wants to omit for any of the possible three reasons (v18.5 and later only).
	constexpr auto XT_Prepare_TargetedDirectories = 0x10; // In case of XT_ACTION_RVS, to signal XWF that you wish to receive calls for XT_ProcessItem[Ex]() even for directories, not only files, for example because you wish to parse the file system data structures in those directories (v18.5 and later only).
	constexpr auto XT_Prepare_TargetZeroByteFiles = 0x20; // In case of XT_ACTION_RVS, to signal XWF that you wish to receive calls for XT_ProcessItem[Ex]() even for files that have a size of 0 bytes, which are otherwise skipped for performance reasons (v18.9 SR-7 and later only).

	/// PREPARE OPTYPE OPTIONS
	// Flag                 Value   Description
	constexpr auto XT_Action_MainMenu = 0;    // Simply run directly from the main menu, not for any particular volume, since v16.6.
	constexpr auto XT_Action_RefineVolumeSnapshot = 1;    // Volume snapshot refinement starting.
	constexpr auto XT_Action_LogicalSearchStarting = 2;    // Logical simultaneous search starting.
	constexpr auto XT_Action_PhysicalSearchStarting = 3;    // Physical simultaneous search starting.
	constexpr auto XT_Action_DirectoryBrowserContextMenu = 4;    // Directory browser context menu command invoked.
	constexpr auto XT_Action_SearchHitContextMenu = 5;    // Search hit context menu command invoked.
	constexpr auto XT_Action_EventListContextMenu = 6;    // Event list context menu command invoked (since v20.3 SR-3).
	constexpr auto XT_Action_PrepareSimultaneousSearch = 7;    // Preparing a Simultaneous Search - JCS CUSTOM VALUE - MAY BE OVERRIDDEN BY FUTURE XWAYS VERSIONS.

	/// XT_Finalize
	// LONG __stdcall XT_Finalize(HANDLE hVolume, HANDLE hEvidence, DWORD nOpType, PVOID lpReserved);
	constexpr auto XT_Finalize_NoAction = 0; // No further action to take.
	constexpr auto XT_Finalize_RefreshDirectoryBrowser = 1; // If the current directory listing in the directory browser of the active data window has to be refreshed


	/// XT_ProcessItem
	// LONG __stdcall XT_ProcessItem(LONG nItemID, PVOID lpReserved);
	constexpr auto XT_ProcessItem_ContinueOperation = 0; // Operation successful/no further actions to take in the XTension; but continue RVS (for example) to process this item.
	constexpr auto XT_ProcessItem_StopOperation = -1; // If you want X - Ways Forensics to stop the current operation (e.g.volume snapshot refinement)
	constexpr auto XT_ProcessItem_SkipOperation = -2; // If you want X-Ways Forensics to skip its own volume snapshot refinement operations for this file(e.g.to save time if you have determined a file to be of no interest).

	/// XT_ProcessItemEx
	// LONG __stdcall XT_ProcessItemEx(LONG nItemID, HANDLE hItem, PVOID lpReserved);

#pragma pack(push, 2)
	/// <summary>
	/// <para>
	///     lpSearchTerms:
	/// </para>
	///     <para>
	///         Null - terminated. Delimited by line breaks. Points to a buffer that specifies the currently entered search terms,
	///         which you can manipulate, replace or complete within the limits of the buffer.
	///     </para>
	/// <para>
	/// nBufLen:
	/// </para>
	///     <para>
	///         Size of the buffer that lpSearchTerms points to in Unicode characters. Currently always 32768,
	///         but subject to change in future versions.
	///     </para>
	/// <para>
	/// nFlags:
	/// </para>
	///     <para>
	///         See XWF_SEARCH_*
	///     </para>
	/// </summary>
	struct PrepareSearchInfo
	{
		DWORD nSize;
		LPWSTR lpSearchTerms;
		DWORD nBufLen;
		DWORD nFlags;
	};
#pragma pack(pop)

	/// XT_PrepareSearch
	// LONG XT_PrepareSearch(struct PrepareSearchInfo* PSInfo, struct CodePages* CPages);
	constexpr auto XT_PrepareSearch_NoAdjustmentMade = 0; // Current settings are ok and applied.
	constexpr auto XT_PrepareSearch_AdjustmentMade = 1; // If you have made adjustments to the search terms and are to be applied.
	constexpr auto XT_PrepareSearch_Abort = -1; // If you are not happy with the current settings at all and want the X-Tension to be unselected.

	/// XT_ProcessSearchHit
	// LONG __stdcall XT_ProcessSearchHit(struct SearchHitInfo* info);
	constexpr auto XT_ProcessSearchHit_NoFurtherAction = 0; //  To do no further action.
	constexpr auto XT_ProcessSearchHit_AbortSearch = -1; // If you want X-Ways Forensics to abort the search.
	constexpr auto XT_ProcessSearchHit_StopCalling = -2; // If you want X-Ways Forensics to stop calling you.
}
#pragma endregion Ordinary

#pragma region Viewer
/// <summary>
/// Functions called by X-Ways for viewer X-Tensions.
/// See: https://www.x-ways.net/forensics/x-tensions/XT_functions.html#viewer
/// </summary>
export namespace XWF::Viewer
{
	/// XT_View
	/// For viewer X-Tensions
	// PVOID XT_View(HANDLE hItem, LONG nItemID, HANDLE hVolume, HANDLE hEvidence, PVOID lpReserved, PINT64 nResSize);

	/// XT_ReleaseMem
	/// Free up memory allocated by a previous call e.g. of XT_View
	// BOOL XT_ReleaseMem(PVOID lpBuffer);
}
#pragma endregion Viewer

#pragma region DataSource
/// <summary>
/// Currently no callable functions.
/// See: https://www.x-ways.net/forensics/x-tensions/XT_functions.html#datasource
/// </summary>
export namespace XWF::DataSource
{
}
#pragma endregion DataSource

#pragma region DiskIO
/// <summary>
/// For Disk I/O X-Tensions
/// See: https://www.x-ways.net/forensics/x-tensions/XT_functions.html#diskio
/// </summary>
export namespace XWF::DiskIO
{
#pragma pack(push, 2)
	/// <summary>
	///  nSize is the size of the structure. The structure might grow in future versions of X-Ways Forensics, but the elements at the beginning of the structure remain the same.
	/// 
	/// nDrive may be a negative number(in case of a physical, partitioned disk or image or hardware RAID) or a positive number(in case of a partition or volume on a disk or in an image or RAID).This parameter identifies the data source and must be used for any calls to XWF_DriveIO.
	/// 
	/// lpPrivate is initially a pointer to an initialized Unicode buffer that you may fill with an error message in case your function returns 0. The buffer may hold up to 255 characters.If however you signal success, then you may change this pointer to any private value or other pointer for your own use.You will be provided with the same value / pointer again when responding to calls for XT_SectorIO() and XT_SectorIODone().The value / pointer may help you to reference your own dynamically allocated data about the encryption or to identify the disk.
	/// 
	/// nSectorCount is not only provided to you, but you may also change that value.For example if you provide access to an encrypted volume that is contained in the designated partition, but does not occupy the entire space of that partition because of a reserved header area, you reduce the sector count accordingly to prevent X - Ways Forensics from accessing sectors that do not exist in your volume.In such a case of a reserved header area of n sectors, that also means that when you respond to calls for XT_SectorIO() to read sector x, you will actually read sector x + n using XWF_SectorIO and then(probably after decrypting it) return that data.
	/// 
	/// nParentDrive, nParentSectorCount, and nStartSectorOnParent are provided in case you need metadata from outside of the partition to properly interpret the data in the partition.You may read data from the parent disk using XWF_SectorIO, specifying nParentDrive as the drive to read from.If nParentDrive is zero, there is no parent.
	/// </summary>
	struct DriveInfo
	{
		DWORD nSize;
		LONG nDrive;
		LONG nParentDrive;
		DWORD nBytesPerSector;
		INT64 nSectorCount;
		INT64 nParentSectorCount;
		INT64 nStartSectorOnParent;
		LPVOID lpPrivate;
	};
#pragma pack(pop)

	/// XT_SectorIOInit
	// DWORD XT_SectorIOInit(struct XWF::DiskIO::DriveInfo* pDInfo);

	/// XT_SectorIO
	// DWORD XT_SectorIO(LPVOID lpPrivate, LONG nDrive, INT64 nSector, DWORD nCount, LPVOID lpBuffer, DWORD nFlags);

	/// XT_FileIO
	// INT64 XT_FileIO(LPVOID lpPrivate, LONG nDrive, HANDLE hVolume, HANDLE hItem, LONG nItemID, INT64 nOffset, LPVOID lpBuffer, INT64 nNumberOfBytes, DWORD nFlags);

	/// XT_SectorIODone
	// DWORD XT_SectorIODone(LPVOID lpPrivate, LPVOID lpReserved);
}
#pragma endregion DiskIO

#pragma endregion XT_*