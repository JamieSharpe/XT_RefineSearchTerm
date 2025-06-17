module;

#include <Windows.h>
#include <shobjidl.h>
#include <shlobj_core.h>
#include "GUI/resource.h"

export module GUI;

import std;
import Logging;
import Build;
import Configuration;

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
	std::wstring filePath = L"";
	std::wstring folderPath = L"";
	std::wstring userInput = L"";
	int spinValue = 0;

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
	std::wstring ReadFileToWString(const std::wstring& filePath);

	/// <summary>
	/// Opens a main GUI window for the X-Tension.
	/// </summary>
	export void CreateMainGUIWindow()
	{
		JCS::Logging::Log("Opening Main Window.");

		DialogBox(Build::BuildInfo::XW_HANDLEMain, MAKEINTRESOURCE(IDD_MAIN_DIALOG), nullptr, MainDialogProc);

		JCS::Logging::Log("Terminated Main Window.");
	}

#pragma region GUIEventHandlers
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
				if (IDC_Button_Is_Clicked(IDC_Btn_FilePathSelection, wParam))
				{
					IDC_Btn_FilePathSelection_Clicked(hDlg);
					return TRUE;
				}
				if (IDC_Button_Is_Clicked(IDC_Btn_FolderPathSelection, wParam))
				{
					IDC_Btn_FolderPathSelection_Clicked(hDlg);
					return TRUE;
				}
				else if (IDC_Button_Is_Clicked(IDC_Btn_Process, wParam))
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
	/// The dialog has initialised.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_MAIN_DIALOG_Initialised(HWND hDlg)
	{
		JCS::Logging::Log("Main dialog initialized.");
		SetWindowText(hDlg, Build::BuildInfo::title.c_str());

		/// Set printable text percentage range for the UI:
		/// 0-100 for the spin wheel, and 3 characters max in the text box.
		int minRange = 0;
		int maxRange = 100;
		int maxCharacterInput = 3;

		HWND m_SpinCtrl = GetDlgItem(hDlg, IDC_Spn_SelectedFilePath);
		SendMessage(m_SpinCtrl, UDM_SETRANGE, 0, MAKELPARAM(maxRange, minRange));

		HWND m_TextCtrl = GetDlgItem(hDlg, IDC_Tb_SelectedFilePath);
		SendMessage(m_TextCtrl, EM_LIMITTEXT, maxCharacterInput, 0);

		/// Set the initial values for the GUI controls.
		std::wstring spinValueStr = std::to_wstring(static_cast<int>(Models::Configuration::printablePercentRequired));
		JCS::Logging::Log(std::format(L"Setting initial spin value: {}", spinValueStr), JCS::Logging::LogLevel::Debug);
		SetDlgItemText(hDlg, IDC_Tb_SelectedFilePath, spinValueStr.c_str());
	}

	/// <summary>
	/// The dialog has been closed, this runs before the dialog is destroyed.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_MAIN_DIALOG_Closed(HWND hDlg)
	{
		SaveToConfiguration(hDlg);
		JCS::Logging::Log("Main dialog closed.");
	}

	/// <summary>
	/// The dialog has been destroyed, this runs after the dialog is closed.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDD_MAIN_DIALOG_Destroyed(HWND hDlg)
	{
		JCS::Logging::Log("Main dialog destroyed.");
	}

	/// <summary>
	/// Button File Path Selection clicked event handler.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDC_Btn_FilePathSelection_Clicked(HWND hDlg)
	{
		JCS::Logging::Log("File path selection button clicked.");

		filePath = ShowFileDialog(hDlg);

		SetDlgItemText(hDlg, IDC_Tb_SelectedFilePath, filePath.c_str());

		JCS::Logging::Log(std::format(L"Selected path: {}", filePath), JCS::Logging::LogLevel::Info);
	}

	/// <summary>
	/// Button Folder Path Selection clicked event handler.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDC_Btn_FolderPathSelection_Clicked(HWND hDlg)
	{
		JCS::Logging::Log("Folder path selection button clicked.");

		folderPath = ShowFolderDialog(hDlg);

		SetDlgItemText(hDlg, IDC_Tb_SelectedFolderPath, folderPath.c_str());

		JCS::Logging::Log(std::format(L"Selected path: {}", filePath));
	}

	/// <summary>
	/// Button Process clicked event handler.
	/// </summary>
	/// <param name="hDlg"></param>
	void IDC_Btn_Process_Clicked(HWND hDlg)
	{
		JCS::Logging::Log("Process button clicked.");

		JCS::Logging::Log(std::format(L"Selected File Path: {}", filePath));
		JCS::Logging::Log(std::format(L"Selected Folder Path: {}", folderPath));
		JCS::Logging::Log(std::format(L"User Input: {}", userInput));

		std::wstring fileContent = ReadFileToWString(filePath);
		SetDlgItemText(hDlg, IDC_Tb_FileContent, fileContent.c_str());
	}
#pragma endregion GUIEventHandlers

#pragma region GUIFunctions
	/// <summary>
	/// Resets the GUI controls to their default (empty) state.
	/// </summary>
	/// <param name="hDlg">Handle to the dialog box whose controls will be reset.</param>
	void ResetGUI(HWND hDlg)
	{
		JCS::Logging::Log("Resetting GUI to default state.");

		SetDlgItemText(hDlg, IDC_Tb_SelectedFilePath, L"");
		SetDlgItemText(hDlg, IDC_Tb_SelectedFolderPath, L"");
		SetDlgItemText(hDlg, IDC_Tb_UserInput, L"");
		SetDlgItemText(hDlg, IDC_Tb_FileContent, L"");

		JCS::Logging::Log("GUI reset to default state.");
	}

	/// <summary>
	/// Updates local variables by retrieving data from GUI.
	/// 
	/// This is so if the user has changed the data in the GUI, we can update our local variables accordingly.
	/// </summary>
	/// <param name="hDlg">Handle to the dialog box containing the data.</param>
	void RefreshLocalVariables(HWND hDlg)
	{
		JCS::Logging::Log("Refreshing local variables from GUI.");

		filePath = GetTextFromTextbox(hDlg, IDC_Tb_SelectedFilePath);
		folderPath = GetTextFromTextbox(hDlg, IDC_Tb_SelectedFolderPath);
		userInput = GetTextFromTextbox(hDlg, IDC_Tb_UserInput);

		
		HWND m_SpinCtrl = GetDlgItem(hDlg, IDC_Spn_SelectedFilePath);
		if (SendMessage(m_SpinCtrl, UDM_GETPOS, 0, 0) != -1)
		{
			spinValue = static_cast<int>(SendMessage(m_SpinCtrl, UDM_GETPOS, 0, 0));
		}
		JCS::Logging::Log(std::format(L"Spin control value: {}", spinValue), JCS::Logging::LogLevel::Debug);

		JCS::Logging::Log("Local variables refreshed from GUI.");
	}

	/// <summary>
	/// Validates the state of GUI controls in a dialog window.
	/// Set controls to valid/invalid / enabled/disabled state based on the validation rules.
	/// </summary>
	/// <param name="hDlg">Handle to the dialog window whose controls are being validated.</param>
	void ValidateGUI(HWND hDlg)
	{
		JCS::Logging::Log("Validating GUI controls.");
		// Example validation: Ensure file path is not empty
		if (filePath.empty() || !std::filesystem::exists(filePath))
		{
			JCS::Logging::Log(std::format(L"The file path is empty or does not exists: {}", filePath), JCS::Logging::LogLevel::Warning);
			EnableWindow(GetDlgItem(hDlg, IDC_Btn_Process), FALSE);
		}
		else
		{
			EnableWindow(GetDlgItem(hDlg, IDC_Btn_Process), TRUE);
		}
		// Additional validations...

		if (spinValue > 100)
		{
			JCS::Logging::Log(std::format(L"Spin value out of range: {}, setting to 100.", spinValue), JCS::Logging::LogLevel::Debug);
			SetDlgItemText(hDlg, IDC_Tb_SelectedFilePath, L"100");
		}
		else if (spinValue < 0)
		{
			JCS::Logging::Log(std::format(L"Spin value out of range: {}, setting to 0.", spinValue), JCS::Logging::LogLevel::Debug);
			SetDlgItemText(hDlg, IDC_Tb_SelectedFilePath, L"0");
		}

		JCS::Logging::Log("GUI controls validated successfully.");
	}
	/// <summary>
	/// Save the configuration provided by the user in the GUI to the configuration model.
	/// Try to use the GUI elements as they may have changed in real time by the user.
	/// </summary>
	/// <param name="hDlg"></param>
	void SaveToConfiguration(HWND hDlg)
	{
		JCS::Logging::Log("Saving configuration from GUI.");

		Models::Configuration::selectedFilePath = filePath;
		Models::Configuration::selectedFolderPath = folderPath;
		Models::Configuration::userInput = userInput;
		Models::Configuration::printablePercentRequired = static_cast<double>(spinValue);

		JCS::Logging::Log("Saved configuration from GUI.");
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
			JCS::Logging::Log("Failed to get handle to textbox.", JCS::Logging::LogLevel::Error);
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

	/// <summary>
	/// Reads the entire content of a file and returns it as a wstring.
	/// </summary>
	/// <param name="filePath">The path to the file.</param>
	/// <returns>File content as wstring, or empty if error.</returns>
	std::wstring ReadFileToWString(const std::wstring& filePath)
	{
		// return L"";
		
		std::wifstream file(filePath, std::ios::binary);
		if (!file)
		{
			JCS::Logging::Log(std::format(L"Failed to open file: {}", filePath), JCS::Logging::LogLevel::Error);
			return L"";
		}

		std::wstringstream wss;
		wss << file.rdbuf();
		return wss.str();
	}
#pragma endregion GUIHelperFunctions
}
