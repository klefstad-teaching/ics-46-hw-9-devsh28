#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error for words: \"" << word1 << "\", \"" << word2 << "\" -> " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.size() - (int)str2.size()) > d) return false;
    if (str1.size() == str2.size()) {
        int mismatch_count = 0;
        for (size_t i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                mismatch_count++;
                if (mismatch_count > d) return false;
            }
        }
        return true;
    } else {
        const string& longer = (str1.size() > str2.size()) ? str1 : str2;
        const string& shorter = (str1.size() > str2.size()) ? str2 : str1;
        size_t i = 0, j = 0;
        int skip_count = 0;
        while (i < longer.size() && j < shorter.size()) {
            if (longer[i] != shorter[j]) {
                skip_count++;
                if (skip_count > 1) return false;
                i++;
            } else {
                i++; j++;
            }
        }
        return true;
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> get_neighbors(const string &word, const set<string> &word_list) {
    set<string> neighbor_set;
    string candidate;
    for (size_t i = 0; i < word.size(); i++) {
        candidate = word;
        for (char c = 'a'; c <= 'z'; c++) {
            if (candidate[i] == c) continue;
            candidate[i] = c;
            if (word_list.find(candidate) != word_list.end())
                neighbor_set.insert(candidate);
        }
    }
    for (size_t i = 0; i <= word.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            candidate = word;
            candidate.insert(candidate.begin() + i, c);
            if (word_list.find(candidate) != word_list.end())
                neighbor_set.insert(candidate);
        }
    }
    if (!word.empty()) {
        for (size_t i = 0; i < word.size(); i++) {
            candidate = word;
            candidate.erase(candidate.begin() + i);
            if (word_list.find(candidate) != word_list.end())
                neighbor_set.insert(candidate);
        }
    }
    vector<string> neighbors(neighbor_set.begin(), neighbor_set.end());
    return neighbors;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    queue<vector<string>> ladders;
    vector<string> start_ladder;
    start_ladder.push_back(begin_word);
    ladders.push(start_ladder);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladders.empty()) {
        vector<string> current_ladder = ladders.front();
        ladders.pop();
        string last_word = current_ladder.back();
        vector<string> neighbors = get_neighbors(last_word, word_list);
        for (const auto &neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(neighbor);
                if (neighbor == end_word)
                    return new_ladder;
                ladders.push(new_ladder);
                visited.insert(neighbor);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    if (!infile.is_open()) {
        cerr << "Could not open " << file_name << endl;
        return;
    }
    string word;
    while (infile >> word) {
        word_list.insert(word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << " ";
    }
    cout << "\n";
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    if (generate_word_ladder("cat", "dog", word_list).size() != 4)
        error("cat", "dog", "Ladder size not 4");
    if (generate_word_ladder("marty", "curls", word_list).size() != 6)
        error("marty", "curls", "Ladder size not 6");
    if (generate_word_ladder("code", "data", word_list).size() != 6)
        error("code", "data", "Ladder size not 6");
    if (generate_word_ladder("work", "play", word_list).size() != 6)
        error("work", "play", "Ladder size not 6");
    if (generate_word_ladder("sleep", "awake", word_list).size() != 8)
        error("sleep", "awake", "Ladder size not 8");
    if (generate_word_ladder("car", "cheat", word_list).size() != 4)
        error("car", "cheat", "Ladder size not 4");
}
