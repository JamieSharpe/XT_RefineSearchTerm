module;

#include <Windows.h>
#include <shobjidl.h>
#include <shlobj_core.h>
#include <Richedit.h>
#include "GUI/resource.h"

export module GUI;

import std;
import Logging;
import Build;
import Configuration;
import Utils;

/// <summary>
/// Main GUI components for the X-Tension.
/// 
/// Definitions:
///		IDC_* : Used for control IDs (e.g., buttons, edit boxes, static texts).
///		IDD_* : Used for dialog IDs.
///		IDM_* : Used for menu command IDs.
///		IDR_* : Used for resource IDs (like icons, bitmaps, etc.).
/// </summary>
namespace GUI::GUI_Main
{
	std::wstring printablePercentRequired = L"";
	std::wstring hitContextLength = L"";
	std::wstring searchTermRenameSuffix = L"";
	int printablePercentRequiredSpinValue = 0;
	int hitContextLengthSpinValue = 0;

	/// Declarations for the help dialog procedure and event handlers.
	INT_PTR CALLBACK HelpDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	/// Declarations for event handlers.
	void IDD_HELP_DIALOG_Initialised(HWND hDlg);
	void IDD_HELP_DIALOG_Closed(HWND hDlg);
	void IDD_HELP_DIALOG_Destroyed(HWND hDlg);
	void IDC_Btn_OK_Clicked(HWND hDlg);
	/// Declarations for the main dialog procedure and event handlers.
	INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	/// Declarations for event handlers.
	void IDD_MAIN_DIALOG_Initialised(HWND hDlg);
	void IDD_MAIN_DIALOG_Closed(HWND hDlg);
	void IDD_MAIN_DIALOG_Destroyed(HWND hDlg);
	void IDC_Btn_FilePathSelection_Clicked(HWND hDlg);
	void IDC_Btn_FolderPathSelection_Clicked(HWND hDlg);
	void IDC_Btn_Process_Clicked(HWND hDlg);
	/// GUI functions for other operations.
	void ResetGUI(HWND hDlg);
	void RefreshLocalVariables(HWND hDlg);
	void ValidateGUI(HWND hDlg);
	void SaveToConfiguration(HWND hDlg);
	/// Other declarations.
	std::wstring ShowFolderDialog(HWND owner);
	std::wstring ShowFileDialog(HWND owner);
	std::wstring GetTextFromTextbox(HWND hDlg, long ID_Control);
	bool IDC_Button_Is_Clicked(long ID_Control, WPARAM wParam);

	/// <summary>
	/// Opens a main GUI window for the X-Tension.
	/// </summary>
	export void CreateMainGUIWindow()
	{
		JCS::Logging::Log("Opening Main Window.", JCS::Logging::LogLevel::Trace);

		DialogBox(Build::BuildInfo::XW_HANDLEMain, MAKEINTRESOURCE(IDD_MAIN_DIALOG), nullptr, MainDialogProc);

		JCS::Logging::Log("Terminated Main Window.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// Opens a help GUI window for the X-Tension.
	/// </summary>
	export void CreateHelpGUIWindow()
	{
		JCS::Logging::Log("Opening Help Window.", JCS::Logging::LogLevel::Trace);

		// Need to manually load the DLL for RichEdit controls to work.
		// See https://stackoverflow.com/questions/85427/rich-edit-control-in-raw-win32
		HMODULE hLib_RichTextEdit2 = LoadLibrary(L"riched20.dll");

		DialogBox(Build::BuildInfo::XW_HANDLEMain, MAKEINTRESOURCE(IDD_HELP_DIALOG), nullptr, HelpDialogProc);

		FreeLibrary(hLib_RichTextEdit2);

		JCS::Logging::Log("Terminated Help Window.", JCS::Logging::LogLevel::Trace);
	}

#pragma region MainGUIEventHandlers
	/// <summary>
	/// Main Dialog Message Event Loop
	/// </summary>
	/// <param name="hDlg"></param>
	/// <param name="message"></param>
	/// <param name="wParam"></param>
	/// <param name="lParam"></param>
	/// <returns></returns>
	INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_INITDIALOG:
				IDD_MAIN_DIALOG_Initialised(hDlg);
				return TRUE;
				break;
			case WM_DESTROY:
				IDD_MAIN_DIALOG_Destroyed(hDlg);
				return TRUE;
				break;
			case WM_CLOSE:
				IDD_MAIN_DIALOG_Closed(hDlg);
				EndDialog(hDlg, 0);
				return TRUE;
				break;
			case WM_COMMAND:
				RefreshLocalVariables(hDlg);
				if (IDC_Button_Is_Clicked(IDC_Btn_Process, wParam))
				{
					IDC_Btn_Process_Clicked(hDlg);
					return TRUE;
				}
				ValidateGUI(hDlg);
				break;
			case EN_UPDATE:
				/// RefreshLocalVariables(hDlg);
				/// ValidateGUI(hDlg);
				break;
		}
		return FALSE;
	}

	/// <summary>
	/// The dialog has initialised, contiue with our own initialisation.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_MAIN_DIALOG_Initialised(HWND hDlg)
	{
		JCS::Logging::Log("Main dialog - Initialising.", JCS::Logging::LogLevel::Trace);

		SetWindowText(hDlg, Build::BuildInfo::appTitle.c_str());

		/// Set printable text percentage range for the UI:
		/// 0-100 for the spin wheel, and 3 characters max in the text box.
		int printablePercentageMinRange = 0;
		int printablePercentageMaxRange = 100;

		HWND h_PrintablePercentRequired_SpinCtrl = GetDlgItem(hDlg, IDC_Spn_PrintablePercentRequired);
		SendMessage(h_PrintablePercentRequired_SpinCtrl, UDM_SETRANGE, 0, MAKELPARAM(printablePercentageMaxRange, printablePercentageMinRange));

		int printablePercentageMaxCharacterInput = 3;

		HWND h_PrintablePercentRequired_TextCtrl = GetDlgItem(hDlg, IDC_Tb_PrintablePercentRequired);
		SendMessage(h_PrintablePercentRequired_TextCtrl, EM_LIMITTEXT, printablePercentageMaxCharacterInput, 0);

		/// Set printable hit context range for the UI:
		/// 0-100 for the spin wheel, and 3 characters max in the text box.
		int hitContextLengthMinRange = 0;
		int hitContextLengthMaxRange = 100;

		HWND h_HitContextLength_SpinCtrl = GetDlgItem(hDlg, IDC_Spn_HitContextLength);
		SendMessage(h_HitContextLength_SpinCtrl, UDM_SETRANGE, 0, MAKELPARAM(hitContextLengthMaxRange, hitContextLengthMinRange));

		int hitContextLengthMaxCharacterInput = 3;

		HWND h_HitContextLength_TextCtrl = GetDlgItem(hDlg, IDC_Tb_HitContextLength);
		SendMessage(h_HitContextLength_TextCtrl, EM_LIMITTEXT, hitContextLengthMaxCharacterInput, 0);

		/// Set the max limit for the search term rename suffix text box.
		int searchTermRenameSuffixMaxCharacterInput = 30;

		HWND h_SearchTermRenameSuffix_TextCtrl = GetDlgItem(hDlg, IDC_Tb_SearchTermRenameSuffix);
		SendMessage(h_SearchTermRenameSuffix_TextCtrl, EM_LIMITTEXT, searchTermRenameSuffixMaxCharacterInput, 0);

		JCS::Logging::Log("Setting initial values.", JCS::Logging::LogLevel::Trace);
		ResetGUI(hDlg);

		JCS::Logging::Log("Main dialog - Initialised.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// The dialog has been closed, this runs before the dialog is destroyed.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_MAIN_DIALOG_Closed(HWND hDlg)
	{
		SaveToConfiguration(hDlg);
		JCS::Logging::Log("Main dialog closed.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// The dialog has been destroyed, this runs after the dialog is closed.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_MAIN_DIALOG_Destroyed(HWND hDlg)
	{
		JCS::Logging::Log("Main dialog destroyed.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// Button Process clicked event handler.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDC_Btn_Process_Clicked(HWND hDlg)
	{
		JCS::Logging::Log("Process button clicked.", JCS::Logging::LogLevel::Trace);

		JCS::Logging::Log(std::format(L"Printable Percentage Required: {}", printablePercentRequired), JCS::Logging::LogLevel::Trace);
		JCS::Logging::Log(std::format(L"Hit Context Length: {}", hitContextLength), JCS::Logging::LogLevel::Trace);
		JCS::Logging::Log(std::format(L"Search Term Rename Suffix: {}", searchTermRenameSuffix), JCS::Logging::LogLevel::Trace);

		/// Run close dialog commands.
		IDD_MAIN_DIALOG_Closed(hDlg);
		EndDialog(hDlg, 0);
	}
#pragma endregion MainGUIEventHandlers

#pragma region HelpGUIEventHandlers
	/// <summary>
	/// Help Dialog Message Event Loop
	/// </summary>
	/// <param name="hDlg"></param>
	/// <param name="message"></param>
	/// <param name="wParam"></param>
	/// <param name="lParam"></param>
	/// <returns></returns>
	INT_PTR CALLBACK HelpDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_INITDIALOG:
				IDD_HELP_DIALOG_Initialised(hDlg);
				return TRUE;
				break;
			case WM_DESTROY:
				IDD_HELP_DIALOG_Destroyed(hDlg);
				return TRUE;
				break;
			case WM_CLOSE:
				IDD_HELP_DIALOG_Closed(hDlg);
				EndDialog(hDlg, 0);
				return TRUE;
				break;
			case WM_COMMAND:
				if (IDC_Button_Is_Clicked(IDC_Btn_OK, wParam))
				{
					IDC_Btn_OK_Clicked(hDlg);
					return TRUE;
				}
				break;
			case EN_UPDATE:
				break;
		}
		return FALSE;
	}

	/// <summary>
	/// The dialog has initialised, contiue with our own initialisation.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_HELP_DIALOG_Initialised(HWND hDlg)
	{
		JCS::Logging::Log("Help dialog - Initialising.", JCS::Logging::LogLevel::Trace);

		/// Set the help text.
		//auto helpTextW = JCS::Utils::ReadFileToWString(L"./Resources/Help.rtf");
		auto helpTextW = JCS::Utils::GetHelpText();
		auto helpText = JCS::Utils::ws2s(helpTextW);

		SETTEXTEX setTextSettings = {};
		setTextSettings.flags = ST_DEFAULT;// | ST_NEWCHARS | ST_UNICODE;
		setTextSettings.codepage = 1200;

		HWND h_Help_RichTextCtrl = GetDlgItem(hDlg, IDC_Rtb_Help);
		SendMessage(h_Help_RichTextCtrl, EM_SETTEXTEX, (WPARAM)&setTextSettings, (LPARAM)helpText.c_str());
	}

	/// <summary>
	/// The dialog has been closed, this runs before the dialog is destroyed.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_HELP_DIALOG_Closed(HWND hDlg)
	{
		JCS::Logging::Log("Help dialog closed.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// The dialog has been destroyed, this runs after the dialog is closed.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_HELP_DIALOG_Destroyed(HWND hDlg)
	{
		JCS::Logging::Log("Help dialog destroyed.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// Button Process clicked event handler.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDC_Btn_OK_Clicked(HWND hDlg)
	{
		JCS::Logging::Log("OK button clicked.", JCS::Logging::LogLevel::Trace);

		/// Run close dialog commands.
		IDD_HELP_DIALOG_Closed(hDlg);
		EndDialog(hDlg, 0);
	}
#pragma endregion HelpGUIEventHandlers

#pragma region GUIFunctions
	/// <summary>
	/// Resets the GUI controls to their default state.
	/// </summary>
	/// <param name="hDlg">Handle to the dialog box whose controls will be reset.</param>
	void ResetGUI(HWND hDlg)
	{
		JCS::Logging::Log("Resetting GUI to default state.", JCS::Logging::LogLevel::Trace);

		/// Printable percentage required.
		
		int printablePercentageRequiredInitialSpinValue = static_cast<int>(Models::Configuration::printablePercentRequired);
		std::wstring printablePercentageRequiredSpinValueStr = std::to_wstring(printablePercentageRequiredInitialSpinValue);
		JCS::Logging::Log(std::format(L"Printable percentage: {}", printablePercentageRequiredSpinValueStr), JCS::Logging::LogLevel::Trace);
		SetDlgItemText(hDlg, IDC_Tb_PrintablePercentRequired, printablePercentageRequiredSpinValueStr.c_str());

		/// Hit context length.
		int hitContextInitialSpinValue = static_cast<int>(Models::Configuration::hitContextLength);
		std::wstring HitContextLengthSpinValueStr = std::to_wstring(hitContextInitialSpinValue);
		JCS::Logging::Log(std::format(L"Hit context: {}", HitContextLengthSpinValueStr), JCS::Logging::LogLevel::Trace);
		SetDlgItemText(hDlg, IDC_Tb_HitContextLength, HitContextLengthSpinValueStr.c_str());

		/// Search Term Rename Suffix
		JCS::Logging::Log(std::format(L"Search Term Rename Suffix: {}", HitContextLengthSpinValueStr), JCS::Logging::LogLevel::Trace);
		SetDlgItemText(hDlg, IDC_Tb_SearchTermRenameSuffix, Models::Configuration::searchTermRenameSuffix.c_str());

		JCS::Logging::Log("GUI reset to default state.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// Updates local variables by retrieving data from GUI.
	/// 
	/// This is so if the user has changed the data in the GUI, we can update our local variables accordingly.
	/// </summary>
	/// <param name="hDlg">Handle to the dialog box containing the data.</param>
	void RefreshLocalVariables(HWND hDlg)
	{
		JCS::Logging::Log("Refreshing local variables from GUI.", JCS::Logging::LogLevel::Trace);

		printablePercentRequired = GetTextFromTextbox(hDlg, IDC_Tb_PrintablePercentRequired);
		HWND h_PrintablePercentRequired_SpinCtrl = GetDlgItem(hDlg, IDC_Spn_PrintablePercentRequired);
		if (SendMessage(h_PrintablePercentRequired_SpinCtrl, UDM_GETPOS, 0, 0) != -1)
		{
			printablePercentRequiredSpinValue = static_cast<int>(SendMessage(h_PrintablePercentRequired_SpinCtrl, UDM_GETPOS, 0, 0));
		}

		hitContextLength = GetTextFromTextbox(hDlg, IDC_Tb_HitContextLength);
		HWND h_HitContextLength_SpinCtrl = GetDlgItem(hDlg, IDC_Spn_HitContextLength);
		if (SendMessage(h_HitContextLength_SpinCtrl, UDM_GETPOS, 0, 0) != -1)
		{
			hitContextLengthSpinValue = static_cast<int>(SendMessage(h_HitContextLength_SpinCtrl, UDM_GETPOS, 0, 0));
		}

		searchTermRenameSuffix = GetTextFromTextbox(hDlg, IDC_Tb_SearchTermRenameSuffix);
		
		JCS::Logging::Log("Local variables refreshed from GUI.", JCS::Logging::LogLevel::Trace);
	}

	/// <summary>
	/// Validates the state of GUI controls in a dialog window.
	/// Set controls to valid/invalid / enabled/disabled state based on the validation rules.
	/// </summary>
	/// <param name="hDlg">Handle to the dialog window whose controls are being validated.</param>
	void ValidateGUI(HWND hDlg)
	{
		JCS::Logging::Log("Validating GUI controls.", JCS::Logging::LogLevel::Trace);

		/// Validate the printable percentage required.
		if (printablePercentRequiredSpinValue > 100)
		{
			JCS::Logging::Log(std::format(L"Spin value out of range: {}, setting to 100.", printablePercentRequiredSpinValue), JCS::Logging::LogLevel::Trace);
			SetDlgItemText(hDlg, IDC_Tb_PrintablePercentRequired, L"100");
		}
		else if (printablePercentRequiredSpinValue < 0)
		{
			JCS::Logging::Log(std::format(L"Spin value out of range: {}, setting to 0.", printablePercentRequiredSpinValue), JCS::Logging::LogLevel::Trace);
			SetDlgItemText(hDlg, IDC_Tb_PrintablePercentRequired, L"0");
		}

		/// Validate the hit context length.
		if (hitContextLengthSpinValue > 100)
		{
			JCS::Logging::Log(std::format(L"Spin value out of range: {}, setting to 100.", hitContextLengthSpinValue), JCS::Logging::LogLevel::Trace);
			SetDlgItemText(hDlg, IDC_Tb_HitContextLength, L"100");
		}
		else if (printablePercentRequiredSpinValue < 0)
		{
			JCS::Logging::Log(std::format(L"Spin value out of range: {}, setting to 0.", hitContextLengthSpinValue), JCS::Logging::LogLevel::Trace);
			SetDlgItemText(hDlg, IDC_Tb_HitContextLength, L"0");
		}

		/// Check data is provided.
		if (printablePercentRequired.empty() || hitContextLength.empty())
		{
			JCS::Logging::Log(std::format(L"Required values are empty."), JCS::Logging::LogLevel::Warning);
			EnableWindow(GetDlgItem(hDlg, IDC_Btn_Process), FALSE);
		}
		else
		{
			EnableWindow(GetDlgItem(hDlg, IDC_Btn_Process), TRUE);
		}

		JCS::Logging::Log("GUI controls validated successfully.", JCS::Logging::LogLevel::Trace);
	}
	/// <summary>
	/// Save the configuration provided by the user in the GUI to the configuration model.
	/// Try to use the GUI elements as they may have changed in real time by the user.
	/// </summary>
	/// <param name="hDlg"></param>
	void SaveToConfiguration(HWND hDlg)
	{
		JCS::Logging::Log("Saving configuration from GUI.", JCS::Logging::LogLevel::Trace);

		Models::Configuration::searchTermRenameSuffix = searchTermRenameSuffix;
		Models::Configuration::hitContextLength = hitContextLengthSpinValue;
		Models::Configuration::printablePercentRequired = static_cast<double>(printablePercentRequiredSpinValue);

		JCS::Logging::Log("Saved configuration from GUI.", JCS::Logging::LogLevel::Trace);
	}
#pragma endregion GUIFunctions

#pragma region FileAndFolderBrowserDialog
	/// <summary>
	/// Folder Selection dialog.
	/// </summary>
	/// <param name="owner"></param>
	/// <returns></returns>
	std::wstring ShowFolderDialog(HWND owner = nullptr)
    {
        std::wstring folderPath;
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (!SUCCEEDED(hr))
		{
			return folderPath;
		}
        
        IFileDialog* pFileDialog = nullptr;
        hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
		if (!SUCCEEDED(hr))
		{
			return folderPath;
		}

        DWORD options;
        pFileDialog->GetOptions(&options);
        pFileDialog->SetOptions(options | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);

        if (SUCCEEDED(pFileDialog->Show(owner)))
        {
            IShellItem* pItem = nullptr;
            if (SUCCEEDED(pFileDialog->GetResult(&pItem)))
            {
                PWSTR pszFilePath = nullptr;
                if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath)))
                {
                    folderPath = pszFilePath;
                    CoTaskMemFree(pszFilePath);
                }
                pItem->Release();
            }
        }
        pFileDialog->Release();
        
        CoUninitialize();
        
        return folderPath;
    }

	/// <summary>
	/// File Selection dialog.
	/// </summary>
	/// <param name="owner"></param>
	/// <returns>Selected file path or empty string if canceled.</returns>
	std::wstring ShowFileDialog(HWND owner = nullptr)
	{
		std::wstring filePath;
		HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (!SUCCEEDED(hr))
		{
			return filePath;
		}

		IFileDialog* pFileDialog = nullptr;
		hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
		if (!SUCCEEDED(hr))
		{
			return filePath;
		}

		DWORD options;
		pFileDialog->GetOptions(&options);
		// No FOS_PICKFOLDERS, so it will select files
		pFileDialog->SetOptions(options | FOS_FORCEFILESYSTEM);

		if (SUCCEEDED(pFileDialog->Show(owner)))
		{
			IShellItem* pItem = nullptr;
			if (SUCCEEDED(pFileDialog->GetResult(&pItem)))
			{
				PWSTR pszFilePath = nullptr;
				if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath)))
				{
					filePath = pszFilePath;
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
		pFileDialog->Release();
		
		CoUninitialize();
		
		return filePath;
	}
#pragma endregion FileAndFolderBrowserDialog

#pragma region GUIHelperFunctions
	/// <summary>
	/// Check if a button with a specific ID was clicked.
	/// </summary>
	/// <param name="ID_Control"></param>
	/// <param name="wParam"></param>
	/// <returns></returns>
	bool IDC_Button_Is_Clicked(long ID_Control, WPARAM wParam)
	{
		return (LOWORD(wParam) == ID_Control && HIWORD(wParam) == BN_CLICKED);
	}

	/// <summary>
	/// Helper function that gets text from a control.
	/// </summary>
	/// <param name="hDlg"></param>
	/// <param name="ID_Control"></param>
	/// <returns></returns>
	std::wstring GetTextFromTextbox(HWND hDlg, long ID_Control)
	{
		JCS::Logging::Log("Getting text from textbox control.", JCS::Logging::LogLevel::Trace);

		std::wstring text = L"";

		HWND hEdit = GetDlgItem(hDlg, ID_Control);
		if (!hEdit)
		{
			JCS::Logging::Log("Failed to get handle to textbox.", JCS::Logging::LogLevel::Trace);
			return text;
		}

		int length = GetWindowTextLength(hEdit);

		if (length > 0)
		{
			std::wstring retreived_text(length, '\0');
			GetWindowText(hEdit, &retreived_text[0], length + 1);

			JCS::Logging::Log(std::format(L"Text from textbox: {}", retreived_text), JCS::Logging::LogLevel::Trace);

			text = retreived_text;
		}
		else
		{
			JCS::Logging::Log("Textbox is empty.", JCS::Logging::LogLevel::Trace);
			text = L"";
		}

		return text;
	}
#pragma endregion GUIHelperFunctions
}
