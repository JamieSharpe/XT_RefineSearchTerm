module;

#include "JCS/XWFWrapper/XWFWrapper.h"
#include <Windows.h>

export module SearchHitInfo;

import std;
import XTension;
import Logging;
import Utils;
import ItemObject;
import VolumeObject;

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

        SearchHitInfo(XWF::Search::SearchHitInfo* info, std::shared_ptr<Models::VolumeObject> volume, int dataPrePostRead = 0)
        {
            this->info = info;
            this->ParentVolume = volume;
            this->dataPrePostRead = dataPrePostRead;
            Initialise();
        }

        void Initialise()
        {
            searchHitExcerpt = GetSearchHitExcerpt();

            CalculatePositiveChars();

            stringLengthWithoutSearchTerm = searchHitExcerpt.length() - info->nLength;

            printablePercentage = (double)positiveChars / (double)searchHitExcerpt.length();
            printablePercentage = printablePercentage * 100;
        }

        std::wstring GetSearchHitExcerpt()
        {
            std::unique_ptr<Models::ItemObject> item = std::make_unique<Models::ItemObject>(info->nItemID, ParentVolume);

            INT64 startOffsetBuffer = info->nRelOfs - dataPrePostRead;
            if (startOffsetBuffer < 0)
            {
                startOffsetBuffer = 0;
            }

            INT64 endOffsetBuffer = info->nRelOfs + info->nLength + dataPrePostRead;
            if (item->size && endOffsetBuffer > item->size.value())
            {
                endOffsetBuffer = item->size.value();
            }

            INT64 readSize = endOffsetBuffer - startOffsetBuffer;

            if (readSize < 0)
            {
                JCS::Logging::Log(std::format("Possibly found hit in file slack of Item ID: {}. Attempting to read may error", item->ID), JCS::Logging::LogLevel::Warning);
                endOffsetBuffer = info->nRelOfs + info->nLength + dataPrePostRead;
                readSize = endOffsetBuffer - startOffsetBuffer;
            }

            std::unique_ptr<char[]> readBytes = item->GetFileExcerpt(startOffsetBuffer, readSize);

            std::unique_ptr<char[]> readBytesNoNulls = std::make_unique<char[]>(readSize);

            for (int i = 0, j = 0; i < readSize; i++)
            {
                if (readBytes[i] != '\0')
                {
                    readBytesNoNulls[j] = readBytes[i];
                    j++;
                }
            }

            std::wstring convertedToString = JCS::Utils::b2ws(readBytesNoNulls.get(), info->nCodePage);

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
            JCS::Logging::Log(std::format(L"\tlpOptionalHitPtrDeRef: {}", JCS::Utils::LPWStrToWString((LPWSTR)info->lpOptionalHitPtr)));
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
        void DiscardResult(double percentageThreshold)
        {
            if (printablePercentage < percentageThreshold)
            {
                JCS::Logging::Log(std::format("Readable characters in excerpt did not meet the required percentage: {:.2f}/{}", printablePercentage, percentageThreshold), JCS::Logging::LogLevel::Debug);
                info->nFlags |= XWF::Search::XWF_SearchHitInfo_Flag_Deleted; // Discard the result.
            }
            else
            {
                JCS::Logging::Log(std::format("Readable characters in excerpt met the required percentage: {:.2f}/{}. Item added to search hits.", printablePercentage, percentageThreshold), JCS::Logging::LogLevel::Debug);
            }
        }
    };
}
