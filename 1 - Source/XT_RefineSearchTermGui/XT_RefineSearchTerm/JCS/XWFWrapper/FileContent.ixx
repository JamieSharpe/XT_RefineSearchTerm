module;

#include <Windows.h>

export module FileContent;

import Utils;
import XTension;
import std;

/// <summary>
/// File Contents Functions
/// </summary>
export namespace JCS::XWFWrapper::FileContent
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="nItemID"></param>
	/// <param name="hItem"></param>
	std::optional<LPWSTR> XWF_GetMetadata(LONG nItemID, HANDLE hItem)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::FileContent::XWF_GetMetadata, L"XWF_GetMetadata"))
		{
			return std::nullopt;
		}

		return XWF::FileContent::XWF_GetMetadata(nItemID, hItem);
	}

	/// <summary>
	///  Available in v18.9 and later. Can extract extensive internal metadata of files of various types, exactly as seen in Details mode in X-Ways Forensics, typically much more than GetMetadata. Fills a memory buffer with either null-terminated UTF-16 plain text or null-terminated ASCII HTML code, and returns a pointer to it. You may parse the buffer to retrieve specific metadata that you need. The format may theoretically change from one version to the other. You must release the allocated memory by passing that pointer to XWF_ReleaseMem() when you do not need it any more. If no metadata is extracted, the return value is NULL instead.
	/// 
	/// Unlike XWF_GetMetadata, this function is thread - safe.Unlike XWF_GetExtractedMetadata, the file must have been opened with XWF_OpenItem because this function reads from the file contents, not from data stored in the volume snapshot.The metadata is taken from the very file that contains it, for example in the case of zip - style Office documents from the XML files if you specify such an XML file as hItem.
	/// </summary>
	/// <param name="hItem"></param>
	/// <param name="lpnFlags">
	/// lpnFlags points to flags for input and output. The only currently defined input flag is 0x01. It tells X-Ways Forensics to extract only a subset of the available metadata, as shown in the software in the Metadata column. The resulting buffer currently contains always UTF-16 plain text. If the flag is not set, the complete metadata as seen in Details mode is extracted. The resulting buffer can be of either above-mentioned formats.
	/// The only currently defined output flag is 0x01 (indicating, if set, that the resulting buffer is HTML - formatted ASCII instead of UTF - 16 plain text).If any of the 8 highest bits are set, you must not touch the resulting buffer, just release it with XWF_ReleaseMem().The output flags are valid only if the function was successful, i.e. if it has returned a pointer.
	/// </param>
	std::optional<LPVOID> XWF_GetMetadataEx(HANDLE hItem, PDWORD lpnFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::FileContent::XWF_GetMetadataEx, L"XWF_GetMetadataEx"))
		{
			return std::nullopt;
		}

		return XWF::FileContent::XWF_GetMetadataEx(hItem, lpnFlags);
	}

	/// <summary>
	/// Available in v20.3 and later. Prepares X-Ways Forensics for calls of XWF_GetText(), which may be necessary depending on whether similar functionality has already been used in the GUI during the current session or not. Does not override the user's decision to not use the viewer component or OCR in general. 
	/// 
	/// This function returns flags. If no flag in the result is set, that means you did not request text decoding capability or text decoding capability is not available, and OCR is not active either.
	/// 0x01: text decoding capability was requested and is available
	/// 0x02 : extended text decoding capability is available
	/// 0x04 : dates and number stored in spreadsheets in binary are converted to text as part of text decoding
	/// 0x10 : OCR capability is active
	/// </summary>
	/// <param name="nFlags">nFlags: 0x01 means that text decoding should be prepared. You don't need to specify this flag if you are interested in only OCR.</param>
	/// <param name="lpLangs>pLangs: Optional. If not NULL, points to a null-terminated ANSI string that identifies the languages to optimize OCR for, and this will override the configuration in the installation. The language identifiers can be seen in the filenames of *.traineddata files of Tesseract (list). You may concatenate multiple language identifiers with a + sign as long as the length of the result does not exceed 15 characters, e.g. "eng+spa+ita" or "chi_sim+chi_tra". Perhaps later versions will accept longer strings. If lpLangs points to a buffer that starts with a 0x00 character, then your buffer will receive the current language settings. The buffer should be 64 bytes in size at least. It will be null-terminated.</param>
	std::optional<DWORD> XWF_PrepareTextAccess(DWORD nFlags, LPSTR lpLangs)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::FileContent::XWF_PrepareTextAccess, L"XWF_PrepareTextAccess"))
		{
			return std::nullopt;
		}

		return XWF::FileContent::XWF_PrepareTextAccess(nFlags, lpLangs);
	}

	/// <summary>
	/// Available in v20.3 and later. Can extract pure text from files of various types, using means including OCR if OCR functionality is available in X-Ways Forensics (not WinHex Lab Edition), as known from the Text submode of Preview mode in the GUI. How spreadsheets are processed depends on the options in Options | Viewer Programs. If successful, the function returns a pointer to a buffer that you eventually need to release with XWF_ReleaseMem(). The buffer contains text usually in UTF-16 (for exceptions see below).
	/// </summary>
	/// <param name="hItem"> hItem identifies the file from which to extract text.</param>
	/// <param name="nFlags">
	/// nFlags:
	/// 0x01: decode text in files that have textual contents
	/// 0x02 : recognize text in files with graphical contents(OCR)
	/// 0x10 : retrieve text as 8 - bit ASCII or Latin 1 instead of UTF - 16 if no contained characters require UTF - 16
	/// 0x20 : retrieve text as 8 - bit ASCII or Latin 1 instead of UTF - 16 even if characters are lost that way.
	/// 
	///  0x10 and 0x20 have slightly different effects on different computers depending on which ANSI code page is active in the Windows system. If it's the 1252 Latin 1 code page, then Unicode characters from 0x81 to 0xFF are considered convertible. Otherwise such characters are considered not convertible, meaning no conversion from UTF-16 to ASCII takes place or - if forced - such characters are converted to a placeholder character, which is currenly an asterisk (*).
	/// 
	/// If neither the flag 0x01 nor 0x02 is specified, then no potentially time - consuming attempts will be made to extract text from the file, but if previously extracted text was stored(buffered) in the volume snapshot, that text is still retrieved, and very quickly so.If 0x01 and /or 0x02 are specified and if text was extracted and buffered previously, that "old" text is retrieved and no new extraction is attempted.If 0x01 and 0x02 are combined, that does not mean that both operations are attempted, e.g.in a PDF document.It means that depending on the file type at least one of the two operations are performed, and in currently available versions it means for example for PDF files that first decoding takes place, and if that no text is found that way, OCR will be attempted.In currently available versions the resulting text will never be a mix of both operations.
	/// </param>
	/// <param name="lpnResult"> lpnResult must point to an integer variable ("nResult") which will receive information about the outcome of the function:
	/// 
	/// >0 = success, flags as defined below
	/// 0 = no buffer available, no textual content found
	/// -1 = no buffer available, file seems encrypted
	/// -2 = no buffer available, action aborted
	/// -3 = no buffer available, error occurred
	/// 
	/// 0x01 = pointer to buffer with UTF - 16 returned
	/// 0x02 = pointer to buffer with 8 - bit ASCII / Latin 1 returned
	/// 0x10 = text derived through OCR</param>
	/// <param name="lpnBufUsedSize">lpnBufUsedSize may be NULL or point to a DWORD variable, if in case of a positive nResult you wish to know how many bytes in the buffer are considered in use.</param>
	/// <param name="lpnBufAllocSize">lpnBufAllocSize may be NULL or point to a DWORD variable, if in case of a positive nResult you wish to know how many bytes in the buffer are allocated. </param>   
	std::optional<LPVOID> XWF_GetText(HANDLE hItem, DWORD nFlags, INT* lpnResult, PDWORD lpnBufUsedSize, PDWORD lpnBufAllocSize)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::FileContent::XWF_GetText, L"XWF_GetText"))
		{
			return std::nullopt;
		}

		return XWF::FileContent::XWF_GetText(hItem, nFlags, lpnResult, lpnBufUsedSize, lpnBufAllocSize);
	}

	/// <summary>
	/// Available in v18.0 and later, not in WinHex Lab Edition. Provides a standardized true-color RGB raster image representation for any picture file type that is supported internally in X-Ways Forensics (e.g. JPEG, GIF, PNG, ...), with 24 bits per pixel. The result is a pointer to a memory buffer, or NULL if not successful (e.g. if not a supported file type variant or the file is too corrupt). The caller is responsible for releasing the allocated memory buffer when no longer needed, by calling the Windows API function VirtualFree, with parameters dwSize = 0 and dwFreeType = MEM_RELEASE.
	/// </summary>
	/// <param name="pRIInfo">Pointer to a raster image info struct.</param>
	std::optional<LPVOID> XWF_GetRasterImage(struct XWF::FileContent::RasterImageInfo* pRIInfo)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::FileContent::XWF_GetRasterImage, L"XWF_GetRasterImage"))
		{
			return std::nullopt;
		}

		return XWF::FileContent::XWF_GetRasterImage(pRIInfo);
	}
}
