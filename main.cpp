#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

#include "flagsAndAliases.h"
#include "flagChecks.h"
#include "useOfFlags.h"

int main(int args_count, const char *args[]) {

    auto arguments = std::vector<std::string>(args + 1, args + args_count);

    auto flagsAndStrings = std::map<std::string, Flags>();

    auto isThereAOFlag = false;

    auto wasThereAnIFlag = false;

    changeAliasesToFlags(arguments);

    fillMapWithFlags(flagsAndStrings);

    auto vectorOfFlags = std::vector<Flags>();

    fillVectorOfFlags(flagsAndStrings, arguments, vectorOfFlags);

    try {
        flagChecker(flagsAndStrings, arguments, vectorOfFlags, isThereAOFlag);
    } catch (std::runtime_error &e) {
        std::cout << e.what() << "\n";
        getHelp(arguments, vectorOfFlags);
        return 0;
    }

    if (isThereAOFlag) {
        auto fileToWriteToPosition = std::find(arguments.begin(), arguments.end(), "-o") + 1;
        auto fileToWriteToName = *fileToWriteToPosition;
        auto fileToWriteTo = std::ofstream();
        fileToWriteTo.open(fileToWriteToName, std::ofstream::out | std::ofstream::trunc);
        fileToWriteTo.close();
    }

    auto argumentsFromFile = std::vector<std::string>();
    auto isThereAnIFlag = std::find(vectorOfFlags.begin(), vectorOfFlags.end(), Flags::i) != vectorOfFlags.end();
    auto numberOfFlagI = 0;

    while (isThereAnIFlag) {
        auto fileInLocation = std::find(arguments.begin(), arguments.end(), "-i") + 1;
        if (numberOfFlagI == 0) {
            numberOfFlagI++;
        } else {
            fileInLocation = std::find(argumentsFromFile.begin(), argumentsFromFile.end(), "-i") + 1;
        }
        argumentsFromFile.clear();
        auto fileInName = *fileInLocation;
        auto fileIn = std::ifstream();
        fileIn.open(fileInName);
        while (!fileIn.eof()) {
            std::string argument;
            fileIn >> argument;
            argumentsFromFile.push_back(argument);
        }
        changeAliasesToFlags(argumentsFromFile);
        isThereAnIFlag = std::find(argumentsFromFile.begin(),
                                   argumentsFromFile.end(),
                                   "-i") != argumentsFromFile.end();
        wasThereAnIFlag = true;
    }

    if (!wasThereAnIFlag) {
        useOfFlags(arguments, vectorOfFlags, isThereAOFlag);
    } else {
        auto vectorOfFlagsFromFile = std::vector<Flags>();
        fillVectorOfFlags(flagsAndStrings, argumentsFromFile, vectorOfFlagsFromFile);
        try {
            flagChecker(flagsAndStrings, argumentsFromFile, vectorOfFlagsFromFile, isThereAOFlag);
        } catch (std::runtime_error &e) {
            std::cout << e.what() << "\n";
            getHelp(arguments, vectorOfFlags);
            return 0;
        }
        useOfFlags(argumentsFromFile, vectorOfFlagsFromFile, isThereAOFlag);
    }
}