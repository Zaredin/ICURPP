#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <thread>
#include <chrono>

// Struct to hold victim's profile information
struct Profile {
    std::string name;
    std::string surname;
    std::string nick;
    std::string birthdate;
    std::string wife;
    std::string wifen;
    std::string wifeb;
    std::string kid;
    std::string kidn;
    std::string kidb;
    std::string pet;
    std::string company;
    std::vector<std::string> words;
    bool spechars;
    bool randnum;
    bool leetmode;
    bool flipwords;
    bool capwords;
};

// Function to ask questions and fill profile data
void askQuestions(Profile &profile) {
    std::cout << "\n[+] Insert the information about the victim to make a dictionary (low cap)\n";
    std::cout << "[+] If you don't know all the info, just hit enter when asked! ;)\n\n";

    std::cout << "> First Name: ";
    std::getline(std::cin, profile.name);

    while (profile.name.empty()) {
        std::cout << "\n[-] You must enter a name at least!";
        std::cout << "> First Name: ";
        std::getline(std::cin, profile.name);
    }

    std::cout << "> Surname: ";
    std::getline(std::cin, profile.surname);

    std::cout << "> Nickname: ";
    std::getline(std::cin, profile.nick);

    std::cout << "> Birthdate (DDMMYYYY): ";
    std::getline(std::cin, profile.birthdate);

    while (!profile.birthdate.empty() && profile.birthdate.length() != 8) {
        std::cout << "\n[-] You must enter 8 digits for birthday!";
        std::cout << "> Birthdate (DDMMYYYY): ";
        std::getline(std::cin, profile.birthdate);
    }

    std::cout << "\n> Partner's name: ";
    std::getline(std::cin, profile.wife);

    std::cout << "> Partner's nickname: ";
    std::getline(std::cin, profile.wifen);

    std::cout << "> Partner's birthdate (DDMMYYYY): ";
    std::getline(std::cin, profile.wifeb);

    while (!profile.wifeb.empty() && profile.wifeb.length() != 8) {
        std::cout << "\n[-] You must enter 8 digits for birthday!";
        std::cout << "> Partner's birthdate (DDMMYYYY): ";
        std::getline(std::cin, profile.wifeb);
    }

    std::cout << "\n> Child's name: ";
    std::getline(std::cin, profile.kid);

    std::cout << "> Child's nickname: ";
    std::getline(std::cin, profile.kidn);

    std::cout << "> Child's birthdate (DDMMYYYY): ";
    std::getline(std::cin, profile.kidb);

    while (!profile.kidb.empty() && profile.kidb.length() != 8) {
        std::cout << "\n[-] You must enter 8 digits for birthday!";
        std::cout << "> Child's birthdate (DDMMYYYY): ";
        std::getline(std::cin, profile.kidb);
    }

    std::cout << "\n> Pet's name: ";
    std::getline(std::cin, profile.pet);

    std::cout << "> Company name: ";
    std::getline(std::cin, profile.company);

    std::cout << "\n> Do you want to add some key words about the victim? Y/[N]: ";
    std::string addWords;
    std::getline(std::cin, addWords);

    if (addWords == "Y" || addWords == "y") {
        std::cout << "> Please enter the words, separated by comma. [i.e. hacker,juice,black], spaces will be removed: ";
        std::string wordsInput;
        std::getline(std::cin, wordsInput);
        size_t pos = 0;
        while ((pos = wordsInput.find(',')) != std::string::npos) {
            profile.words.push_back(wordsInput.substr(0, pos));
            wordsInput.erase(0, pos + 1);
        }
        profile.words.push_back(wordsInput);
    }

    std::cout << "\n> Do you want to add special chars at the end of words? Y/[N]: ";
    std::string addSpecialChars;
    std::getline(std::cin, addSpecialChars);
    profile.spechars = (addSpecialChars == "Y" || addSpecialChars == "y");

    std::cout << "> Do you want to add some random numbers at the end of words? Y/[N]: ";
    std::string addRandomNumbers;
    std::getline(std::cin, addRandomNumbers);
    profile.randnum = (addRandomNumbers == "Y" || addRandomNumbers == "y");

    std::cout << "> Leet mode? (i.e. leet = 1337) Y/[N]: ";
    std::string leetMode;
    std::getline(std::cin, leetMode);
    profile.leetmode = (leetMode == "Y" || leetMode == "y");

    std::cout << "> Flip words? (i.e. John -> nhoJ) Y/[N]: ";
    std::string flipWords;
    std::getline(std::cin, flipWords);
    profile.flipwords = (flipWords == "Y" || flipWords == "y");

    std::cout << "> Capitalize words in various ways? Y/[N]: ";
    std::string capWords;
    std::getline(std::cin, capWords);
    profile.capwords = (capWords == "Y" || capWords == "y");
}

// Function to convert a string to leet speak
std::string toLeetSpeak(const std::string &str) {
    static std::unordered_map<char, char> leetDict = {
        {'a', '4'}, {'e', '3'}, {'i', '1'}, {'o', '0'}, {'s', '5'}, {'t', '7'}
    };
    std::string leetStr = str;
    for (auto &ch : leetStr) {
        if (leetDict.find(ch) != leetDict.end()) {
            ch = leetDict[ch];
        }
    }
    return leetStr;
}

// Function to flip a word
std::string flipWord(const std::string &str) {
    std::string flippedStr = str;
    std::reverse(flippedStr.begin(), flippedStr.end());
    return flippedStr;
}

// Function to generate all possible capitalization combinations of a word
void capitalizeCombinations(const std::string &str, std::unordered_set<std::string> &combinations) {
    size_t len = str.length();
    size_t maxComb = 1 << len;  // 2^len combinations

    for (size_t i = 0; i < maxComb; ++i) {
        std::string newComb = str;
        for (size_t j = 0; j < len; ++j) {
            if (i & (1 << j)) {
                newComb[j] = std::toupper(newComb[j]);
            }
        }
        combinations.insert(newComb);
    }
}

// Function to generate basic word combinations
void generateCombinations(const std::vector<std::string> &inputs, std::unordered_set<std::string> &combinations) {
    // Remove empty strings
    std::vector<std::string> nonEmptyInputs;
    std::copy_if(inputs.begin(), inputs.end(), std::back_inserter(nonEmptyInputs), [](const std::string &s) { return !s.empty(); });

    // Include single words
    for (const auto &word : nonEmptyInputs) {
        combinations.insert(word);
    }

    // Generate basic combinations
    for (size_t i = 0; i < nonEmptyInputs.size(); ++i) {
        for (size_t j = 0; j < nonEmptyInputs.size(); ++j) {
            if (i != j) {
                combinations.insert(nonEmptyInputs[i] + nonEmptyInputs[j]);
                combinations.insert(nonEmptyInputs[j] + nonEmptyInputs[i]);
            }
        }
    }
}

// Function to add special characters to combinations
void addSpecialChars(std::unordered_set<std::string> &combinations) {
    std::vector<char> specialChars = {'!', '@', '#', '$', '%', '&', '*'};
    std::unordered_set<std::string> newCombinations;
    for (const auto &str : combinations) {
        for (const auto &ch : specialChars) {
            newCombinations.insert(str + ch);
        }
    }
    combinations.insert(newCombinations.begin(), newCombinations.end());
}

// Function to add random numbers to combinations
void addRandomNumbers(std::unordered_set<std::string> &combinations, int count = 100) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 9999);
    std::unordered_set<std::string> newCombinations;
    for (const auto &str : combinations) {
        for (int i = 0; i < count; ++i) {
            newCombinations.insert(str + std::to_string(dist(gen)));
        }
    }
    combinations.insert(newCombinations.begin(), newCombinations.end());
}

// Function to apply leet speak transformation
void applyLeetMode(std::unordered_set<std::string> &combinations) {
    std::unordered_set<std::string> newCombinations;
    for (const auto &str : combinations) {
        newCombinations.insert(toLeetSpeak(str));
    }
    combinations.insert(newCombinations.begin(), newCombinations.end());
}

// Function to flip words
void applyFlipWords(std::unordered_set<std::string> &combinations) {
    std::unordered_set<std::string> newCombinations;
    for (const auto &str : combinations) {
        newCombinations.insert(flipWord(str));
    }
    combinations.insert(newCombinations.begin(), newCombinations.end());
}

// Function to apply capitalization combinations
void applyCapitalizeWords(std::unordered_set<std::string> &combinations) {
    std::unordered_set<std::string> newCombinations;
    for (const auto &str : combinations) {
        capitalizeCombinations(str, newCombinations);
    }
    combinations.insert(newCombinations.begin(), newCombinations.end());
}

// Function to show progress
void showProgress(size_t current, size_t total) {
    static const char* progressChars = "|/-\\";
    static int progressIndex = 0;
    std::cout << "\rGenerating potential passwords (" << progressChars[progressIndex] << ") "
              << current << "/" << total << std::flush;
    progressIndex = (progressIndex + 1) % 4;
}

size_t generateWordlist(const Profile &profile, const std::string &filename) {
    std::unordered_set<std::string> combinations;

    std::vector<std::string> inputs = {
        profile.name, profile.surname, profile.nick, profile.birthdate,
        profile.wife, profile.wifen, profile.wifeb, profile.kid,
        profile.kidn, profile.kidb, profile.pet, profile.company
    };
    inputs.insert(inputs.end(), profile.words.begin(), profile.words.end());

    generateCombinations(inputs, combinations);

    if (profile.capwords) {
        applyCapitalizeWords(combinations);
    }
    if (profile.flipwords) {
        applyFlipWords(combinations);
    }
    if (profile.spechars) {
        addSpecialChars(combinations);
    }
    if (profile.randnum) {
        addRandomNumbers(combinations);
    }
    if (profile.leetmode) {
        applyLeetMode(combinations);
    }

    // Check for empty wordlist
    if (combinations.empty()) {
        std::cout << "No word combinations generated." << std::endl;
        return 0;
    }

    // Write to file
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        size_t count = 0;
        size_t total = combinations.size();
        for (const auto &comb : combinations) {
            showProgress(++count, total);
            if (!outfile.write(comb.c_str(), comb.length())) {
                std::cerr << "Error writing to file: " << filename << std::endl;
                return -1;
            }
            outfile << std::endl;
        }
        std::cout << "\rGenerating potential passwords... Done!         " << std::endl;
        outfile.close();
        return total;
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return -1;
    }
}

int main() {
    Profile profile;
    askQuestions(profile);

    std::string filename;
    std::cout << "\n> Enter the name of the dictionary file to create: ";
    std::getline(std::cin, filename);

    std::cout << "\nGenerating potential passwords...\n";
    size_t wordCount = generateWordlist(profile, filename+".txt");

    std::cout << "\nWordlist generated with " << wordCount << " words and saved to " << filename << ".txt" << std::endl;

    // Prompt to press Enter to close the window
    std::cout << "\nPress Enter to close the window...";
    std::cin.get();

    return 0;
}