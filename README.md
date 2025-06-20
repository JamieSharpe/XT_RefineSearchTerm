# XT_RefineSearchTerm

This is an X-Ways XTension which checks how many printable characters (A-Z, 0-9, spaces, punctuation), there is around a search hit from a Simultaneous Search operation. The user may input how many bytes to read before and after the search hit, and provide a percentage threshold of how many printable characters there should be to mark the hit a positive (not including the hit itself), otherwise ignore the search hit.

The primary reason for this XTension is to reduce the amount of false positive hits on a keyword search. For example, if the keyword happens to be amongst a binary file by chance.

## Table of Contents

- [XT\_RefineSearchTerm](#xt_refinesearchterm)
  - [Table of Contents](#table-of-contents)
  - [Requirements](#requirements)
  - [Sample](#sample)
  - [Contributing](#contributing)
  - [Environment Setup](#environment-setup)
  - [License](#license)

## Requirements

This XTension is tested with X-Ways 21.5 SR-0 x64. Earlier versions of X-Ways have not been tested.

Supported code pages:

- ANSI Latin 1 (1252)
- UTF-8 (65001)
- UTF16 LE (1200)

When running a Simultaneous Search, be sure to select this XTension in the appropriate settings:

![XWays Simultaneous Search Settings](3%20-%20Documentation/1%20-%20XWays%20Simultaneous%20Search.png)

Upon execution the user will be:

- Asked what percentage of printable characters is required for a positive hit.
- How many bytes to read before and after the search hit to calculate the printable character percentage.
- If the above numbers should be added to the search term suffix.
- A suffix to append to the name of the search term as a friendly name.

![XT_RefineSearchTerm UI Config](3%20-%20Documentation/2%20-%20XT_RefineSearchTerm%20-%20UI%20-%20Config.png)

During testing, using the settings 90% printable character requirement and +30 bytes either side for the hit context to check, keyword hits of 20,000+ are reduced to <1000 of predominantly clear text files. These values are the default settings.

It may be worth running the searches multiple times with different settings, modifying the suffix portion to reflect what options were used and to keep track of them.

## Sample

In the following text file, the word `tHorn` is located at `0x26`-`0x2A`:

```
    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
00  67 36 C3 D3 C5 06 03 AD 7C E1 1B 73 06 09 11 1E   g6ÃÓÅ...|á.s....
10  70 7A EB 25 AC DB 13 06 FF CB 1A F7 DF 51 0A 65   pzë%¬Û..ÿË.÷ßQ.e
20  EB 71 EC FA 60 39 74 48 6F 72 6E F1 F1 08 15 EE   ëqìú`9tHornññ..î
30  FF 4C 00 24 01 CB 31 EF C3 F5 98 67 ED 8A B4 A2   ÿL.$.Ë1ïÃõ˜gíŠ´¢
40  3D 58 39 75 31 66 59 AE 85 5B 5C 2E 92 AB 9B 50   =X9u1fY®…[\.’«›P
```

Traditional simultaneous search would mark this as a positive hit, along with hundreds/thousands of others just like this one. This extension checks the hit (by default) 30 bytes before, and after, to make sure (by default) 90% of them are printable characters, and if so mark the hit as positive, otherwise the hit is discarded. In the above example, it would be marked as a negative hit.

## Contributing

Pull Requests, Features, and Fixes are always welcome.

Please leave a detailed issue report for bugs so it may be reproduced.

## Environment Setup

This XTension has been created using Visual Studio in C++.

## License

GNU General Public License v3.0 or later

See [LICENSE](LICENSE.txt) to see the full text.
