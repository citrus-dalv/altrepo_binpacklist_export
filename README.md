# ALTlinux binary packages repository export library
C++ Library for exporting packages list from ALTRepo API

## Building
### Requirements
* libcurl library. On author machine libcurl version 4.7.0.
* make utility
* g++ compiler
### Make
  Project building is automated by make utility. Makefile have main targets 'library' and 'prog'. You can build library separately.
  Just run make without any arguments. This will create the library and cli-unitiliy. Shared library is located in directory lib/.
  It also creates there a symbolic link to library. You can copy it to system directories before run cli-untility.
  
## Library usage
You have to include to your project lib/include/altrepo_export.h. It contains class Exporter, wich contains the method export_branch_packages(). Also contains struct PackageKit. Meghod export_branch_packages() wors with it and returns count of retrieved packages from server.
Before call it, you have to set URL via set_url_export(const char*)
> altrepo::Exporter exp;\
> exp.set_url_export('url');\
> altrepo::PackageKit packages;\
> exp.export_branch_packages("i586", "p10");


or create Exporter instance like:
> altrepo::Exporter exp('url');

## Launch
You have to add library (lib/libaltrepo_export.so) to your system libraries directory.
Cli-utility compares both branches, selects unique packages in them and packages with the upper version and writes result in JSON format to standard output.
By deafult cli-program names 'prog'. Program expects three arguments: architecture name, first branch name, second branch name. Program will terminate if will given another count of command line arguments.

Launch example:
>  ./prog i586 p9 p10
  
Just redirect standart output stream to file
> ./prog i586 p9 p10 > result.json

JSON output format:
```json
{
  "arch": "",
  "uniques":
      {
        "first":{"name": "", "count": "", "packages": []},
        "second":{"name": "", "count": "", "packages": []}
      },
  "upper_version":
      {
          "count": "",
          "packages": []
      }
}
```
#### Author:
Vladislav Yusov, Magnitogorsk, 2023.
citrus.dalv@mail.ru


### Project uses nlohmann json library
https://github.com/nlohmann/json

The class is licensed under the MIT License:
Copyright © 2013-2022 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

The class contains the UTF-8 Decoder from Bjoern Hoehrmann which is licensed under the MIT License (see above). Copyright © 2008-2009 Björn Hoehrmann bjoern@hoehrmann.de
The class contains a slightly modified version of the Grisu2 algorithm from Florian Loitsch which is licensed under the MIT License (see above). Copyright © 2009 Florian Loitsch
The class contains a copy of Hedley from Evan Nemerson which is licensed as CC0-1.0.
The class contains parts of Google Abseil which is licensed under the Apache 2.0 License.
