# LibMsON

This library is supposed to parse and create OneNote&trade; revision store files according to the [[MS-ONESTORE]](https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-onestore/ae670cd2-4b38-4b24-82d1-87cfb2cc3725) and [[MS-ONE]](https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-one/73d22548-a613-4350-8c23-07d15576be50) specifications. 

Currently, this is mainly an exercise in learning software development by doing. This means the current state does not provide alot of useful features other than parsing some elements of the OneNote&trade;  file. The current structure is messy, and the parsing functionality is not yet extracted from the document model. 

However, a goal of writing this library is to add it as filter to the [Calligra](https://invent.kde.org/office/calligra) project, [BasKet](https://invent.kde.org/utilities/basket) or something new within the KDE realm.
It can be expected, that these projects already require Qt, and use CMake to be build. For this reason, this library will use these frameworks as well, even if they offer more functionality than required.

If you are looking for working OneNote parsers go to:
* [Apache Tika](https://tika.apache.org/), library to parse documents and meta data
* [Interop-TestSuites](https://github.com/OfficeDev/Interop-TestSuites), an OfficeDev repository by Microsoft to test a number of protocols

## Requirements

* Qt 5.12+ libraries
* CMake

## Compiling

from the root directory of this repository run:
```
mkdir build && cd build
cmake ..
make
```

In the build directory, you can find the tool `one2xml`.

By calling the following command structure, you can convert `.one` and `.onetoc2` files to an xml format
```
one2xml -f \[filename\] 
```

Run `one2xml --help` for more information.

Right now, the xml format represents the revision store file's structure. Currently, this is hardly useful. 


## Contributing
Any comments and contributions are welcome!


## Disclaimer

This project is neither related nor endorsed by Microsoft in any way. The author does not have any affiliation with Microsoft. Use at your own risk.

