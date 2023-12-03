# Lab work <mark>7</mark>: <mark>Робота із бінарними даними на прикладі читання образу диску ext2 FS</mark>
Author: <mark>Dmytro Vasylkiv [Dima-Vas](https://github.com/Dima-Vas)</mark><br>
Variant: <mark>ext2fs</mark>
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

<code>-v</code> flag displays the whole info about file as required by task.

Non-verbose mode will simply print all the files and directories recursively

### Important!
- Verbose output is designed for at least 150-characters-wide terminal window

### Results
Learned that five minutes of reading the documentation may end the five-hour session of pain. RTFM.

# Additional tasks
- Рекурсивно вивести всі файли в образі
