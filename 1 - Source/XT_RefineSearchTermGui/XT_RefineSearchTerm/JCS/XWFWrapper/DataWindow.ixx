module;

#include <Windows.h>

export module DataWindow;

import Utils;
import XTension;
import std;

/// <summary>
/// Data Window Functions
/// </summary>
export namespace JCS::XWFWrapper::DataWindow
{
	/// <summary>
	/// Available in v19.9 SR-7 and later. Retrieves the handle of a window related to a data window, so that you can use it as a parameter in Windows API functions. The possibilities are endless. You could send any kind of message to a window, redraw it, take a screenshot of it, simulate a mouse click, etc. For example, to refresh the contents of a window, you can call the Windows API function InvalidateRect(..., NULL, FALSE).
	/// 
	/// Not all related windows always exist.The function returns 0 for an unavailable window.
	/// </summary>
	/// <param name="nWndNo"> 	
	/// Available in v19.9 SR - 7 and later.Retrieves the handle of a window related to a data window, so that you can use it as a parameter in Windows API functions.The possibilities are endless.You could send any kind of message to a window, redraw it, take a screenshot of it, simulate a mouse click, etc.For example, to refresh the contents of a window, you can call the Windows API function InvalidateRect(..., NULL, FALSE).
	/// 
	/// Not all related windows always exist.The function returns 0 for an unavailable window.
	/// 
	/// nWndNo: The 1 - based number of the data window, for example as retrieved using XWF_GetEvObjProp().In v20.3 SR - 13, v20.4 SR - 9, v20.5 SR - 6, v20.6 SR - 5 and later you may specify 0 to target the active data window(the one in the foreground)
	/// </param>
	/// <param name="nWndIndex">nWndIndex: Identifies the exact window that you are interested in.</param>
	/// <returns></returns>
	std::optional<HWND> XWF_GetWindow(WORD nWndNo, WORD nWndIndex)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::DataWindow::XWF_GetWindow, L"XWF_GetWindow"))
		{
			return std::nullopt;
		}

		return XWF::DataWindow::XWF_GetWindow(nWndNo, nWndIndex);
	}
	/// <summary>
	/// Available in v20.3 and later. Retrieves the title of a particular column in the directory browser. The title depends on the currently active language in the GUI of the application and other factors. Returns true if the requested column exist, false if not. You can call this function repeatedly, starting with nColIndex == 0, ideally with nWndNo == 65535, to determine whether the column that you need still exists in the active version or what column index it has. 
	/// </summary>
	/// <param name="nWndNo">
	/// nWndNo: The 1-based number of the data window for which you wish to retrieve a column title, for example as retrieved using XWF_GetEvObjProp(). Depending on whether the data window shows an event list or not, the first few columns have different names. Depending on the file system and depending on what kind of hash values have been computed, other columns may have variable names. You may specify 0 to retrieve a language-specific column title that just depends on the currently active volume snapshot, if one is active, or 65535 for a standardized column title in English that does not depend on any window or volume snapshot.
	/// </param>
	/// <param name="nColIndex">
	/// nColIndex: Identifies the exact column that you are interested in. These identifiers are constant within a given version of the software and usually constant over many versions, but might change in future versions. They are based on the order of columns that you see in the application by default, if you do not change it in the GUI. E.g. in v20.3:
	/// 4: Name
	/// 5 : Existent
	/// 6 : Description
	/// 7 : Ext.
	/// 8 : Type
	/// ...
	/// 27 : Attr.
	/// ...
	/// 44 : File count
	/// ...
	/// 57 : Metadata
	/// ...
	/// </param>
	/// <param name="lpBuffer">
	/// lpBuffer: Pointer to your buffer, which should be able to accommodate at least 127 Unicode characters plus a terminating null.
	/// </param>
	/// <returns></returns>
	std::optional<BOOL> XWF_GetColumnTitle(WORD nWndNo, WORD nColIndex, LPWSTR lpBuffer)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::DataWindow::XWF_GetColumnTitle, L"XWF_GetColumnTitle"))
		{
			return std::nullopt;
		}

		return XWF::DataWindow::XWF_GetColumnTitle(nWndNo, nColIndex, lpBuffer);
	}
}
