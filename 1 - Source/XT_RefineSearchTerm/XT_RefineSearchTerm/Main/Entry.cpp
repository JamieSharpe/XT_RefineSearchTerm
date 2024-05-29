///////////////////////////////////////////////////////////////////////////////
// X-Tension Template
// Author: Jamie Sharpe
///////////////////////////////////////////////////////////////////////////////

#include "JCS/XWFWrapper/XWFWrapper.h"
#include <Windows.h>

import Build;
import XTension;
import Logging;
import Utils;
import Main;
import std;

/// <summary>
/// XT_Init
/// 
/// Mandatory to export. Will be called before anything else happens, before the X-Tension does its actual job,
/// among other things to inform the DLL of the version of X-Ways Forensics that is loading the DLL, already when
/// the X-Tension is selected by the user in X-Ways Forensics. You may return -1 to prevent further use of the DLL,
/// for example if certain functions that you require are not present (i.e. exported only by a newer version of
/// X-Ways Forensics) or if you detect an environment in which your DLL is not meant or licensed to run. Otherwise
/// you must return either 1 or (if you consider your X-Tension to be thread-safe) 2. If your X-Tension does not
/// identify itself as thread-safe, that may result in suboptimal performance of X-Ways Forensics during volume
/// snapshot refinement operations which invoke your X-Tension. At least disk I/O X-Tensions should be made
/// thread-safe. If you call XWF_* functions that alter data (in the case or volume snapshot), please ensure
/// that you call each of them only once concurrently.
/// </summary>
/// <param name="nVersion">The higher word specifies the version number.For example 2040 means v20.4.
/// The third highest byte specified the service release number.The lowest byte specifies the current
/// language of the user interface of the calling program.</param>
/// <param name="nFlags">
/// See <c>XWF::Core::XT_Init_*</c>
/// </param>
/// <param name="hMainWnd">Handle of the main window in case you need it, for example as a parent window for a message box.</param>
/// <param name="pLicInfo">Points to a structure that contains information about the license.</param>
/// <returns></returns>
LONG __stdcall XT_Init(DWORD nVersion, DWORD nFlags, HANDLE hMainWnd, struct XWF::Core::LicenseInfo* pLicInfo)
{
    auto functionMetaData = XWF::Other::XT_RetrieveFunctionPointers();

    JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage(std::format(L" Initialising - {}", Build::BuildInfo::title), 0);

    LONG returnValue = XWF::Core::XT_Init_Return_Abort;
    std::exception_ptr globalExceptionPointer;
    try
    {
        JCS::Logging::SetupFileLogger();

        JCS::Logging::Log(Build::BuildInfo::title);

        JCS::Logging::Log("Function Start: 'XT_Init'", JCS::Logging::LogLevel::Trace);

        returnValue = XT_RefineSearchTerm::Main::Init(nVersion, nFlags, hMainWnd, pLicInfo);

        JCS::Logging::Log("Function End: 'XT_Init'", JCS::Logging::LogLevel::Trace);
    }
    catch (...)
    {
        /// Output to logger and directly to XWF output window in case it was the logger than threw the exception.
        std::wstring message = L"FATAL ERROR: GLOBAL CATCH ALL EXCEPTIONS ENGAGED - 'XT_INIT'.";
        JCS::XWFWrapper::Miscellaneous::XWF_OutputMessage(message.data(), 0);
        JCS::Logging::Log(message, JCS::Logging::LogLevel::Critical);
        globalExceptionPointer = std::current_exception();
    }

    bool handledException = JCS::Utils::HandleExceptionPtr(globalExceptionPointer);

    return returnValue;
}

/// <summary>
/// XT_About
/// 
/// If exported (optional), will be called when the user requests to see information about the DLL.
/// You can display copyright notices, a version number, a brief description of the exported functionality,
/// extensive help on how to use it, from where in X-Ways Forensics to call it with what settings etc. etc.
/// You could even display a dialog window where the user can change settings for this X-Tension, which you
/// store in the Windows registry or in a permanent file.
/// 
/// You should return 0.
/// </summary>
/// <param name="hParentWnd"></param>
/// <param name="lpReserved">Currently always NULL.</param>
/// <returns></returns>
LONG __stdcall XT_About(HANDLE hParentWnd, PVOID lpReserved)
{
    LONG returnValue = XWF::Ordinary::XT_About_NoAction;
    std::exception_ptr globalExceptionPointer;
    try
    {
        JCS::Logging::Log("Function Start: 'XT_About'", JCS::Logging::LogLevel::Trace);

        returnValue = XT_RefineSearchTerm::Main::About(hParentWnd, lpReserved);

        JCS::Logging::Log("Function End: 'XT_About'", JCS::Logging::LogLevel::Trace);
    }
    catch (...)
    {
        JCS::Logging::Log("FATAL ERROR: GLOBAL CATCH ALL EXCEPTIONS ENGAGED - 'XT_About'.", JCS::Logging::LogLevel::Critical);
        globalExceptionPointer = std::current_exception();
    }

    bool handledException = JCS::Utils::HandleExceptionPtr(globalExceptionPointer);

    return returnValue;
}

/// <summary>
/// XT_Prepare
/// 
/// If exported (optional), will be called immediately for a volume when volume snapshot refinement or some other
/// action starts, before items or search hits in that volume are processed individually, or simply when the user
/// runs your X-Tension from the main menu or command line or applies it to selected files directly. Your X-Tension
/// can do its actual job when responding to a call of this function or any of the other below functions. The nOpType
/// parameter tells you in which context exactly your X-Tension is running.
/// 
/// Possible negative return values:
/// -4 if you want X - Ways Forensics to stop the whole operation(e.g.volume snapshot refinement) altogether
/// -3 if you want to prevent further use of the X - Tension for the remainder of the whole operation, for example because your X - Tension is not supposed to do anything for that kind of operation as indicated by nOpType or because your X - Tension expects to be applied to a particular data window(requiring hVolume to be unequal to 0)
/// -2 if you want this particular volume excluded from the operation
/// -1 if you don't want other functions of this X-Tension to be called for this particular volume, not even XT_Finalize()
/// Full negative return value evaluation only for XT_ACTION_RVS.
/// 
/// 0 is the default return value, if you just want XT_Finalize() to be called.Will also be assumed if you do not export XT_Prepare().
/// 
/// Positive return values are a combination of these flags :
/// #define XT_PREPARE_CALLPI 0x01
/// #define XT_PREPARE_CALLPILATE 0x02
/// #define XT_PREPARE_EXPECTMOREITEMS 0x04
/// #define XT_PREPARE_DONTOMIT 0x08
/// #define XT_PREPARE_TARGETDIRS 0x10
/// #define XT_PREPARE_TARGETZEROBYTEFILES 0x20
/// 
/// XT_PREPARE_CALLPI: if you want X - Ways Forensics to call your implementation of XT_ProcessItem[Ex]() (whichever is exported) for each item this volume snapshot(not if the volume snapshot is not targeted, e.g. in case of XT_ACTION_RUN)
/// XT_PREPARE_CALLPILATE : for XT_ACTION_RVS specify this flag in addition to XT_PREPARE_CALLPI if you wish to receive calls of XT_ProcessItem() (not Ex), if actually exported, after all other individual item refinement operations instead of before(preferable for example so that you do not get called for ignorable files that were recognized as such by hash database matching during the same volume snapshot refinement run)
/// XT_PREPARE_EXPECTMOREITEMS : in case of XT_ACTION_RVS, to signal XWF that you may create more items in the volume snapshot, so that for example the user will definitely be informed of how many item were added(v16.5 and later only)
/// XT_PREPARE_DONTOMIT: in case of XT_ACTION_RVS, to signal XWF that you wish to receive calls for XT_ProcessItem[Ex]() even for files that the user wants to omit for any of the possible three reasons(v18.5 and later only)
/// XT_PREPARE_TARGETDIRS: in case of XT_ACTION_RVS, to signal XWF that you wish to receive calls for XT_ProcessItem[Ex]() even for directories, not only files, for example because you wish to parse the file system data structures in those directories(v18.5 and later only)
/// XT_PREPARE_TARGETZEROBYTEFILES: in case of XT_ACTION_RVS, to signal XWF that you wish to receive calls for XT_ProcessItem[Ex]() even for files that have a size of 0 bytes, which are otherwise skipped for performance reasons(v18.9 SR - 7 and later only)
/// </summary>
/// <param name="hVolume">Typically a handle to the volume that the X - Tension is applied to.
/// 0 (i.e. not a valid handle) if run from the main menu or command line with no data window open, i.e. when not applied to anything.
/// A handle to a file if run from the main window if the active data window represents a single file opened via File | Open.
/// To make sure that a non - zero handle is a handle to a volume, you can call XWF_GetVolumeInformation and check that lpBytesPerSector 
/// retrieves a value unequal to zero. Or, if your X - Tension is intended to be applied to a file opened that way, verify that
/// lpBytesPerSector retrieves zero.</param>
/// <param name="hEvidence">From v17.5 SR - 2, a handle to an evidence object if hVolume represents an evidence object, otherwise 0.</param>
/// <param name="nOpType">How the X - Tension is executed within X - Ways Forensics.
/// #define XT_ACTION_RUN 0 // simply run directly from the main menu or command line3
/// #define XT_ACTION_RVS 1 // volume snapshot refinement starting2
/// #define XT_ACTION_LSS 2 // logical simultaneous search starting
/// #define XT_ACTION_PSS 3 // physical simultaneous search starting
/// #define XT_ACTION_DBC 4 // directory browser context menu command invoked1
/// #define XT_ACTION_SHC 5 // search hit list context menu command invoked
/// #define XT_ACTION_EVT 6 // event list context menu command invoked (since v20.3 SR-3)
/// 
/// 	1 Run from the directory browser context menu, an X - Tension is applied to selected files.This may occur in the case root window, not for just one particular volume!XT_ProcessItem() is not necessarily called for the selected items in the order in which they are listed in the directory browser.
/// 	2 Run from Specialist | Refine Volume Snapshot, the X - Tension is applied to a volume snapshot(all files if you want).
/// 	3 Run from Tools | Run X - Tension, the X - Tension is applied to the data window as a whole(the file or disk or image represented by the active data window), but not to the volume snapshot.The data window could be one with no volume snapshot at all(e.g.an ordinary binary file opened with File | Open).So there are no "items" in that sense that need to be processed(XT_ProcessItem[Ex]() is not called!) because no volume snapshot is targeted in the first place.
/// </param>
/// <param name="lpReserved">Currently always NULL.</param>
/// <returns></returns>
LONG __stdcall XT_Prepare(HANDLE hVolume, HANDLE hEvidence, DWORD nOpType, PVOID lpReserved)
{
    LONG returnValue = XWF::Ordinary::XT_Prepare_NoAction;
    std::exception_ptr globalExceptionPointer;
    try
    {
        JCS::Logging::Log("Function Start: 'XT_Prepare'", JCS::Logging::LogLevel::Trace);

        /// Error check for Volume Handle.
        std::optional<HANDLE> hVolumeOpt = std::nullopt;

        if (hVolume == nullptr)
        {
            hVolumeOpt = std::nullopt;
            JCS::Logging::Log(L"Volume handle object is: " + JCS::Utils::OptionalValueToString(hVolumeOpt), JCS::Logging::LogLevel::Warning);
        }
        else
        {
            hVolumeOpt = hVolume;
        }

        /// Error check for Evidence Handle.
        std::optional<HANDLE> hEvidenceOpt = std::nullopt;

        if (hEvidence == nullptr)
        {
            hEvidenceOpt = std::nullopt;
            JCS::Logging::Log(L"Evidence handle object is: " + JCS::Utils::OptionalValueToString(hEvidenceOpt), JCS::Logging::LogLevel::Warning);
        }
        else
        {
            hEvidenceOpt = hEvidence;
        }

        returnValue = XT_RefineSearchTerm::Main::Prepare(hVolumeOpt, hEvidenceOpt, nOpType, lpReserved);

        JCS::Logging::Log("Function End: 'XT_Prepare'", JCS::Logging::LogLevel::Trace);
    }
    catch (...)
    {
        JCS::Logging::Log("FATAL ERROR: GLOBAL CATCH ALL EXCEPTIONS ENGAGED - 'XT_Prepare'.", JCS::Logging::LogLevel::Critical);
        globalExceptionPointer = std::current_exception();
    }

    bool handledException = JCS::Utils::HandleExceptionPtr(globalExceptionPointer);

    return returnValue;
}

/// <summary>
/// XT_Finalize
/// 
/// If exported (optional), will be called when volume snapshot refinement or another operation has completed.
/// Return 1 if the current directory listing in the directory browser of the active data window has to be
/// refreshed after XT_ACTION_DBC (usually not necessary, perhaps when adding new files to the directory,
/// has an effect in v17.6 and later only), or otherwise 0.
/// </summary>
/// <param name="hVolume">Typically a handle to the volume that the X - Tension is applied to. See 'XT_Prepare'.</param>
/// <param name="hEvidence">From v17.6, a handle to an evidence object if the hVolume represents an evidence object, otherwise 0.</param>
/// <param name="nOpType">See above.</param>
/// <param name="lpReserved">Currently always NULL.</param>
/// <returns></returns>
LONG __stdcall XT_Finalize(HANDLE hVolume, HANDLE hEvidence, DWORD nOpType, PVOID lpReserved)
{
    LONG returnValue = XWF::Ordinary::XT_Finalize_NoAction;
    std::exception_ptr globalExceptionPointer;
    try
    {
        JCS::Logging::Log("Function Start: 'XT_Finalize'", JCS::Logging::LogLevel::Trace);

        /// Error check for Volume Handle.
        std::optional<HANDLE> hVolumeOpt = std::nullopt;

        if (hVolume == nullptr)
        {
            hVolumeOpt = std::nullopt;
            JCS::Logging::Log(std::format(L"Volume handle object is: {}", JCS::Utils::OptionalValueToString(hVolumeOpt)), JCS::Logging::LogLevel::Warning);
        }
        else
        {
            hVolumeOpt = hVolume;
        }

        /// Error check for Evidence Handle.
        std::optional<HANDLE> hEvidenceOpt = std::nullopt;

        if (hEvidence == nullptr)
        {
            hEvidenceOpt = std::nullopt;
            JCS::Logging::Log(std::format(L"Evidence handle object is: {}", JCS::Utils::OptionalValueToString(hEvidenceOpt)), JCS::Logging::LogLevel::Warning);
        }
        else
        {
            hEvidenceOpt = hEvidence;
        }

        returnValue = XT_RefineSearchTerm::Main::Finalize(hVolumeOpt, hEvidenceOpt, nOpType, lpReserved);

        JCS::Logging::Log("Function End: 'XT_Finalize'", JCS::Logging::LogLevel::Trace);
    }
    catch (...)
    {
        JCS::Logging::Log("FATAL ERROR: GLOBAL CATCH ALL EXCEPTIONS ENGAGED - 'XT_Finalize'.", JCS::Logging::LogLevel::Critical);
        globalExceptionPointer = std::current_exception();
    }

    bool handledException = JCS::Utils::HandleExceptionPtr(globalExceptionPointer);

    return returnValue;
}

/// <summary>
/// XT_PrepareSearch
/// 
/// If exported (optional), will be called by v16.9 and later if an X-Tension is loaded for use with a simultaneous search,
/// so that the X-Tension can enter predefined search terms into the dialog window for use with the search. The X-Tension
/// can also learn about the current search settings (the active code pages and some other settings through the flags field)
/// and could inform the user of necessary adjustments for the search to work as intended by the X-Tension.
/// 
/// Return:
/// 1	if you have made adjustments to the search terms.
/// 0	if not.
/// -1	if you are not happy with the current settings at all and want the X-Tension to be unselected. 
/// 
/// Adjustments to the pointer, to the buffer size, to the flags or the code pages are currently ignored.
/// </summary>
/// <param name="pPSInfo">Prepared search terms info.</param>
/// <param name="CPages">Indicates code pages currently selected for the search.See this web page for possible code page identifiers. 0 means unused code page.</param>
/// <returns></returns>
LONG __stdcall XT_PrepareSearch(struct XWF::Ordinary::PrepareSearchInfo* pPSInfo, struct XWF::Search::CodePages* CPages)
{
    LONG returnValue = XWF::Ordinary::XT_PrepareSearch_NoAdjustmentMade;
    std::exception_ptr globalExceptionPointer;
    try
    {
        JCS::Logging::Log("Function Start: 'XT_PrepareSearch'", JCS::Logging::LogLevel::Trace);

        returnValue = XT_RefineSearchTerm::Main::PrepareSearch(pPSInfo, CPages);

        JCS::Logging::Log("Function End: 'XT_PrepareSearch'", JCS::Logging::LogLevel::Trace);
    }
    catch (...)
    {
        JCS::Logging::Log("FATAL ERROR: GLOBAL CATCH ALL EXCEPTIONS ENGAGED - 'XT_PrepareSearch'.", JCS::Logging::LogLevel::Critical);
        globalExceptionPointer = std::current_exception();
    }

    bool handledException = JCS::Utils::HandleExceptionPtr(globalExceptionPointer);

    return returnValue;
}

/// <summary>
/// XT_ProcessSearchHit
/// 
/// If exported (optional), this function will be called for each search hit when it is found (or in a future version of X-Ways Forensics perhaps later if selected by the user in a search hit list). Return 0, except if you want X-Ways Forensics to abort the search (return -1) or if you want X-Ways Forensics to stop calling you (return -2). This function is not called if the search was initiated by the X-Tension itself (via XWF_Search).
/// 
/// If you call XWF_SelectVolumeSnapshot() while responding to a call to XT_ProcessSearchHit(), you have to call it again to undo the change before returning control.
/// </summary>
/// <param name="info"></param>
/// <returns></returns>
LONG __stdcall XT_ProcessSearchHit(XWF::Search::SearchHitInfo* info)
{
    LONG returnValue = XWF::Ordinary::XT_ProcessSearchHit_NoFurtherAction;
    std::exception_ptr globalExceptionPointer;
    try
    {
        JCS::Logging::Log("Function Start: 'XT_ProcessSearchHit'", JCS::Logging::LogLevel::Trace);

        returnValue = XT_RefineSearchTerm::Main::ProcessSearchHit(info);

        JCS::Logging::Log("Function End: 'XT_ProcessSearchHit'", JCS::Logging::LogLevel::Trace);
    }
    catch (...)
    {
        JCS::Logging::Log("FATAL ERROR: GLOBAL CATCH ALL EXCEPTIONS ENGAGED - 'XT_ProcessSearchHit'.", JCS::Logging::LogLevel::Critical);
        globalExceptionPointer = std::current_exception();
    }

    bool handledException = JCS::Utils::HandleExceptionPtr(globalExceptionPointer);

    return returnValue;
}
