#ifndef PROJEKTFLAGI_FLAGCHECKS_H
#define PROJEKTFLAGI_FLAGCHECKS_H

#include <filesystem>
#include <exception>
#include <regex>

#include "flagsAndAliases.h"

/**
 * This function checks if there is an argument after -f flag and checks if file
 * direction is correct (if the file exists).
 * @param arguments are arguments from parameters or file given after -i and is used to get file direction
 * @return returns file direction after everything is deemed correct
 */
auto checkFFlag(const std::vector<std::string> &arguments
) -> std::string {
    auto amountOfFFlags = std::count(arguments.begin(), arguments.end(), "-f");
    if (amountOfFFlags > 1) {
        throw std::runtime_error("More than one -f flag or --file alias given!");
    }
    if (arguments[arguments.size() - 1] == "-f") {
        throw std::runtime_error("No argument given after -f or --file");
    }
    auto fileNamePosition = std::find(arguments.begin(), arguments.end(), "-f") + 1;
    auto fileDirection = std::string(*fileNamePosition);
    if (!std::filesystem::exists(fileDirection)) {
        throw std::runtime_error("File given after -f or --file doesn't exist or wrong direction");
    }
    return fileDirection;
}
/**
 * This function checks if there is an argument after -i flag and checks if file
 * direction is correct (if the file exists).
 * @param arguments are arguments from parameters or file given after -i and is used to get file direction
 * @param vectorOfFlags are flags that are used to check if -i is the only flag used
 * @return returns file direction after everything is deemed correct
 */
auto checkIFlag(const std::vector<std::string> &arguments,
                std::vector<Flags> &vectorOfFlags
) -> std::string {
    auto fileDirection = std::string();
    if (
            vectorOfFlags.size() > 1
            &&
            std::find(arguments.begin(), arguments.end(), "--help") != arguments.end()) {
        throw std::runtime_error("Flag -i or it's alias --input is not the only one");
    } else {
        if (arguments[arguments.size() - 1] == "-i") {
            throw std::runtime_error("No argument given after -i or --input");
        }
        auto fileNamePosition = std::find(arguments.begin(), arguments.end(), "-i") + 1;
        fileDirection = std::string(*fileNamePosition);
        if (!std::filesystem::exists(fileDirection)) {
            throw std::runtime_error("File doesn't exist or wrong direction given");
        }
    }
    return fileDirection;
}

/**
 * This function checks if there is an -s or -rs flag after an -l flag
 * @param vectorOfFlags is a vector with flags that is used to check if there are -s or -rs after -l
 */
auto checkLFlag(std::vector<Flags> &vectorOfFlags) -> void {
    auto lastFoundLFlag = std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::l);
    for (int i = 0; i < std::count(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::l); i++) {
        if (std::find(lastFoundLFlag, vectorOfFlags.end(), Flags::l) != vectorOfFlags.end()) {
            if (
                    std::find(lastFoundLFlag, vectorOfFlags.end(), Flags::s) == vectorOfFlags.end()
                    &&
                    std::find(lastFoundLFlag, vectorOfFlags.end(), Flags::rs) == vectorOfFlags.end()) {
                throw std::runtime_error("No -s or -rs flag after -l flag!");
            }
            lastFoundLFlag = std::find(lastFoundLFlag + 1, vectorOfFlags.end(), Flags::l);
        }
    }
}

/**
 * This function is used to check if the -a flag is the last flag in the arguments
 * @param vectorOfFlags is used to check if its last element is -a
 */
auto checkAFlag(std::vector<Flags> &vectorOfFlags) -> void {
    if (
            std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::a) != vectorOfFlags.end()
            &&
            vectorOfFlags[vectorOfFlags.size() - 1] != Flags::a
            ) {
        throw std::runtime_error("-a flag or --anagrams alias is not the last flag given!");
    }
}

/**
 * This function is used to check if the -p flag is the last flag in the arguments
 * @param vectorOfFlags is used to check if its last element is -p
 */
auto checkPFlag(std::vector<Flags> &vectorOfFlags) -> void {
    if (
            std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::p) != vectorOfFlags.end()
            &&
            vectorOfFlags[vectorOfFlags.size() - 1] != Flags::p
            ) {
        throw std::runtime_error("-p flag or --palindromes alias is not the last flag given!");
    }
}

/**
 * This function is used to check if the -ss flag is the last flag in the program
 * @param vectorOfFlags is used to check if its last element is -ss
 */
auto checkSSFlag(std::vector<Flags> &vectorOfFlags) -> void {
    if (
            std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::ss) != vectorOfFlags.end()
            &&
            vectorOfFlags[vectorOfFlags.size() - 1] != Flags::ss
            ) {
        throw std::runtime_error("-ss flag or --string-search alias is not the last flag given!");
    }
}

/**
 * This function checks if there is any argument after -o flag and if file direction is correct
 * (if the file exists or can be created in given place)
 * @param arguments are used to get name of file after -o flag
 * @param vectorOfFlags is an vector with flags used to check if there is an -o flag
 * @param isThereAOFlag is a boolean that is used later to check if we should write in console or in file
 */
auto
checkOFlag(
        const std::vector<std::string> &arguments,
        const std::vector<Flags> &vectorOfFlags,
        bool &isThereAOFlag
) -> void {
    isThereAOFlag = std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::o) != vectorOfFlags.end();
    if (isThereAOFlag) {
        if (arguments[arguments.size() - 1] == "-o") {
            throw std::runtime_error("No argument given after -o or --output");
        } else {
            auto fileNameToWriteToPosition = std::find(arguments.begin(), arguments.end(), "-o") + 1;
            auto fileDirection = std::string(*fileNameToWriteToPosition);
            if (!std::filesystem::exists(fileDirection)) {
                std::regex match(R"(^(?:[\w]:|\)(\[a-z_-\s0-9.]+)+.(txt)$)");
                if (!std::regex_match(fileDirection, match)) {
                    throw std::runtime_error("File direction is not correct, file couldn't be created");
                }
                std::cout << "File with direction after -o or --output didn't exist so it's getting created";
                auto fileToCreate = std::ofstream();
                fileToCreate.open(fileDirection);
                fileToCreate.close();
            }
        }
    }
}

/**
 * This function checks if any flag given in arguments doesn't exist
 * @param arguments is used to get any flag that starts with - and to check in map if it doesn't exist
 * @param flagsAndStrings is a map with every flag that is correct and is used to check if any flag from
 * arguments isn't correct
 */
void isFlagInMap(const std::vector<std::string> &arguments, const std::map<std::string, Flags> &flagsAndStrings) {
    for (const auto &argument : arguments) {
        bool doesFlagExist = false;
        bool isItAFlag = false;
        for (const auto &flag : flagsAndStrings) {
            if (argument[0] == '-') {
                isItAFlag = true;
                if (argument == flag.first || argument == "--help") {
                    doesFlagExist = true;
                    break;
                }
            }
        }
        if (isItAFlag && !doesFlagExist) {
            throw std::runtime_error("Flag that doesnt exist was given");
        }
    }
}

/**
 * This function uses every flag checker and if there is a file to use
 * @param flagsAndStrings map of flags to get used in isFlagInMap
 * @param arguments are arguments given in parameters or in file after -i
 * @param vectorOfFlags is a vector of flags used to check if flags are correctly placed
 * @param isThereAOFlag is used in the application to see if we write in console or a file
 */
auto flagChecker(const std::map<std::string, Flags> &flagsAndStrings,
                 const std::vector<std::string> &arguments,
                 std::vector<Flags> &vectorOfFlags,
                 bool& isThereAOFlag
) -> void {
    isFlagInMap(arguments, flagsAndStrings);
    auto fileDirection = std::string("");
    if (std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::f) != vectorOfFlags.end()) {
        fileDirection = checkFFlag(arguments);
    }
    if (std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::i) != vectorOfFlags.end()) {
        fileDirection = checkIFlag(arguments, vectorOfFlags);
    }
    if (!std::filesystem::exists(fileDirection)) {
        throw std::runtime_error("No file to use flags on");
    }
    checkLFlag(vectorOfFlags);
    checkAFlag(vectorOfFlags);
    checkPFlag(vectorOfFlags);
    checkSSFlag(vectorOfFlags);
    checkOFlag(arguments, vectorOfFlags, isThereAOFlag);
}

/**
 * This function checks if there is no arguments or if --help argument was given
 * @param arguments are arguments given in parameters or in file after -i
 * @param vectorOfFlags is vector of every flag given
 */
auto getHelp(const std::vector<std::string> &arguments, const std::vector<Flags> &vectorOfFlags) -> void {
    if (vectorOfFlags.empty() || std::find(arguments.begin(), arguments.end(), "--help") != arguments.end()) {
        std::cout << "Flags to use: \n\n"
                     "-f filename or --file filename to add file to read from"
                     "-n or --newlines to get amount of lines from file given\nafter -f\n\n"
                     "-d or --digits to see amount of digits in file given after -f\n\n"
                     "-dd or --numbers to see amount of numbers in file given after -f\n\n"
                     "-c or --chars to see amount of characters in file given after -f\n\n"
                     "-w or --words to see amount of words in file given after -f (numbers are also counted as words)\n\n"
                     "-s or --sorted to see every word from file in alphabetical order\n\n"
                     "-rs or --reverse-sorted to see every word from file in reversed alphabetical order\n\n"
                     "-l or --by-length has to be before -s or -rs. Use it to show every word ordered by lenght"
                     " and not alphabeticaly\n\n"
                     "-a or --anagrams should be the last flag."
                     " This will show anagrams of words placed after this flag."
                     "\nThe anagrams will come from file after -f\n\n"
                     "-o filename or --output filename to make every information"
                     " printed in the file rather than in a console\n\n"
                     "-p or --palindromes should be the last flag."
                     " This will show words after the flag that are PALINDROMES and exist in file given by -f\n\n"
                     "-i filename or --input filename should be the only flag in arguments."
                     " This will get all flags from given file and use\nthem as arguments\n\n"
                     "-ss or --string-search should be the last flag. "
                     "This will show amount of words in file that were given after this flag\n\n";
    }
}


#endif
