# C++ Flag-Based Text Tool
This is a C++ project that was created as a part of my University studies at the Polish-Japanese Academy of Information Technology.
It is a command-line tool performing various operations on text files based on flags the user chose to use.
# Features
## Basic functionality:
- Flag parsing with aliases (for example, -f can also be used as --file).
- Two possible outputs - to console or to file if an -o flag was used.
- Error handling in case of incorrect order of flags or if the flags do not have needed arguments after them.
## Supported flags:
### File operations:
- -f {filename} or --file {filename} - used to choose a file to read the text from.
- -o {filename} or --output {filename} - used to change the output to a file.
- -i {filename} or --input {filename} - used to read flags from a file instead of the command line.
### Text statistics:
- -n or --newlines - used to count the number of lines in the file.
- -d or --digits - used to count the number of digits in the file.
- -dd or --numbers - used to count the amount of numbers in the file.
- -c or --chars - used to count the amount of individual characters in the file.
- -w or --words - used to count the amount of words in the file.
### Sorting:
- -s or --sorted - used to output the words from the file in alphabetical order.
- -rs or --reverse-sorted - used to output the words from the file in reversed alphabetical order.
- -l or --by-length - used to output every word from the file ordered by length.
### Patterns:
- -a {words} or --anagrams {words} - used to find words from the file that are anagrams of the given words.
- -p {words} or --palindromes {words} - used to find which from the given words are palindromes and are present in the given file.
- -ss {words} or --string-search {words} - used to find how many times the words given behind this flag appear in the file.
# Purpose and how it works
This tool is a simple project to help operate on text based files. It reads flags from the command line or a file if the -i flag was used in the command line, checks if the order of the flags and their use is correct and applies operations to the input file given after the -f flag. Output is printed in the console or in a file if the -o flag is used.
# Technologies
This application was created using C++17 and only uses the Standard Template Library.

### This project is shared for educational and demonstration purposes only. Ownership and reuse may be subject to university IP policies.