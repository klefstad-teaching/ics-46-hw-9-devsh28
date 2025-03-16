#include "ladder.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Load the dictionary of words from words.txt.
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    // Prompt the user for a start word and an end word.
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    // Generate the word ladder using BFS.
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);

    // Output the result.
    if (ladder.empty()) {
        cout << "No ladder found from " << start_word << " to " << end_word << "." << endl;
    } else {
        cout << "Word ladder from " << start_word << " to " << end_word << ":" << endl;
        print_word_ladder(ladder);
    }
    

    return 0;
}
