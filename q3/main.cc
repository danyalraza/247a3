#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <random>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

using namespace std;

bool alreadyGuessed(vector<char> guessed, char c) {
    return find(guessed.begin(), guessed.end(), c) != guessed.end();
}

bool gotWord(vector<char> guessed, string word) {
  int count = count_if(word.begin(), word.end(), [guessed](char c) {
    return alreadyGuessed(guessed, c);
  });
  if (count == word.size()) return true;
  return false;
}

bool correctGuess(vector<char> guessed, string word, char c) {
  bool correct = (find(word.begin(), word.end(), tolower(c)) != word.end() && find(word.begin(), word.end(), toupper(c)) != word.end());
  return correct;
}

int main(int argc, char* argv[]) {
    string filename;
    int seed = 0;
    if (argc > 1) {
        filename = string(argv[1]);
    } else {
        cout << "Error: No input file specified." << endl;
        return -1;
    }
    if (argc >= 3) {
      seed = atoi(argv[2]);
      mt19937 random(seed);
    }
      // Read words from file into vector
    ifstream inFile(filename);
    if (!inFile) {
      cout << "Error: Could not open file \"" << filename << "\"." << endl;
      return -1;
    }
    istream_iterator<string> in_iter(inFile);
    istream_iterator<string> eof;
    vector<string> unfiltered(in_iter, eof);
    vector<string> words;
    inFile.close();

    // Filter words
    remove_copy_if(unfiltered.begin(), unfiltered.end(), back_inserter(words),
        [](string &word) -> bool {
            bool nonalpha = find_if(word.begin(), word.end(), [](char c) {return !isalpha(c);}) != word.end();
            return (word.length() < 6 || nonalpha);
    });
    if (words.size() == 0) {
        cout << "Error: Pool of game words is empty." << endl;
        return -1;
    }
    ofstream outFile("gamewords");
    ostream_iterator<string> out_iter(outFile, "\n");
    copy(words.begin(), words.end(), out_iter);
    outFile.close();

    while (true) {
      vector<char> guessed;
      int guesses_remaining = 5;
      string word = words[random() % words.size()];

      while (guesses_remaining >= 1) {
        string remaining;
        cout << "Word: ";
        remaining = accumulate(word.begin(), word.end(), string(), [guessed](string &remaining, char c) {
          if (alreadyGuessed(guessed, tolower(c)) || alreadyGuessed(guessed, toupper(c))) {
            remaining.push_back(c);
          }
          else {
            remaining.push_back('-');
          }
          return remaining;
        });
        cout << remaining << endl;

        cout << "Letters used: ";
        ostream_iterator<char> out_iter(cout, " ");
        copy(guessed.begin(), guessed.end(), out_iter);
        cout << endl;

        if (guesses_remaining == 1) {
          cout << "You have 1 life left." << endl;
        }
        else {
          cout << "You have " << guesses_remaining << " lives left." << endl;
        }

        cout << "Next guess: ";
        string guess;
        cin >> guess;

        if (guess.length() > 1) {
          if (guess == word) {
            cout << "You WIN!";
          }
          else {
            cout << "You LOSE!  The word was \"" << word << "\".\n";
          }
          break;
        }
        else {
          char letter = tolower(guess[0]);
          if (alreadyGuessed(guessed, letter)) {
            cout << "You have already guessed letter \"" << letter << "\".\n";
          }
          else {
            guessed.push_back(letter);
            bool correct = correctGuess(guessed, word, letter);
            cout << correct << endl;
            if (correct) {
              bool finished = gotWord(guessed, word);
              cout << finished << endl;
              if (finished) {
                cout << "You WIN!  The word was \"" << word << "\".\n";
                break;
              }
            }
            else {
              --guesses_remaining;
            }
          }
        }

        if (guesses_remaining == 0) {
          cout << "You LOSE!  The word was \"" << word << "\".\n";
          break;
        }
      }
      char ans;
      cout << "Do you want to play again? [Y/N] ";
      cin >> ans;
      if (toupper(ans) != 'Y') break;
  }
  return 0;
}
