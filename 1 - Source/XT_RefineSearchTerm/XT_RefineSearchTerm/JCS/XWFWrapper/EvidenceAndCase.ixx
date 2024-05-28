module;

#include <Windows.h>

export module EvidenceAndCase;

import Utils;
import XTension;
import Logging;
import std;

/// <summary>
/// Evidence Object / Case Management Functions
/// </summary>
export namespace JCS::XWFWrapper::EvidenceAndCase
{
    /// <summary>
    /// Available in v17.2 and later. Depending on nPropType, either returns information about the current case as a 64-bit integer OR retrieves such information in a buffer that you supply. The buffer size for strings is to be specified in characters (UTF-16). pReserved must be NULL. Unless otherwise noted, returns the original length of the requested string in characters, or the number of bytes for other buffer types, or a negative number if an error occurred, for example if no case is active.
    /// 
    /// Much of the functionality of X - Ways Forensics and WinHex Lab Edition is available when not working with a case (when no case was created / opened in the program), after just having opened a disk or image or even an ordinary single file, including the ability to run X - Tensions.If the X - Tension specifically works with the evidence objects of a case, not just the snapshot of the volume represented by the active data window or the single file represented by the active data window, yet the user tries to run the X - Tension with no case / no evidence objects open, then the X - Tension should simply tell the user that it only works with a case and cannot do anything without(and it should not try do provide NULL pointers / handles where pointers / handles to evidence objects are expected).X - Ways Forensics itself also refuses to let the user do certain things when no case is active.
    /// </summary>
    /// <param name="pReserved"></param>
    /// <param name="nPropType"></param>
    /// <param name="pBuffer"></param>
    /// <param name="nBufLen"></param>
    /// <returns></returns>
    INT64 XWF_GetCaseProp(LPVOID pReserved, LONG nPropType, PVOID pBuffer, LONG nBufLen)
    {
        INT64 returnedValue = XWF::EvidenceAndCase::XWF_GetCaseProp(pReserved, nPropType, pBuffer, nBufLen);

        if (returnedValue < 0)
        {
            JCS::Logging::Log("Getting case property errored. No active case?", JCS::Logging::LogLevel::Error);
        }

        return returnedValue;
    }

    std::optional<INT64> XWF_GetCaseProp_ID()
    {
        INT64 returnedValue = XWF::EvidenceAndCase::XWF_GetCaseProp(nullptr, XWF::EvidenceAndCase::XWF_GetCaseProp_PropType_ID, nullptr, NULL);

        if (returnedValue < 0)
        {
            return std::nullopt;
        }

        return returnedValue;
    }

    std::optional<std::wstring> XWF_GetCaseProp_Title()
    {
        std::unique_ptr<WCHAR[]> pTitle = std::make_unique<WCHAR[]>(MAX_PATH);
        INT64 returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp(NULL, XWF::EvidenceAndCase::XWF_GetCaseProp_PropType_Title, pTitle.get(), MAX_PATH);

        if (returnedValue < 0 || pTitle == nullptr)
        {
            return std::nullopt;
        }

        std::wstring title = JCS::Utils::LPWStrToWString(pTitle.get());
        return title;
    }

    std::optional<SYSTEMTIME> XWF_GetCaseProp_Creation()
    {
        INT64 caseCreationTime = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp(NULL, XWF::EvidenceAndCase::XWF_GetCaseProp_PropType_Creation, NULL, NULL);

        if (caseCreationTime < 0)
        {
            return std::nullopt;
        }

        SYSTEMTIME creationTime = JCS::Utils::Int64FileTimeToSystemTime(caseCreationTime);
        return creationTime;
    }

    std::optional<std::wstring> XWF_GetCaseProp_Examiner()
    {
        std::unique_ptr<WCHAR[]> pExaminer = std::make_unique<WCHAR[]>(MAX_PATH);
        INT64 returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp(NULL, XWF::EvidenceAndCase::XWF_GetCaseProp_PropType_Examiner, pExaminer.get(), MAX_PATH);

        if (returnedValue < 0 || pExaminer == nullptr)
        {
            return std::nullopt;
        }

        std::wstring examiner = JCS::Utils::LPWStrToWString(pExaminer.get());
        return examiner;
    }

    std::optional<std::wstring> XWF_GetCaseProp_CaseFilePath()
    {
        std::unique_ptr<WCHAR[]> pFile = std::make_unique<WCHAR[]>(MAX_PATH);
        INT64 returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp(NULL, XWF::EvidenceAndCase::XWF_GetCaseProp_PropType_File, pFile.get(), MAX_PATH);

        if (returnedValue < 0 || pFile == nullptr)
        {
            return std::nullopt;
        }

        std::wstring file = JCS::Utils::LPWStrToWString(pFile.get());
        return file;
    }

    std::optional<std::wstring> XWF_GetCaseProp_CaseDirPath()
    {
        std::unique_ptr<WCHAR[]> pDir = std::make_unique<WCHAR[]>(MAX_PATH);
        INT64 returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetCaseProp(NULL, XWF::EvidenceAndCase::XWF_GetCaseProp_PropType_Dir, pDir.get(), MAX_PATH);

        if (returnedValue < 0 || pDir == nullptr)
        {
            return std::nullopt;
        }

        std::wstring dir = JCS::Utils::LPWStrToWString(pDir.get());
        return dir;
    }

    /// <summary>
    /// Retrieves a handle to the first evidence object in the case, or NULL if the active case has no evidence objects or (in releases from June 2016) if no case is active. In conjunction with XWF_GetNextEvObj this function allows to enumerate all evidence objects of the case. pReserved must be NULL. Available from v17.6. 
    /// </summary>
    /// <param name="pReserved"></param>
    /// <returns></returns>
    HANDLE XWF_GetFirstEvObj(LPVOID pReserved)
    {
        return XWF::EvidenceAndCase::XWF_GetFirstEvObj(pReserved);
    }

    /// <summary>
    /// Retrieves the next evidence object in the chain if there is another, or otherwise NULL. pReserved must be NULL. Available from v17.6. 
    /// </summary>
    /// <param name="hPrevEvidence"></param>
    /// <param name="pReserved"></param>
    /// <returns></returns>
    HANDLE XWF_GetNextEvObj(HANDLE hPrevEvidence, LPVOID pReserved)
    {
        return XWF::EvidenceAndCase::XWF_GetNextEvObj(hPrevEvidence, pReserved);
    }

    /// <summary>
    /// Removes the specified evidence object from the case. Not currently implemented. 
    /// <param name="hEvidence"></param>
    /// <returns></returns>
    /// </summary>
    HANDLE XWF_DeleteEvObj(HANDLE hEvidence)
    {
        return XWF::EvidenceAndCase::XWF_DeleteEvObj(hEvidence);
    }

    /// <summary>
    /// Available in v16.5 and later. Creates one or more evidence objects from one source (which can be a physical storage device, logical drive letter, disk or volume image, memory dump, a directory/path, or single file) and returns the first evidence object created, or NULL in case of an error (for example if that particular disk or image had been added to that case already). A case must already be loaded. If more than 1 evidence object is created (for example for a physical disk that contains partitions, which count as evidence objects themselves), use XWF_GetNextEvObj to find them. Evidence objects should not be created during an ongoing volume snapshot refinement or search etc. Potentially time-consuming if the volume snapshot is taken by X-Ways Forensics immediately when the evidence object is added.
    /// </summary>
    /// <param name="nType"></param>
    /// <param name="nDiskID"></param>
    /// <param name="lpPath"></param>
    /// <param name="pReserved"></param>
    /// <returns></returns>
    HANDLE XWF_CreateEvObj(DWORD nType, LONG nDiskID, LPWSTR lpPath, PVOID pReserved)
    {
        return XWF::EvidenceAndCase::XWF_CreateEvObj(nType, nDiskID, lpPath, pReserved);
    }

    /// <summary>
    /// If not currently open, opens the specified evidence object in a data window. A handle to the evidence object is expected for that, which is returned by the functions XWF_GetFirstEvObj, XWF_GetNextEvObj, and XWF_CreateEvObj. Such a handle remains valid until a case is closed. Opening an evidence object at the operating system level also means opening the corresponding disk or image file or interpreting the image file (if the evidence object is an image). This will also load or take the volume snapshot. This function returns a handle to the volume that the evidence object represents. Use this function if you wish to read data from the disk/volume or deal with its volume snapshot. Opening an evidence object is potentially time-consuming if the volume snapshot has to be taken at that time. Returns 0 if unsuccessful or otherwise a handle to the disk/volume that you can use with the Disk and General I/O Functions. Available from v17.6. nFlags must be 0 in v18.0 and older. 
    /// </summary>
    /// <param name="hEvidence"></param>
    /// <param name="nFlags"></param>
    /// <returns></returns>
    HANDLE XWF_OpenEvObj(HANDLE hEvidence, DWORD nFlags)
    {
        return XWF::EvidenceAndCase::XWF_OpenEvObj(hEvidence, nFlags);
    }

    /// <summary>
    /// Closes the specified evidence object if it is currently open, also the volume that it represents, and unloads the volume snapshot. Does nothing if the evidence object is not currently open. Available from v17.6. 
    /// </summary>
    /// <param name="hEvidence"></param>
    /// <returns></returns>
    VOID XWF_CloseEvObj(HANDLE hEvidence)
    {
        return XWF::EvidenceAndCase::XWF_CloseEvObj(hEvidence);
    }

    /// <summary>
    /// Retrieves information about the specified evidence object, either through the buffer or the return value, depending on what kind of information you require (nPropType). If through the return value, you may need to cast it to the appropriate type in order to correctly interpret/understand it. This function does not require that the evidence object is open. General error return code is -1. Available from v17.6.  
    /// </summary>
    /// <param name="hEvidence"></param>
    /// <param name="nPropType"></param>
    /// <param name="lpBuffer"></param>
    /// <returns></returns>
    std::optional<INT64> XWF_GetEvObjProp(std::optional<HANDLE> hEvidence, DWORD nPropType, PVOID lpBuffer)
    {
        if (!hEvidence || hEvidence.value() == nullptr)
        {
            JCS::Logging::Log("Evidence handle is null.", JCS::Logging::LogLevel::Error);
            return std::nullopt;
        }

        INT64 returnedValue = -1;
        returnedValue = XWF::EvidenceAndCase::XWF_GetEvObjProp(hEvidence.value(), nPropType, lpBuffer);

        if (returnedValue < 0)
        {
            JCS::Logging::Log(std::format("Getting evidence object property ({}) errored.", nPropType), JCS::Logging::LogLevel::Error);
            return std::nullopt;
        }

        return returnedValue;
    }

    std::optional<WORD> XWF_GetEvObjProp_EvidenceObjectNumber(HANDLE hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectNumber, nullptr);

        if (returnedValue)
        {
            std::optional<WORD> evidenceObjectNumber = static_cast<WORD>(returnedValue.value());
            return evidenceObjectNumber;
        }

        return std::nullopt;
    }

    std::optional<DWORD> XWF_GetEvObjProp_EvidenceObjectID(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectID, nullptr);

        if (returnedValue)
        {
            std::optional<DWORD> evidenceObjectID = static_cast<DWORD>(returnedValue.value());
            return evidenceObjectID;
        }

        return std::nullopt;
    }

    std::optional<DWORD> XWF_GetEvObjProp_EvidenceObjectParentID(std::optional<HANDLE> hEvidence)
    {

        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectParentID, nullptr);

        if (returnedValue)
        {
            std::optional<DWORD> evidenceObjectParentID = static_cast<DWORD>(returnedValue.value());
            return evidenceObjectParentID;
        }

        return std::nullopt;
    }

    std::optional<WORD> XWF_GetEvObjProp_EvidenceObjectShortID(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectShortID, nullptr);

        if (returnedValue)
        {
            std::optional<WORD> evidenceObjectParentShortID = static_cast<WORD>(returnedValue.value());
            return evidenceObjectParentShortID;
        }

        return std::nullopt;
    }

    std::optional<DWORD> XWF_GetEvObjProp_VolumeSnapshotID(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_VolumeSnapshotID, nullptr);

        if (returnedValue.has_value())
        {
            std::optional<DWORD> volumeSnapshotID = static_cast<WORD>(returnedValue.value());
            return volumeSnapshotID;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_EvidenceObjectTitle(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectitle, nullptr);

        if (returnedValue)
        {
            LPWSTR pEvidenceObjectTitle = reinterpret_cast<LPWSTR>(returnedValue.value());

            if (pEvidenceObjectTitle == nullptr)
            {
                return std::nullopt;
            }

            std::wstring EvidenceObjectTitle = JCS::Utils::LPWStrToWString(pEvidenceObjectTitle);
            return EvidenceObjectTitle;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_EvidenceObjectExtendedTitle(std::optional<HANDLE> hEvidence)
    {
        std::unique_ptr<WCHAR[]> pExtendedTitle = std::make_unique<WCHAR[]>(MAX_PATH);
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectitleExtended, pExtendedTitle.get());

        if (returnedValue)
        {
            std::wstring extendedTitle = JCS::Utils::WCharPointerToWString(pExtendedTitle.get());
            return extendedTitle;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_EvidenceObjectExtendedAbbreviatedTitle(std::optional<HANDLE> hEvidence)
    {
        std::unique_ptr<WCHAR[]> pExtendedAbbreviatedTitle = std::make_unique<WCHAR[]>(MAX_PATH);
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_EvidenceObjectitleExtendedAbbreviated, pExtendedAbbreviatedTitle.get());

        if (returnedValue)
        {
            std::wstring extendedAbbreviatedTitle = JCS::Utils::WCharPointerToWString(pExtendedAbbreviatedTitle.get());
            return extendedAbbreviatedTitle;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_InternalName(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_InternalName, nullptr);

        if (returnedValue)
        {
            LPWSTR pInternalName = reinterpret_cast<LPWSTR>(returnedValue.value());

            if (pInternalName == nullptr)
            {
                return std::nullopt;
            }

            std::wstring internalName = JCS::Utils::LPWStrToWString(pInternalName);
            return internalName;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_Description(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_Description, nullptr);

        if (returnedValue)
        {
            LPWSTR pDescription = reinterpret_cast<LPWSTR>(returnedValue.value());

            if (pDescription == nullptr)
            {
                return std::nullopt;
            }

            std::wstring description = JCS::Utils::LPWStrToWString(pDescription);
            return description;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_ExaminerComments(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_ExaminerComments, nullptr);

        if (returnedValue)
        {
            LPWSTR pExaminerComments = reinterpret_cast<LPWSTR>(returnedValue.value());

            if (pExaminerComments == nullptr)
            {
                return std::nullopt;
            }

            std::wstring examinerComments = JCS::Utils::LPWStrToWString(pExaminerComments);
            return examinerComments;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_InternallyUsedDirectory(std::optional<HANDLE> hEvidence)
    {
        std::unique_ptr<WCHAR[]> pInternallyUsedDirectory = std::make_unique<WCHAR[]>(MAX_PATH);
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_InternallyUsedDirectory, pInternallyUsedDirectory.get());

        if (returnedValue)
        {
            std::wstring internallyUsedDirectory = JCS::Utils::WCharPointerToWString(pInternallyUsedDirectory.get());
            return internallyUsedDirectory;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_OutputDirectory(std::optional<HANDLE> hEvidence)
    {
        std::unique_ptr<WCHAR[]> pOutputDirectory = std::make_unique<WCHAR[]>(MAX_PATH);
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_OutputDirectory, pOutputDirectory.get());

        if (returnedValue)
        {
            std::wstring outputDirectory = JCS::Utils::WCharPointerToWString(pOutputDirectory.get());
            return outputDirectory;
        }

        return std::nullopt;
    }

    std::optional<INT64> XWF_GetEvObjProp_SizeInBytes(std::optional<HANDLE> hEvidence)
    {
        auto sizeInBytes = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_SizeInBytes, nullptr);
        return sizeInBytes;
    }

    std::optional<DWORD> XWF_GetEvObjProp_VolumeSnapshotFileCount(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_VolumeSnapshotFileCount, nullptr);

        if (returnedValue)
        {
            DWORD volumeSnapshotFileCount = static_cast<DWORD>(returnedValue.value());
            return volumeSnapshotFileCount;
        }

        return std::nullopt;
    }

    std::optional<INT64> XWF_GetEvObjProp_Flags(std::optional<HANDLE> hEvidence)
    {
        auto flags = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_Flags, nullptr);
        return flags;
    }

    std::optional<INT64> XWF_GetEvObjProp_FileSystemIdentifier(std::optional<HANDLE> hEvidence)
    {
        auto fileSystemIdentifier = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_FileSystemIdentifier, nullptr);
        return fileSystemIdentifier;
    }

    std::optional<DWORD> XWF_GetEvObjProp_HashOneType(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_HashTypeOne, nullptr);

        if (returnedValue)
        {
            DWORD hashType = static_cast<DWORD>(returnedValue.value());
            return hashType;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_HashOneValue(std::optional<HANDLE> hEvidence)
    {
        std::unique_ptr<BYTE[]> pHash = std::make_unique<BYTE[]>(MAX_PATH);
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_HashValueOne, pHash.get());

        if (returnedValue)
        {
            std::wstring hashValue = JCS::Utils::BytesToHex(pHash.get(), returnedValue.value());
            return hashValue;
        }

        return std::nullopt;
    }

    std::optional<SYSTEMTIME> XWF_GetEvObjProp_CreationTime(std::optional<HANDLE> hEvidence)
    {
        auto evidenceObjectCreationTime = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_CreationTime, nullptr);

        if (evidenceObjectCreationTime)
        {
            SYSTEMTIME creationTime = JCS::Utils::Int64FileTimeToSystemTime(evidenceObjectCreationTime.value());
            return creationTime;
        }

        return std::nullopt;
    }

    std::optional<SYSTEMTIME> XWF_GetEvObjProp_ModifiedTime(std::optional<HANDLE> hEvidence)
    {
        auto evidenceObjectModifiedTime = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_ModifiedTime, nullptr);

        if (evidenceObjectModifiedTime)
        {
            SYSTEMTIME modifiedTime = JCS::Utils::Int64FileTimeToSystemTime(evidenceObjectModifiedTime.value());
            return modifiedTime;
        }

        return std::nullopt;
    }

    std::optional<DWORD> XWF_GetEvObjProp_HashTwoType(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_HashTypeTwo, nullptr);

        if (returnedValue)
        {
            DWORD hashType = static_cast<DWORD>(returnedValue.value());
            return hashType;
        }

        return std::nullopt;
    }

    std::optional<std::wstring> XWF_GetEvObjProp_HashTwoValue(std::optional<HANDLE> hEvidence)
    {
        std::unique_ptr<BYTE[]> pHash = std::make_unique<BYTE[]>(MAX_PATH);
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_HashValueTwo, pHash.get());

        if (returnedValue)
        {
            std::wstring hashValue = JCS::Utils::BytesToHex(pHash.get(), returnedValue.value());
            return hashValue;
        }

        return std::nullopt;
    }

    std::optional<WORD> XWF_GetEvObjProp_DataWindow(std::optional<HANDLE> hEvidence)
    {
        auto returnedValue = JCS::XWFWrapper::EvidenceAndCase::XWF_GetEvObjProp(hEvidence, XWF::EvidenceAndCase::XWF_GetEvObjProp_PropType_DataWindow, nullptr);

        if (returnedValue)
        {
            WORD dataWindow = static_cast<WORD>(returnedValue.value());
            return dataWindow;
        }

        return std::nullopt;
    }

    /// <summary>
    ///  Sets information about the specified evidence object. See above for possible values of nPropType. Only those marked * cannot be used with this function. Strings must be null-terminated. Not currently implemented. 
    /// </summary>
    /// <param name="hEvidence"></param>
    /// <param name="nPropType"></param>
    /// <param name="pBuffer"></param>
    /// <returns></returns>
    LONG XWF_SetEvObjProp(HANDLE hEvidence, LONG nPropType, PVOID pBuffer)
    {
        return XWF::EvidenceAndCase::XWF_SetEvObjProp(hEvidence, nPropType, pBuffer);
    }

    /// <summary>
    /// Retrieves a handle to the evidence object with the specified unique ID. Returns NULL if not found. The unique ID of an evidence object remains the same after closing and re-opening a case, whereas the handle will likely change. The evidence object number may also change. That happens if the user re-orders the evidence objects in the case. The unique ID, however, is guaranteed to never change and also guaranteed to be unique within the case (actually likely unique even across all the cases that the user will ever deal with) and can be used to reliably recognize a known evidence object. Available from v18.7.
    /// </summary>
    /// <param name="nEvObjID"></param>
    /// <returns></returns>
    HANDLE XWF_GetEvObj(DWORD nEvObjID)
    {
        return XWF::EvidenceAndCase::XWF_GetEvObj(nEvObjID);
    }

    /// <summary>
    /// Available in v17.7 and later. If nReportTableID designates an existing label or report table in the current case, returns a pointer to the null-terminated name of that label/report table, or otherwise NULL. nReportTableID may be set to -1 to retrieve the maximum number of labels/report tables supported by the active version in the integer pointed to by lpOptional. Valid label/report table IDs range from 0 to (maximum number-1). pReserved must be NULL. lpOptional must point to a 0 when called.
    /// </summary>
    /// <param name="pReserved"></param>
    /// <param name="nReportTableID"></param>
    /// <param name="lpOptional"></param>
    /// <returns></returns>
    LPVOID XWF_GetReportTableInfo(LPVOID pReserved, LONG nReportTableID, PLONG lpOptional)
    {
        return XWF::EvidenceAndCase::XWF_GetReportTableInfo(pReserved, nReportTableID, lpOptional);
    }

    /// <summary>
    /// Available in v17.7 and later. Returns a pointer to an internal list that describes all labels/report table associations of the specified evidence object, or NULL if unsuccessful (for example if not available any more in a future version). Scanning this list is a much quicker way to find out which items are labeled in what way than calling GetReportTableAssocs for all items in a volume snapshot, especially if the snapshot is huge. The list consists of 16-bit report table ID and 32-bit item ID pairs repeatedly, stored back to back. The integer pointed to by lpValue is set to the number of pairs in the data structure. You may set the flag 0x01 in nFlags to request a list sorted by item IDs. Other flags must not be set at this time.
    /// </summary>
    /// <param name="hEvidence"></param>
    /// <param name="nFlags"></param>
    /// <param name="lpValue"></param>
    /// <returns></returns>
    LPVOID XWF_GetEvObjReportTableAssocs(HANDLE hEvidence, LONG nFlags, PLONG lpValue)
    {
        return XWF::EvidenceAndCase::XWF_GetEvObjReportTableAssocs(hEvidence, nFlags, lpValue);
    }
}
