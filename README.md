# LibMsON

This library is supposed to parse and create OneNote&reg; revision store files according to the [[MS-ONESTORE]](https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-onestore/ae670cd2-4b38-4b24-82d1-87cfb2cc3725) and [[MS-ONE]](https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-one/73d22548-a613-4350-8c23-07d15576be50) specifications. 

Currently, this is mainly an exercise in learning software development by doing. This means the current state does not provide alot of useful features other than parsing some elements of the OneNote&reg;  file. The current structure is messy, and the parsing functionality is not yet extracted from the document model. 

However, a goal of writing this library is to add it as filter to the [Calligra](https://invent.kde.org/office/calligra) project, [BasKet](https://invent.kde.org/utilities/basket) or something new within the KDE realm.
It can be expected, that these projects already require Qt, and use CMake to be build. For this reason, this library will use these frameworks as well, even if they offer more functionality than required.

If you are looking for working OneNote parsers go to:
* [Apache Tika](https://tika.apache.org/), library to parse documents and meta data
* [Interop-TestSuites](https://github.com/OfficeDev/Interop-TestSuites), an OfficeDev repository by Microsoft to test a number of protocols

What I learn with this project I'll also contribute to the project [libone](https://github.com/tshikaboom/libone) which is based on [librevenge](https://sourceforge.net/projects/libwpd/). This library will be useful to a broader audience since it is already an important infrastructure for LibreOffice.



## Requirements

* Qt 5.12+ libraries
* CMake

likely will require `libmspack` as well in near future (used to unpack `.onepkg` files)

## Compiling

from the root directory of this repository run:
```
mkdir build && cd build
cmake ..
make
```

## Contributing
Any comments and contributions are welcome! Just open an issue, or drop me an [email](mailto:libmson@sebastianengel.eu).

If you run into any issues while trying to parse a file, consider to open an issue in which the respective file is submitted. That way i can figure out which part of the code is the likely culprit.


At some point this library should have a public API which masks the RevisionStoreFile components and lets you interact with the actual content of the notebooks/sections/pages only. If you imagine a specific use case, I would be glad to hear your ideas.


## TODO

* Make parsing more robust when encountering errors/ fail safely - study other libraries to extract pattern.
* Develop an API which can be used as public Facade masking all of the RevisionStoreFile components
* Create an XmlWriter which builds an xml file according to MS-ONE
* Object spaces, and maps for GUID/ExtendedGUIDs are not yet created
* Develop a DocumentBuilder/DocumentWriter to write own .one files to further analyze the file format
* TransactionLogFragment parsing is buggy. Sometimes parsing has to end before the given number of TransactionEntries can be parsed.
* SOLID principles are not considered enough. Most classes contain functionality which is a mixture of file operations, data structure and string writer.
* No graph implemented which describes the relationships between components, such as FileNodeList->FileNodeListFragment->FileNode, or Notebook->Page->Outline
* Regarding drawings, the algorithm in which points of a Stroke are serialized is yet not clear to me
* Deduct serialized format of Shapes
* Analyze Audio/Video embedded into File

* Create XMLs according to OneNotes XSD


## Disclaimer

This project is neither related nor endorsed by Microsoft in any way. The author does not have any affiliation with Microsoft. Information which is not specified in MS-ONESTORE is done by 'clean room reverse engineering' only, mostly with code found in this project. Third party software binaries have NOT been analyzed (or disassembled). Only .one, .onetoc2, and .onepkg files have been used to deduct unspecified information. This also means validity of the finding cannot be garuanteed.

Third party projects from which functionality has been derived are listed in LICENSE.3rdparty.md. This currently includes :

* Qt Open Source Edition - 5.15
* OfficeDev's [Interop-TestSuites][1]
* pablospe's [cmake-example-library][2]


[1]: https://github.com/OfficeDev/Interop-TestSuites
[2]: https://github.com/pablospe/cmake-example-library
