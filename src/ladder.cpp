#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error for words: \"" << word1 << "\", \"" << word2 << "\" -> " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.size() - (int)str2.size()) > d) {
        return false;
    }

    // Case 1: Same length -> check if they differ by at most one character.
    if (str1.size() == str2.size()) {
        int mismatch_count = 0;
        for (size_t i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                mismatch_count++;
                if (mismatch_count > d) return false;
            }
        }
        return (mismatch_count <= d);
    }
    // Case 2: Length differs by 1 -> check if one can be obtained by inserting/deleting 1 char.
    else {
        const string& longer  = (str1.size() > str2.size()) ? str1 : str2;
        const string& shorter = (str1.size() > str2.size()) ? str2 : str1;

        size_t i = 0, j = 0;
        int skip_count = 0;
        while (i < longer.size() && j < shorter.size()) {
            if (longer[i] != shorter[j]) {
                skip_count++;
                if (skip_count > 1) return false;
                i++;
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word,
                                    const set<string>& word_list) {
    // Quick check: if begin == end, no valid ladder by assignment requirement.
    if (begin_word == end_word) {
        return {};
    }

    queue<vector<string>> ladders;
    vector<string> start_ladder;
    start_ladder.push_back(begin_word);
    ladders.push(start_ladder);
    set<string> visited;
    visited.insert(begin_word);

    // BFS
    while (!ladders.empty()) {
        vector<string> current_ladder = ladders.front();
        ladders.pop();

        // The last word in the current ladder
        string last_word = current_ladder.back();

        for (const auto& dict_word : word_list) {
            if (visited.find(dict_word) == visited.end() &&
                is_adjacent(last_word, dict_word)) {

                // Create a new ladder with this neighbor appended
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(dict_word);

                if (dict_word == end_word) {
                    return new_ladder;
                }

                // Otherwise, enqueue the new ladder for further exploration
                ladders.push(new_ladder);

                visited.insert(dict_word);
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
        cout << "No ladder found." << endl;
        return;
    }
    // Example printing: "cat -> cot -> dot -> dog"
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i + 1 < ladder.size()) cout << " -> ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    // We expect 4 steps: cat -> ... -> dog
    my_assert(generate_word_ladder("cat",   "dog",   word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code",  "data",  word_list).size() == 6);
    my_assert(generate_word_ladder("work",  "play",  word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car",   "cheat", word_list).size() == 4);
}
