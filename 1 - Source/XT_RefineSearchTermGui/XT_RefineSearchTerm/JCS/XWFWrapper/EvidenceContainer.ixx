module;

#include <Windows.h>

export module EvidenceContainer;

import Utils;
import XTension;
import std;

/// <summary>
/// Evidence File Container Functions
/// </summary>
export namespace JCS::XWFWrapper::EvidenceContainer
{
	/// <summary>
	/// Available in v16.5 and later. Creates a new or opens an existing evidence file container (in its native, raw format) and returns a handle to it if successful (otherwise returns 0). Currently only 1 container can be open at a time for filling. If a container is open already when this function is called, that other container will be closed automatically.
	/// </summary>
	/// <param name="lpFileName"></param>
	/// <param name="nFlags"></param>
	/// <param name="pReserved"></param>
	/// <returns></returns>
	std::optional<HANDLE> XWF_CreateContainer(LPWSTR lpFileName, DWORD nFlags, LPVOID pReserved)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::EvidenceContainer::XWF_CreateContainer, L"XWF_CreateContainer"))
		{
			return std::nullopt;
		}

		return XWF::EvidenceContainer::XWF_CreateContainer(lpFileName, nFlags, pReserved);
	}

	/// <summary>
	/// Available in v16.5 and later. Copies a file to an evidence file container. Returns 0 if successful, otherwise an error code. If the error code is negative, you should not try to fill the container further. nStartOfs and nEndOfs should be -1 for any nMode where they are not used. 
	/// </summary>
	/// <param name="hContainer"></param>
	/// <param name="hItem"></param>
	/// <param name="nFlags"></param>
	/// <param name="nMode"></param>
	/// <param name="nStartOfs"></param>
	/// <param name="nEndOfs"></param>
	/// <param name="pReserved"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_CopyToContainer(HANDLE hContainer, HANDLE hItem, DWORD nFlags, DWORD nMode, INT64 nStartOfs, INT64 nEndOfs, LPVOID pReserved)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::EvidenceContainer::XWF_CopyToContainer, L"XWF_CopyToContainer"))
		{
			return std::nullopt;
		}

		return XWF::EvidenceContainer::XWF_CopyToContainer(hContainer, hItem, nFlags, nMode, nStartOfs, nEndOfs, pReserved);
	}

	/// <summary>
	/// Available in v16.5 and later. Closes a container. Returns 1 if successful.
	/// </summary>
	/// <param name="hContainer"></param>
	/// <param name="pReserved"></param>
	/// <returns></returns>
	std::optional<LONG> XWF_CloseContainer(HANDLE hContainer, LPVOID pReserved)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::EvidenceContainer::XWF_CloseContainer, L"XWF_CloseContainer"))
		{
			return std::nullopt;
		}

		return XWF::EvidenceContainer::XWF_CloseContainer(hContainer, pReserved);
	}
}
