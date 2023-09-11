/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {//read the file line by line
        string word_upper = word;
        std::transform(word_upper.begin(), word_upper.end(), word_upper.begin(), ::toupper);
        if (word_upper.size() == 5) {
            string word1 = word.substr(1);//remove the first letter
            string word2 = word[0] + word.substr(2);//remove the second letter
            if (d.homophones(word, word1) && d.homophones(word, word2)) {
                ret.push_back(std::make_tuple(word, word1, word2));
            }
        }
    }
}
    return ret;
}
