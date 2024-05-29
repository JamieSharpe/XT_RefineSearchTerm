module;

#include <Windows.h>

export module Main;

import Utils;
import XTension;
import Logging;
import XWUtils;
import Build;
import ItemObject;
import VolumeObject;
import SearchHitInfo;
import std;

namespace XT_RefineSearchTerm
{
    /// <summary>
    /// Create null volume object pointer. TODO: Put this in a better place.
    /// This is a shared pointer amongst the volume, and items within the volume which may need access/manipulate it as well.
    /// </summary>
    export std::shared_ptr<Models::VolumeObject> volume{};
    int readPrePostCount = 0;
    int percentageRequired = 0;

    export class Main
    {
    private:
    public:
        /// <summary>
        /// Init
        /// 
        /// Will be called before anything else happens, before the X-Tension does its actual job,
        /// among other things to inform the DLL of the version of X-Ways Forensics that is loading the DLL, already when
        /// the X-Tension is selected by the user in X-Ways Forensics. 
        /// </summary>
        /// <param name="nVersion">The higher word specifies the version number.For example 2040 means v20.4.
        /// The third highest byte specified the service release number.The lowest byte specifies the current
        /// language of the user interface of the calling program.</param>
        /// <param name="nFlags">A flag which states what software is currently running. See XT_INIT_*</param>
        /// <param name="hMainWnd">Handle of the main window in case you need it, for example as a parent window for a message box.</param>
        /// <param name="pLicInfo">Points to a structure that contains information about the license.</param>
        /// <returns>
        /// <para>Return -1 to prevent further use of the DLL, for example if certain functions that you require
        /// are not present (i.e. exported only by a newer version of X-Ways Forensics) or if you detect an environment
        /// in which your DLL is not meant or licensed to run.</para>
        ///
        /// <para>Return 1 if the X-Tension is not thread safe.</para>
        /// 
        /// <para>Return 2 if the X-Tension is thread-safe.</para>
        /// 
        /// <para>If your X-Tension does not identify itself as thread-safe, that may result in suboptimal performance
        /// of X-Ways Forensics during volume snapshot refinement operations which invoke your X-Tension.</para>
        /// 
        /// <para>At least disk I/O X-Tensions should be made thread-safe. If you call XWF_* functions that alter
        /// data (in the case or volume snapshot), please ensure that you call each of them only once concurrently.</para>
        /// </returns>
        static LONG Init(DWORD nVersion, DWORD nFlags, HANDLE hMainWnd, struct XWF::Core::LicenseInfo* pLicInfo)
        {
            return XWF::Core::XT_Init_Return_SingleThread;
        }

        /// <summary>
        /// About
        /// 
        /// Will be called when the user requests to see information about the DLL.
        /// You can display copyright notices, a version number, a brief description of the exported functionality,
        /// extensive help on how to use it, from where in X-Ways Forensics to call it with what settings etc. etc.
        /// You could even display a dialog window where the user can change settings for this X-Tension, which you
        /// store in the Windows registry or in a permanent file.
        /// </summary>
        /// <param name="hParentWnd"></param>
        /// <param name="lpReserved">Currently always NULL.</param>
        /// <returns>You should return 0.</returns>
        static LONG About(HANDLE hParentWnd, PVOID lpReserved)
        {
            JCS::Logging::Log("About:");
            JCS::Logging::Log(Build::BuildInfo::title);
            JCS::Logging::Log("Project's URL: https://github.com/JamieSharpe/XT_RefineSearchTerm");
            JCS::Logging::Log("Author's URL: https://jamiesharpe.co.uk");
            JCS::Logging::Log("Copyright (C) 2024 Jamie Sharpe");

            std::string licenseInfo = "License:\r\n"
                "This program is free software: you can redistribute it and/or modify\r\n"
                "it under the terms of the GNU General Public License as published by\r\n"
                "the Free Software Foundation, either version 3 of the License, or\r\n"
                "(at your option) any later version.\r\n"
                "This program is distributed in the hope that it will be useful,\r\n"
                "but WITHOUT ANY WARRANTY; without even the implied warranty of\r\n"
                "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the\r\n"
                "GNU General Public License for more details.\r\n"
                "You should have received a copy of the GNU General Public License\r\n"
                "along with this program. If not, see <https://www.gnu.org/licenses/>.";

            JCS::Logging::Log(licenseInfo);

            return XWF::Ordinary::XT_About_NoAction;
        }

        /// <summary>
        /// Prepare
        /// 
        /// Will be called immediately for a volume when volume snapshot refinement or some other
        /// action starts, before items or search hits in that volume are processed individually, or simply when the user
        /// runs your X-Tension from the main menu or command line or applies it to selected files directly. Your X-Tension
        /// can do its actual job when responding to a call of this function or any of the other below functions. The nOpType
        /// parameter tells you in which context exactly your X-Tension is running.
        /// </summary>
        /// <param name="hVolume">Typically a handle to the volume that the X - Tension is applied to.
        /// 0 (i.e. not a valid handle) if run from the main menu or command line with no data window open, i.e. when not applied to anything.
        /// A handle to a file if run from the main window if the active data window represents a single file opened via File | Open.
        /// To make sure that a non - zero handle is a handle to a volume, you can call XWF_GetVolumeInformation and check that lpBytesPerSector 
        /// retrieves a value unequal to zero. Or, if your X - Tension is intended to be applied to a file opened that way, verify that
        /// lpBytesPerSector retrieves zero.</param>
        /// <param name="hEvidence">From v17.5 SR-2, a handle to an evidence object if hVolume represents an evidence object, otherwise 0.</param>
        /// <param name="nOpType">How the X - Tension is executed within X - Ways Forensics. See: XT_ACTION_*</param>
        /// <param name="lpReserved">Currently always NULL.</param>
        /// <returns>
        /// <para>
        /// Possible negative return values:
        /// </para>
        /// <para>
        /// -4 if you want X - Ways Forensics to stop the whole operation(e.g.volume snapshot refinement) altogether
        /// </para>
        /// <para>
        /// -3 if you want to prevent further use of the X - Tension for the remainder of the whole operation, for example because your X - Tension is not supposed to do anything for that kind of operation as indicated by nOpType or because your X - Tension expects to be applied to a particular data window(requiring hVolume to be unequal to 0)
        /// </para>
        /// <para>
        /// -2 if you want this particular volume excluded from the operation
        /// </para>
        /// <para>
        /// -1 if you don't want other functions of this X-Tension to be called for this particular volume, not even XT_Finalize()
        /// </para>
        /// <para>
        /// Full negative return value evaluation only for XT_ACTION_RVS.
        /// </para>
        /// <para>
        /// 0 is the default return value, if you just want XT_Finalize() to be called. Will also be assumed if you do not export XT_Prepare().
        /// </para>
        /// <para>
        /// Positive return values are a combination of these flags: See XT_PREPARE_*
        /// </para>
        /// </returns>
        static LONG Prepare(std::optional<HANDLE> hVolume, std::optional<HANDLE> hEvidence, DWORD nOpType, PVOID lpReserved)
        {
            JCS::Logging::Log(std::format(L"Running Type: {}", JCS::XWUtils::XTensionOperationTypeToWString(nOpType)));

            int attempts = 0;

            if (readPrePostCount != 0)
            {
                JCS::Logging::Log(std::format("Bytes to read has already been set as: {}", readPrePostCount));
            }
            else
            {
                while (attempts < 3)
                {
                    INT64 byteCountInput = JCS::XWUtils::GetUserInputNumber(L"Bytes before and after for the search hit (typically 20):");

                    if (byteCountInput <= 0 || byteCountInput > 4096)
                    {
                        JCS::Logging::Log(std::format("Invalid read byte count: {}", byteCountInput));
                        JCS::Logging::Log("Please enter a number between 1 and 4096 (inclusive).");
                        attempts++;
                        continue;
                    }

                    readPrePostCount = byteCountInput;
                    break;
                }

                if (attempts >= 3)
                {
                    JCS::Logging::Log(std::format(L"Invalid excerpt buffer input, the {} will not be run.", Build::BuildInfo::appName));
                    return -3;
                }
            }

            JCS::Logging::Log(std::format("Bytes to read before and after search term for excerpt: {}", readPrePostCount));

            if (percentageRequired != 0)
            {
                JCS::Logging::Log(std::format("Readable character percentage has already been set as: {}", percentageRequired));
            }
            else
            {
                attempts = 0;
                while (attempts < 3)
                {
                    INT64 percentageRequiredInput = JCS::XWUtils::GetUserInputNumber(L"Percentage of readable characters to mark the search hit positive:");

                    if (percentageRequiredInput <= 0 || percentageRequiredInput > 100)
                    {
                        JCS::Logging::Log(std::format("Invalid percentage: {}", percentageRequiredInput));
                        JCS::Logging::Log("Please enter a number between 1 and 100 (inclusive).");
                        attempts++;
                        continue;
                    }

                    percentageRequired = percentageRequiredInput;
                    break;
                }

                if (attempts >= 3)
                {
                    JCS::Logging::Log(std::format(L"Invalid required percentage input, the {} will not be run.", Build::BuildInfo::appName));
                    return -3;
                }
            }

            JCS::Logging::Log(std::format("Readable character percentage in excerpt: {}", percentageRequired));

            // Setup volume object.
            volume = std::make_shared<Models::VolumeObject>(hVolume, hEvidence);

            return XWF::Ordinary::XT_Prepare_CallProcessItem | XWF::Ordinary::XT_Prepare_CallProcessItemLate;
        }

        /// <summary>
        /// Finalize
        /// 
        /// Will be called when volume snapshot refinement or another operation has completed.
        /// </summary>
        /// <param name="hVolume">Typically a handle to the volume that the X - Tension is applied to. See 'XT_Prepare'.</param>
        /// <param name="hEvidence">From v17.6, a handle to an evidence object if the hVolume represents an evidence object, otherwise 0.</param>
        /// <param name="nOpType">See above.</param>
        /// <param name="lpReserved">Currently always NULL.</param>
        /// <returns>
        /// <para>
        ///     Return 1 if the current directory listing in the directory browser of the active data window has to be
        ///     refreshed after XT_ACTION_DBC (usually not necessary, perhaps when adding new files to the directory,
        ///     has an effect in v17.6 and later only)
        /// </para>
        /// 
        /// <para>
        ///     Return 0 otherwise.
        /// </para>
        /// </returns>
        static LONG Finalize(std::optional<HANDLE> hVolume, std::optional<HANDLE> hEvidence, DWORD nOpType, PVOID lpReserved)
        {
            JCS::Logging::Log("Finalising the process of a volume.", JCS::Logging::LogLevel::Debug);

            return XWF::Ordinary::XT_Finalize_NoAction;
        }

        /// <summary>
        /// PrepareSearch
        /// 
        /// <para>Will be called by v16.9 and later if an X-Tension is loaded for use with a simultaneous search,
        /// so that the X-Tension can enter predefined search terms into the dialog window for use with the search. The X-Tension
        /// can also learn about the current search settings (the active code pages and some other settings through the flags field)
        /// and could inform the user of necessary adjustments for the search to work as intended by the X-Tension.</para>
        /// 
        /// <para>Adjustments to the pointer, to the buffer size, to the flags or the code pages are currently ignored.</para>
        /// </summary>
        /// <param name="pPSInfo">Prepared search terms info.</param>
        /// <param name="CPages">Indicates code pages currently selected for the search.See this web page for possible code page identifiers. 0 means unused code page.</param>
        /// <returns>
        /// <para>Return XWF::Ordinary::XT_PrepareSearch_AdjustmentMade if you have made adjustments to the search terms.</para>
        /// <para>Return XWF::Ordinary::XT_PrepareSearch_NoAdjustmentMade if not.</para>
        /// <para>Return XWF::Ordinary::XT_PrepareSearch_Abort if you are not happy with the current settings at all and want the X-Tension to be unselected.</para>
        /// </returns>
        static LONG PrepareSearch(struct XWF::Ordinary::PrepareSearchInfo* pPSInfo, struct XWF::Search::CodePages* CPages)
        {
            JCS::Logging::Log(std::format(L"Running Type: {}", JCS::XWUtils::XTensionOperationTypeToWString(XWF::Ordinary::XT_Action_PrepareSimultaneousSearch)));

            return XWF::Ordinary::XT_PrepareSearch_NoAdjustmentMade;
        }

        /// <summary>
        /// ProcessSearchHit
        /// 
        /// This function will be called for each search hit when it is found (or in a future version
        /// of X-Ways Forensics perhaps later if selected by the user in a search hit list).
        /// 
        /// This function is not called if the search was initiated by the X-Tension itself (via XWF_Search).
        /// 
        /// If you call XWF_SelectVolumeSnapshot() while responding to a call to XT_ProcessSearchHit(),
        /// you have to call it again to undo the change before returning control.
        /// </summary>
        /// <param name="info">Information about the search hit.</param>
        /// <returns>
        /// <para>Return XWF::Ordinary::XT_ProcessSearchHit_NoFurtherAction to do no further action.</para>
        /// <para>Return XWF::Ordinary::XT_ProcessSearchHit_AbortSearch if you want X-Ways Forensics to abort the search.</para>
        /// <para>Return XWF::Ordinary::XT_ProcessSearchHit_StopCalling if you want X-Ways Forensics to stop calling you.</para>
        /// </returns>
        static LONG ProcessSearchHit(XWF::Search::SearchHitInfo* info)
        {
            Models::SearchHitInfo searchHitInfo = Models::SearchHitInfo(info, volume, readPrePostCount);
            searchHitInfo.DiscardResult(percentageRequired);
            return XWF::Ordinary::XT_ProcessSearchHit_NoFurtherAction;
        }
    };
}
