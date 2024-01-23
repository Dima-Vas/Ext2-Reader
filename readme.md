This is my UCU laboratory code for working with binary data using pure C. The folder structure was provided by the UCU CS classroom, and I am the author of all the C code and CMakeLists.txt. Feel free to use and modify them with no licensing concerns.

## Prerequisites

<mark>gcc >= 11.4</mark>

<mark>cmake >= 3.22.1</mark>

### Compilation

Use CMake : 

<code>cmake -S . -B ./cmake/build</code> 

<code>cd ./cmake/build</code> 

<code>make</code> 

### Usage

<code>ext2_reader IMGPATH [-v]</code>

<code>-v</code> flag displays the whole info about file.

Non-verbose mode will simply print all the files and directories recursively

### Important!
- Verbose output is designed for at least 150-characters-wide terminal window
