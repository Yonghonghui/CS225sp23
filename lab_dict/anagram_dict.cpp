/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
        string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        if (dict.find(sortedWord) == dict.end()) {//if the key doesn't exist
            vector<string> anagrams;//create a vector of strings
            anagrams.push_back(word);//push the word into the vector
            dict[sortedWord] = anagrams;//add the vector to the map
        } else {//if the key already exists
            dict[sortedWord].push_back(word);//push the word into the vector
        }
    }
}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(unsigned i=0;i<words.size();i++){
        string word = words[i];
        string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());//sort the word
        if (dict.find(sortedWord) == dict.end()) {//if the key doesn't exist
            vector<string> anagrams;//create a vector of strings
            anagrams.push_back(word);//push the word into the vector
            dict[sortedWord] = anagrams;//add the vector to the map
        } else {//if the key already exists
            dict[sortedWord].push_back(word);//push the word into the vector
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sortedWord = word;
    std::sort(sortedWord.begin(), sortedWord.end());
    if (dict.find(sortedWord) == dict.end()) {//if the key doesn't exist
        return vector<string>();
    } else {//if the key already exists
        return dict.at(sortedWord);//return the vector of strings
    }
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> allAnagrams;
    for(auto it = dict.begin(); it != dict.end(); ++it) {
        if(it->second.size() > 1) {
            allAnagrams.push_back(it->second);
        }
    }
    return allAnagrams;
}
