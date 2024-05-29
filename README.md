# XT_RefineSearchTerm

This is an X-Ways XTension which checks how many printable characters (A-Z, 0-9, spaces, punctuation), there is around a search hit from a Simultaneous Search operation. The user may input how many bytes to read before and after the search hit, and provide a percentage threshold of how many printable characters there should be to mark the hit a positive, otherwise ignore the search hit.

The primary reason for this XTension is to reduce the amount of false positive hits on a keyword search. For example, if the keyword happens to be amongst a binary file by chance.

## Table of Contents

- [XT\_RefineSearchTerm](#xt_refinesearchterm)
  - [Table of Contents](#table-of-contents)
  - [Requirements](#requirements)
  - [Contributing](#contributing)
  - [Environment Setup](#environment-setup)
  - [License](#license)

## Requirements

This XTension is tested with X-Ways 21.0 SR-6 x64.

Earlier versions of X-Ways have not been tested.

When running a Simultaneous Search, be sure to select this XTension in the appropriate settings:

![XWays Simultaneous Search Settings](3%20-%20Documentation/1%20-%20XWays%20Simultaneous%20Search.png)

Upon execution the user will be:

- Asked how many bytes to read before and after the search hit to calculate the printable character percentage.

  ![XT_RefineSearchTerm Byte Count](3%20-%20Documentation/2%20-%20XT_RefineSearchTerm%20-%20Byte%20Count.png)
- Asked what percentage of printable characters is required for a positive hit.

  ![XT_RefineSearchTerm Required Percentage](3%20-%20Documentation/3%20-%20XT_RefineSearchTerm%20-%20RequiredPercentage.png)

During testing, using the settings +30 bytes either side, and 90% requirement, keyword hits of 20,000+ are reduced to <1000 of predominantly clear text files. The searches may be rerun with other values to widen/narrow the positive criteria.

## Contributing

Pull Requests, Features, and Fixes are always welcome.

Please leave a detailed issue report for bugs so it may be reproduced.

## Environment Setup

This XTension has been created using Visual Studio in C++.

## License

GNU General Public License v3.0 or later

See [LICENSE](LICENSE.txt) to see the full text.
