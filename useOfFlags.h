#ifndef PROJEKTFLAGI_USEOFFLAGS_H
#define PROJEKTFLAGI_USEOFFLAGS_H

/**
 * This file opens any file we want to use
 * @param fileToWriteTo is a file to open to write our answers to in case of -o flag
 * @param fileToTakeFrom is a file to read from (words or flags)
 * @param arguments is a vector of arguments to take file names from
 * @param isThereAnOFlag is used to determine if we open a fileToWriteTo
 * @param fileToTakeFromName is used to set fileToTakeFrom name outside of the function
 */
auto createFilesToUse(
        std::ofstream &fileToWriteTo,
        std::ifstream &fileToTakeFrom,
        const std::vector<std::string> &arguments,
        const bool &isThereAnOFlag,
        std::string fileToTakeFromName
) -> void {
    auto fileToTakeFromPosition = std::find(arguments.begin(), arguments.end(), "-f") + 1;
    fileToTakeFromName = *fileToTakeFromPosition;
    fileToTakeFrom.open(fileToTakeFromName);


    if (isThereAnOFlag) {
        auto fileToWriteToPosition = std::find(arguments.begin(), arguments.end(), "-o") + 1;
        auto fileToWriteToName = *fileToWriteToPosition;
        fileToWriteTo.open(fileToWriteToName, std::ios::app);
    }
}

/**
 * This function checks if two given words are anagrams
 * @param word1 is one of the words
 * @param word2 is second one of the words
 * @return true if they are anagrams, false if they are not
 */
auto checkIfWordsAreAnagrams(std::string word1, std::string word2) -> bool {
    int lengthOfWord1 = word1.length();
    int lengthOfWord2 = word2.length();

    if (lengthOfWord1 != lengthOfWord2)
        return false;

    sort(word1.begin(), word1.end());
    sort(word2.begin(), word2.end());

    for (int i = 0; i < lengthOfWord1; i++) {
        if (word1[i] != word2[i]) {
            return false;
        }
    }
    return true;
}

/**
 * This function counts lines in file
 * @param isThereAnOFlag is used to determine if we write answers in console or in file
 * @param arguments is used to get direction to file to count lines from
 */
auto useOfNFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto linesFromFile = std::vector<std::string>();
    while (!fileToTakeFrom.eof()) {
        auto lineFromFile = std::string();
        std::getline(fileToTakeFrom, lineFromFile);
        linesFromFile.push_back(lineFromFile);
    }
    auto amountOfLinesFromFile = linesFromFile.size();

    if (isThereAnOFlag) {
        fileToWriteTo << "There is " << amountOfLinesFromFile << " lines in file\n";
    } else {
        std::cout << "There is " << amountOfLinesFromFile << " lines in file\n";
    }

}

/**
 * This function counts digits in file
 * @param isThereAnOFlag is used to determine if we write answers in console or in file
 * @param arguments is used to get direction to file to count digits from
 */
auto useOfDFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto linesFromFile = std::vector<std::string>();
    while (!fileToTakeFrom.eof()) {
        auto lineFromFile = std::string();
        std::getline(fileToTakeFrom, lineFromFile);
        linesFromFile.push_back(lineFromFile);
    }

    auto amounOfDigitsInFile = 0;

    for (const auto &line : linesFromFile) {
        for (auto character : line) {
            if (std::isdigit(character)) {
                amounOfDigitsInFile++;
            }
        }
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "There is " << amounOfDigitsInFile << " digits in file\n";
    } else {
        std::cout << "There is " << amounOfDigitsInFile << " digits in file\n";
    }

}

/**
 * This function counts numbers in file
 * @param isThereAnOFlag is used to determine if we write answers in console or in file
 * @param arguments is used to get direction to file to count numbers from
 */
auto useOfDDFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    auto amountOfNumbersInFile = 0;

    for (const auto &word : wordsFromFile) {
        auto isItANumber = true;
        for (int i = 0; i < word.size(); i++) {
            if (!std::isdigit(word[i])) {
                if (word[i] == '.' && word[i + 1] == '.') {
                    isItANumber = false;
                    break;
                } else {
                    if (word[i] != '.') {
                        isItANumber = false;
                        break;
                    } else {
                        if (word[i + 1] != '.') {
                            isItANumber = true;
                        }
                    }
                }
            }
        }
        if (isItANumber) {
            amountOfNumbersInFile++;
        }
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "There is " << amountOfNumbersInFile << " numbers in file\n";
    } else {
        std::cout << "There is " << amountOfNumbersInFile << " numbers in file\n";
    }

}

/**
 * This function counts characters in file
 * @param isThereAnOFlag is used to determine if we write answers in console or in file
 * @param arguments is used to get direction to file to count characters from
 */
auto useOfCFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }
    auto amountOfCharactersInFile = 0;

    // Doesn't count whitespaces
    for (const auto &word : wordsFromFile) {
        amountOfCharactersInFile += word.size();
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "There is " << amountOfCharactersInFile << " characters in file\n";
    } else {
        std::cout << "There is " << amountOfCharactersInFile << " characters in file\n";
    }

}

/**
 * This function counts words in file
 * @param isThereAnOFlag is used to determine if we write answers in console or in file
 * @param arguments is used to get direction to file to count words from
 */
auto useOfWFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    auto amountOfWordsInFile = wordsFromFile.size();

    if (isThereAnOFlag) {
        fileToWriteTo << "There is " << amountOfWordsInFile << " words in file\n";
    } else {
        std::cout << "There is " << amountOfWordsInFile << " words in file\n";
    }

}

/**
 * This function is used to change isThereAnLFlag to true if there is an -l flag
 * @param isThereAnLFlag is used by -s or by -rs to start sorting by length
 */
auto useOfLFlag(bool &isThereAnLFlag) -> void {
    isThereAnLFlag = true;
}

/**
 * This function sorts words alphabeticaly
 * @param isThereAnOFlag determines if we write answers in file or in console
 * @param arguments rguments is used to get direction to file to get words to sort from
 * @param isThereAnLFlag is used to change sorting to length
 */
auto useOfSFlag(
        const bool &isThereAnOFlag,
        const std::vector<std::string> &arguments,
        bool &isThereAnLFlag
) -> void {
    auto wayOfSorting = [isThereAnLFlag](const std::string &word1, const std::string &word2) {
        if (isThereAnLFlag) {
            return word2.size() > word1.size();
        } else {
            return word1 < word2;
        }
    };
    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    std::sort(wordsFromFile.begin(), wordsFromFile.end(), wayOfSorting);

    auto alphabeticalOrLength = std::string();
    if (isThereAnLFlag) {
        alphabeticalOrLength = "by length: ";
    } else {
        alphabeticalOrLength = "alphabeticaly: ";
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "Words " << alphabeticalOrLength;
    } else {
        std::cout << "Words " << alphabeticalOrLength;
    }

    for (const auto &word : wordsFromFile) {
        if (isThereAnOFlag) {
            fileToWriteTo << word << ' ';
        } else {
            std::cout << word << ' ';
        }
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "\n";
    } else {
        std::cout << "\n";
    }
    isThereAnLFlag = false;
}

/**
 * This function sorts words alphabeticaly and reverses them
 * @param isThereAnOFlag determines if we write answers in file or in console
 * @param arguments rguments is used to get direction to file to get words to sort from
 * @param isThereAnLFlag is used to change sorting to length
 */
auto useOfRSFlag(
        const bool &isThereAnOFlag,
        const std::vector<std::string> &arguments,
        bool &isThereAnLFlag
) -> void {
    auto wayOfSorting = [isThereAnLFlag](const std::string &word1, const std::string &word2) {
        if (isThereAnLFlag) {
            return word2.size() > word1.size();
        } else {
            return word1 < word2;
        }
    };

    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    std::sort(wordsFromFile.begin(), wordsFromFile.end(), wayOfSorting);
    std::reverse(wordsFromFile.begin(), wordsFromFile.end());

    auto alphabeticalOrLength = std::string();
    if (isThereAnLFlag) {
        alphabeticalOrLength = "by length backwards: ";
    } else {
        alphabeticalOrLength = "alphabeticaly backwards: ";
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "Words " << alphabeticalOrLength;
    } else {
        std::cout << "Words " << alphabeticalOrLength;
    }

    if (isThereAnOFlag) {
        for (const auto &word : wordsFromFile)
            fileToWriteTo << word << ' ';
    } else {
        for (const auto &word : wordsFromFile)
            std::cout << word << ' ';
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "\n";
    } else {
        std::cout << "\n";
    }
    isThereAnLFlag = false;
}

/**
 * This function prints words that are anagrams of arguments given after -a
 * @param isThereAnOFlag is used to determine if we print in file or in console
 * @param arguments is used to get arguments after -a
 */
auto useOfAFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto positionOfFlagA = std::find(arguments.begin(), arguments.end(), "-a");
    auto argumentsAfterAFlag = std::vector<std::string>();
    argumentsAfterAFlag.insert(argumentsAfterAFlag.begin(), positionOfFlagA + 1, arguments.end());

    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    auto anagramsOfArguments = std::vector<std::string>();

    for (const auto &argumentWord : argumentsAfterAFlag) {
        for (const auto &wordFromFile : wordsFromFile) {
            if (checkIfWordsAreAnagrams(argumentWord, wordFromFile)) {
                if (std::find(anagramsOfArguments.begin(),
                              anagramsOfArguments.end(),
                              wordFromFile)
                    ==
                    anagramsOfArguments.end()) {
                    anagramsOfArguments.push_back(wordFromFile);
                }
            }
        }
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "Words that are anagrams of arguments after -a or --anagram: ";
        for (const auto &anagram : anagramsOfArguments) {
            fileToWriteTo << anagram << ' ';
        }
        fileToWriteTo << '\n';
    } else {
        std::cout << "Words that are anagrams of arguments after -a or --anagram: ";
        for (const auto &anagram : anagramsOfArguments) {
            std::cout << anagram << ' ';
        }
        std::cout << '\n';
    }
}

/**
 * This function is used to see if words in arguments are palindromes and if they are in file
 * @param isThereAnOFlag is used to determine if we print in file or in console
 * @param arguments is used to get arguments after -p
 */
auto useOfPFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto positionOfFlagP = std::find(arguments.begin(), arguments.end(), "-p");
    auto argumentsAfterFlagP = std::vector<std::string>();
    argumentsAfterFlagP.insert(argumentsAfterFlagP.begin(), positionOfFlagP + 1, arguments.end());

    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    auto palindromesInArguments = std::vector<std::string>();

    for (auto argument : argumentsAfterFlagP) {
        if (argument == std::string(argument.rbegin(), argument.rend())
            &&
            std::find(wordsFromFile.begin(), wordsFromFile.end(), argument) != wordsFromFile.end()) {
            if (std::find(palindromesInArguments.begin(),
                          palindromesInArguments.end(),
                          argument)
                ==
                palindromesInArguments.end()) {
                palindromesInArguments.push_back(argument);
            }
        }
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "Words that are palindromes and are in file: ";
        for (const auto &palindrome : palindromesInArguments) {
            fileToWriteTo << palindrome << ' ';
        }
        fileToWriteTo << '\n';
    } else {
        std::cout << "Words that are palindromes and are in file: ";
        for (const auto &palindrome : palindromesInArguments) {
            std::cout << palindrome << ' ';
        }
        std::cout << '\n';
    }
}

/**
 * This function is used to count words given after -ss inside the file
 * @param isThereAnOFlag is used to determine if we print in file or in console
 * @param arguments is used to get arguments after -ss
 */
auto useOfSSFlag(const bool &isThereAnOFlag, const std::vector<std::string> &arguments) -> void {
    auto positionOfFlagSS = std::find(arguments.begin(), arguments.end(), "-ss");
    auto argumentsAfterFlagSS = std::vector<std::string>();
    argumentsAfterFlagSS.insert(argumentsAfterFlagSS.begin(), positionOfFlagSS + 1, arguments.end());

    auto fileToTakeFrom = std::ifstream();
    auto fileToWriteTo = std::ofstream();
    auto fileToTakeFromName = std::string();

    createFilesToUse(fileToWriteTo, fileToTakeFrom, arguments, isThereAnOFlag, fileToTakeFromName);

    auto wordsFromFile = std::vector<std::string>();

    while (!fileToTakeFrom.eof()) {
        auto wordFromFile = std::string();
        fileToTakeFrom >> wordFromFile;
        wordsFromFile.push_back(wordFromFile);
    }

    auto amountOfWordsInFile = std::vector<int>();

    for (const auto &word : argumentsAfterFlagSS) {
        amountOfWordsInFile.push_back(std::count(wordsFromFile.begin(), wordsFromFile.end(), word));
    }

    for (int i = 0; i < argumentsAfterFlagSS.size(); i++) {
        for (int j = 0; j < argumentsAfterFlagSS.size() - 1; j++) {
            if (amountOfWordsInFile[j] < amountOfWordsInFile[j + 1]) {
                std::swap(amountOfWordsInFile[j], amountOfWordsInFile[j + 1]);
                std::swap(argumentsAfterFlagSS[j], argumentsAfterFlagSS[j + 1]);
            }
        }
    }

    if (isThereAnOFlag) {
        fileToWriteTo << "Words and their amount in file:\n";
        for (int i = 0; i < argumentsAfterFlagSS.size(); i++) {
            fileToWriteTo << argumentsAfterFlagSS[i] << ' ' << amountOfWordsInFile[i] << "\n";
        }
    } else {
        std::cout << "Words and their amount in file:\n";
        for (int i = 0; i < argumentsAfterFlagSS.size(); i++) {
            std::cout << argumentsAfterFlagSS[i] << ' ' << amountOfWordsInFile[i] << "\n";
        }
    }

}

/**
 * This function goes through all of the flags and uses them
 * @param arguments is used by flags
 * @param vectorOfFlags is used to go over all the flags
 * @param isThereAnOFlag is used to determine if we print in file or in console
 */
auto useOfFlags(
        const std::vector<std::string> &arguments,
        const std::vector<Flags> &vectorOfFlags,
        const bool isThereAnOFlag
) -> void {
    auto isThereAnLFlag = false;
    for (auto flag : vectorOfFlags) {
        switch (flag) {
            case Flags::f:
                break;
            case Flags::n:
                useOfNFlag(isThereAnOFlag, arguments);
                break;
            case Flags::d:
                useOfDFlag(isThereAnOFlag, arguments);
                break;
            case Flags::dd:
                useOfDDFlag(isThereAnOFlag, arguments);
                break;
            case Flags::c:
                useOfCFlag(isThereAnOFlag, arguments);
                break;
            case Flags::w:
                useOfWFlag(isThereAnOFlag, arguments);
                break;
            case Flags::s:
                useOfSFlag(isThereAnOFlag, arguments, isThereAnLFlag);
                break;
            case Flags::rs:
                useOfRSFlag(isThereAnOFlag, arguments, isThereAnLFlag);
                break;
            case Flags::l:
                useOfLFlag(isThereAnLFlag);
                break;
            case Flags::a:
                useOfAFlag(isThereAnOFlag, arguments);
                break;
            case Flags::p:
                useOfPFlag(isThereAnOFlag, arguments);
                break;
            case Flags::ss:
                useOfSSFlag(isThereAnOFlag, arguments);
                break;
        }
    }

}


#endif
