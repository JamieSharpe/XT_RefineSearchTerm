module;

#include <Windows.h>
//#include <processenv.h>

export module CommandLineOptions;

import Utils;
import std;

namespace Models
{
    export class CommandLineOptions
    {
    private:
    public:
        std::wstring CLIArgs;

        std::wstring GetCLIArgs()
        {
            LPWSTR pCliArgs = GetCommandLine();

            std::wstring cliArgs = JCS::Utils::WCharPointerToWString(pCliArgs);

            this->CLIArgs = cliArgs;

            return cliArgs;
        }
    };
}
