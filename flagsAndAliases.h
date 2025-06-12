#ifndef PROJEKTFLAGI_FLAGSANDALIASES_H
#define PROJEKTFLAGI_FLAGSANDALIASES_H
/**
 * Enum with flags
 */
enum class Flags {
    f, n, d, dd, c, w, s, rs, l, a, p, o, i, ss
};

/**
 * This function is used to get flags as strings and put them in vector of flag enums
 * @param flagsAndStrings is a map used to change flags
 * @param arguments are arguments to get flags from
 * @param vectorOfFlags is a vector to fill with enums
 */
auto fillVectorOfFlags(const std::map<std::string, Flags> &flagsAndStrings,
                       const std::vector<std::string> &arguments,
                       std::vector<Flags> &vectorOfFlags) -> void {

    for (const auto &argument : arguments) {
        for (const auto &flag : flagsAndStrings) {
            if (argument == flag.first) {
                vectorOfFlags.push_back(flag.second);
            }
        }
    }
}

/**
 * this function is used to fill map with all the flags to use
 * @param flagsAndStrings is the map to fill
 */
auto fillMapWithFlags(std::map<std::string, Flags> &flagsAndStrings) -> void {
    flagsAndStrings["-f"] = Flags::f;
    flagsAndStrings["-n"] = Flags::n;
    flagsAndStrings["-d"] = Flags::d;
    flagsAndStrings["-dd"] = Flags::dd;
    flagsAndStrings["-c"] = Flags::c;
    flagsAndStrings["-w"] = Flags::w;
    flagsAndStrings["-s"] = Flags::s;
    flagsAndStrings["-rs"] = Flags::rs;
    flagsAndStrings["-l"] = Flags::l;
    flagsAndStrings["-a"] = Flags::a;
    flagsAndStrings["-p"] = Flags::p;
    flagsAndStrings["-o"] = Flags::o;
    flagsAndStrings["-i"] = Flags::i;
    flagsAndStrings["-ss"] = Flags::ss;
}

/**
 * This function is used to change every alias to its argument.
 * @param arguments is arguments with flags to change
 */
auto changeAliasesToFlags(std::vector<std::string> &arguments) -> void {
    auto mapOfAliasesToFlags = std::map<std::string, std::string>();
    mapOfAliasesToFlags["--file"] = "-f";
    mapOfAliasesToFlags["--newlines"] = "-n";
    mapOfAliasesToFlags["--digits"] = "-d";
    mapOfAliasesToFlags["--numbers"] = "-dd";
    mapOfAliasesToFlags["--chars"] = "-c";
    mapOfAliasesToFlags["--words"] = "-w";
    mapOfAliasesToFlags["--sorted"] = "-s";
    mapOfAliasesToFlags["--reverse-sorted"] = "-rs";
    mapOfAliasesToFlags["--by-length"] = "-l";
    mapOfAliasesToFlags["--anagrams"] = "-a";
    mapOfAliasesToFlags["--palindromes"] = "-p";
    mapOfAliasesToFlags["--output"] = "-o";
    mapOfAliasesToFlags["--input"] = "-i";
    mapOfAliasesToFlags["--string-search"] = "-s";

    for (auto &argument : arguments) {
        for (const auto& alias : mapOfAliasesToFlags) {
            if (argument == alias.first) {
                argument = alias.second;
                break;
            }
        }
    }

}

#endif
