module;

#include <Windows.h>

export module Search;

import Utils;
import XTension;
import std;

/// <summary>
/// Search - Related Functions
/// </summary>
export namespace JCS::XWFWrapper::Search
{
	/// <summary>
	/// Available in v16.5 and later. Must only be called from XT_Prepare() or XT_Finalize(). Runs a simultaneous search for multiple search terms in the specified volume. The volume must be associated with an evidence object. Note that if this function is called as part of volume snapshot refinement, it can be called automatically for all selected evidence objects if the user applies the X-Tension to all selected evidence objects. Returns a negative value in case of an error.
	/// </summary>
	/// <param name="pSInfo"></param>
	/// <param name="pCPages"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_Search(struct XWF::Search::SearchInfo* pSInfo, struct XWF::Search::CodePages* pCPages)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_Search, L"XWF_Search"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_Search(pSInfo, pCPages);
	}

	/// <summary>
	/// Available in v17.7 and later. Retrieves a pointer to the null-terminated name of the search term with the specified ID, or NULL if no search term with that ID exists. You may set nSearchTermID to -1 to get the total number of search terms back (cast the pointer returned to integer). All search terms have consecutive IDs starting with 0. pReserved must be set to NULL. 
	/// </summary>
	/// <param name="nSearchTermID"></param>
	/// <param name="pReserved"></param>
	/// <returns></returns>
	std::optional<LPWSTR> XWF_GetSearchTerm(LONG nSearchTermID, LPVOID pReserved)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_GetSearchTerm, L"XWF_GetSearchTerm"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_GetSearchTerm(nSearchTermID, pReserved);
	}

	/// <summary>
	/// Available in v18.5 and later. Creates a new search term and returns its ID or (if flag 0x01 is specified) alternatively returns the ID of an existing search term with the search expression/keyword, if any. Returns -1 in case of an error. The maximum number of search terms in a case is currently 8,191 (since v18.5). Use this function if you wish to automatically categorize search hits (assign them to different search terms) while responding to calls of XT_ProcessSearchHit() or using XWF_SetSearchHit(). The null-terminated UTF-16 string pointed to by lpSearchTerm may be truncated. Currently, as of v20.3, up to 90 characters are supported.
	/// </summary>
	/// <param name="lpSearchTerm"></param>
	/// <param name="nUsageFlags"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_AddSearchTerm(LPWSTR lpSearchTerm, DWORD nUsageFlags)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_AddSearchTerm, L"XWF_AddSearchTerm"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_AddSearchTerm(lpSearchTerm, nUsageFlags);
	}

	/// <summary>
	///  Available in v20.0 and later.
	/// 
	/// Set nProperty to 0 to delete the specified search term and all its search hits in all evidence objects.That is more efficient than deleting the search hits one by one.If nSearchTermID is - 1, that deletes all search terms and all their search hits.pFlags should be set to NULL and is currently unused.The return value of the function is 1 for presumed success, 0 for failure. 
	/// 
	/// Set nProperty to 1 to manage the flags that define the properties of the search terms whose ID you specify.You can retrieve these flags through the function return value(if pValue is NULL) or set those flags(if pValue is not NULL, but please know what you are doing).If you set the flags, a return value of 1 indicates success, 0 indicates failure.
	/// 
	/// Set nProperty to 2 to rename the search term, e.g. assign a more user-friendly name to a complicated regular expression. In that case pValue must point to a null-terminated UTF-16 string. Available in v20.3 and later. The null-terminated UTF-16 string pointed to by lpSearchTerm may be truncated in X-Ways Forensics. Currently, as of v20.3, up to 90 characters are supported. A return value of 1 indicates success, 0 indicates failure. 
	/// </summary>
	/// <param name="nSearchTermID"></param>
	/// <param name="nProperty"></param>
	/// <param name="pValue"></param>
	/// <returns></returns>
	std::optional<DWORD> XWF_ManageSearchTerm(LONG nSearchTermID, LONG nProperty, LPVOID pValue)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_ManageSearchTerm, L"XWF_ManageSearchTerm"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_ManageSearchTerm(nSearchTermID, nProperty, pValue);
	}

	/// <summary>
	/// Creates a new search hit. Not currently implemented. 
	/// </summary>
	/// <param name="pInfo"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_AddSearchHit(struct XWF::Search::SearchHitInfo* pInfo)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_AddSearchHit, L"XWF_AddSearchHit"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_AddSearchHit(pInfo);
	}

	/// <summary>
	/// Retrieves details about a search hit. Not currently implemented. 
	/// </summary>
	/// <param name="nSearchHitNo"></param>
	/// <param name="pInfo"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_GetSearchHit(DWORD nSearchHitNo, struct XWF::Search::SearchHitInfo* pInfo)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_GetSearchHit, L"XWF_GetSearchHit"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_GetSearchHit(nSearchHitNo, pInfo);
	}

	/// <summary>
	/// Changes details of a search hit. Not currently implemented. 
	/// </summary>
	/// <param name="nSearchHitNo"></param>
	/// <param name="pInfo"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_SetSearchHit(DWORD nSearchHitNo, struct XWF::Search::SearchHitInfo* pInfo)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Search::XWF_SetSearchHit, L"XWF_SetSearchHit"))
		{
			return std::nullopt;
		}

		return XWF::Search::XWF_SetSearchHit(nSearchHitNo, pInfo);
	}
}
