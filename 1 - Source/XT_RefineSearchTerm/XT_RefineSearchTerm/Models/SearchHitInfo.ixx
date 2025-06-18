module;

#include <Windows.h>

export module SearchHitInfo;

import Logging;
import Utils;
import ItemObject;
import VolumeObject;
import Configuration;
import Search;
import XTension;
import std;

namespace Models
{
	export class SearchHitInfo
	{
	private:
	public:
		XWF::Search::SearchHitInfo* info = nullptr;
		std::shared_ptr<Models::VolumeObject> ParentVolume;
		std::wstring searchHitExcerpt = std::wstring();
		double printablePercentage = 0;
		int positiveChars = 0;
		long long stringLengthWithoutSearchTerm = 0;
		int dataPrePostRead = 0;

		SearchHitInfo(XWF::Search::SearchHitInfo* info, std::shared_ptr<Models::VolumeObject> volume, int dataPrePostRead)
		{
			this->info = info;
			this->ParentVolume = volume;
			this->dataPrePostRead = dataPrePostRead;
			Initialise();
		}

		void Initialise()
		{
			searchHitExcerpt = GetSearchHitExcerpt().value_or(L"");

			CalculatePositiveChars();

			stringLengthWithoutSearchTerm = searchHitExcerpt.length() - info->nLength;

			printablePercentage = (double)positiveChars / (double)searchHitExcerpt.length();
			printablePercentage = printablePercentage * 100;
		}

		std::optional<std::wstring> GetSearchHitExcerpt()
		{
			std::unique_ptr<Models::ItemObject> item = std::make_unique<Models::ItemObject>(info->nItemID, ParentVolume);

			int multibyteMultiplier = 1;
			if (info->nCodePage == 1200 || info->nCodePage == 1201) // UTF-16 Little Endian or Big Endian
			{
				multibyteMultiplier = 2; // UTF-16 uses 2 bytes per character
			}

			int dataPrePostReadWithMultiplier = this->dataPrePostRead * multibyteMultiplier;

			INT64 startOffsetBuffer = info->nRelOfs - dataPrePostReadWithMultiplier;
			if (startOffsetBuffer < 0)
			{
				startOffsetBuffer = 0;
			}

			INT64 endOffsetBuffer = info->nRelOfs + info->nLength + dataPrePostReadWithMultiplier;
			std::optional<INT64> fileSizeWithSlack = item->GetFileSizeWithSlack();

			if (!fileSizeWithSlack)
			{
				return std::nullopt;
			}

			if (endOffsetBuffer > fileSizeWithSlack.value())
			{
				endOffsetBuffer = fileSizeWithSlack.value();
			}

			INT64 readSize = endOffsetBuffer - startOffsetBuffer;

			std::unique_ptr<char[]> readBytes = item->GetFileExcerpt(startOffsetBuffer, readSize);

			std::unique_ptr<char[]> readBytesNoNulls = std::make_unique<char[]>(readSize);

			std::wstring convertedToString;

			/// remove nulls it not UTF-16 Little Endian (1200) or UTF-16 Big Endian (1201)
			if (info->nCodePage != 1200 || info->nCodePage != 1201)
			{
				for (int i = 0, j = 0; i < readSize; i++)
				{
					if (readBytes[i] != '\0')
					{
						readBytesNoNulls[j] = readBytes[i];
						j++;
					}
				}

				JCS::Utils::b2ws(readBytesNoNulls.get(), info->nCodePage);
			}
			else
			{
				convertedToString = JCS::Utils::StringToWideString(readBytes.get());
			}

			// errors with 0x53 0x00 0x40 0x00

			return convertedToString;
		}

		void CalculatePositiveChars()
		{
			positiveChars = 0;
			for (WCHAR c : searchHitExcerpt)
			{
				if (((c >= 32) && (c <= 126)) || (c == 10) || (c == 13) || (c == 9))
				{
					positiveChars++;
				}
			}
		}

		void Log()
		{
			JCS::Logging::Log(L"Search Hit Info:");
			JCS::Logging::Log(std::format(L"\tnSize: {}", info->nSize));
			JCS::Logging::Log(std::format(L"\tnItemID: {}", info->nItemID));
			JCS::Logging::Log(std::format(L"\tnRelOfs: {}", info->nRelOfs));
			JCS::Logging::Log(std::format(L"\tnAbsOfs: {}", info->nAbsOfs));
			JCS::Logging::Log(std::format(L"\tlpOptionalHitPtr: {}", info->lpOptionalHitPtr));
			// The below commented line is not reliable. As the docs say, don't assume how many bytes before or after may be read. Use the searchHitExcerpt.
			//JCS::Logging::Log(std::format(L"\tlpOptionalHitPtrDeRef: {}", JCS::Utils::LPWStrToWString((LPWSTR)info->lpOptionalHitPtr)));
			JCS::Logging::Log(std::format(L"\tnSearchTermID: {}", info->nSearchTermID));
			JCS::Logging::Log(std::format(L"\tnLength: {}", info->nLength));
			JCS::Logging::Log(std::format(L"\tnCodePage: {}", info->nCodePage));
			JCS::Logging::Log(std::format(L"\tnFlags: {}", info->nFlags));
			JCS::Logging::Log(std::format(L"\thOptionalItemOrVolume: {}", info->hOptionalItemOrVolume));

			JCS::Logging::Log(std::format(L"\tFile Excerpt: {}", searchHitExcerpt));
			JCS::Logging::Log(std::format(L"\tPositive Chars: {}", positiveChars));
			JCS::Logging::Log(std::format(L"\tString Length no Search Term: {}", stringLengthWithoutSearchTerm));
			JCS::Logging::Log(std::format(L"\tPrintable Chars %: {}", printablePercentage));
		}

		/// <summary>
		/// Discard the result if the printable character percentage is less than the provided value.
		/// </summary>
		/// <param name="percentageThreshold"></param>
		void ProcessResult()
		{
			if (printablePercentage < Models::Configuration::printablePercentRequired)
			{
				JCS::Logging::Log(std::format("Readable characters in excerpt did not meet the required percentage: {:.2f}/{}", printablePercentage, Models::Configuration::printablePercentRequired), JCS::Logging::LogLevel::Trace);

				// Discard the result.
				info->nFlags |= XWF::Search::XWF_SearchHitInfo_Flag_Deleted;

				return;
			}

			JCS::Logging::Log(std::format("Readable characters in excerpt met the required percentage: {:.2f}/{}. Item added to search hits.", printablePercentage, Models::Configuration::printablePercentRequired), JCS::Logging::LogLevel::Trace);

			// Ensure the result is not marked as deleted.
			info->nFlags &= ~XWF::Search::XWF_SearchHitInfo_Flag_Deleted;

			// Get the current search term name and append the rename suffix if it does not already exist.
			std::optional<LPWSTR> pSearchTermName = JCS::XWFWrapper::Search::XWF_GetSearchTerm(info->nSearchTermID, nullptr);
			if (!pSearchTermName.has_value())
			{
				JCS::Logging::Log(L"Failed to retrieve search term name.", JCS::Logging::LogLevel::Error);
				return;
			}

			std::wstring searchTermName = JCS::Utils::LPWStrToWString(pSearchTermName.value());

			if (!searchTermName.ends_with(Models::Configuration::searchTermRenameSuffix))
			{
				searchTermName = std::format(L"{}{}", searchTermName, Models::Configuration::searchTermRenameSuffix);
				JCS::XWFWrapper::Search::XWF_ManageSearchTerm(info->nSearchTermID, XWF::Search::XWF_ManageSearchTerm_nProperty_Rename, searchTermName.data());
			}
		}
	};
}