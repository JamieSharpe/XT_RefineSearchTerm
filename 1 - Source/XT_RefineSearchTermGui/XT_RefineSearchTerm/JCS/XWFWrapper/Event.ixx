module;

#include <Windows.h>

export module Event;

import Utils;
import XTension;
import std;

/// <summary>
/// Event - Related Functions
/// </summary>
export namespace JCS::XWFWrapper::Event
{
	/// <summary>
	/// Available in v17.6 and later. Allows to add events to the internal event hit list of an evidence object. The internal event is loaded and accessible only if the evidence object is open. 
	/// </summary>
	/// <param name="pEvt"></param>
	/// <returns>Returns 1 if the event was successfully added, 2 if deliberately ignored, or 0 in case of failure to signal that the caller should stop adding more events.</returns>
	std::optional<LONG> XWF_AddEvent(struct XWF::Event::EventInfo* pEvt)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Event::XWF_AddEvent, L"XWF_AddEvent"))
		{
			return std::nullopt;
		}

		return XWF::Event::XWF_AddEvent(pEvt);
	}

	/// <summary>
	/// Available in v18.1 and later. Retrieves information about an event from the internal event hit list of an evidence object. The internal event is loaded and accessible only if the evidence object is open. The structure will be populated with values as described above, except where noted.
	/// </summary>
	/// <param name="nEventNo"></param>
	/// <param name="pEvt"></param>
	/// <returns>Returns MAXDWORD if unsuccessful, or otherwise the length of the description copied into the lpDescr buffer, in bytes. 0 indicates success as well as a description is not necessarily available or desired by the caller. </returns>
	std::optional<DWORD> XWF_GetEvent(DWORD nEventNo, struct XWF::Event::EventInfo* pEvt)
	{
		if (JCS::Utils::FunctionPointerIsNull(XWF::Event::XWF_GetEvent, L"XWF_GetEvent"))
		{
			return std::nullopt;
		}

		return XWF::Event::XWF_GetEvent(nEventNo, pEvt);
	}
}
