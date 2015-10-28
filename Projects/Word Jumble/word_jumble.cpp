// Word Jumble
// The classic word jumble game where the player can ask for a hint

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    enum fields {WORD, HINT, NUM_FIELDS};
    const int NUM_WORDS = 10;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
        {"wall", "Do you feel you're banging your head against something?"},
        {"glasses", "These might help you see the answer."},
        {"labored", "Going slowly, is it?"},
        {"persistent", "Keep at it."},
        {"jumble", "It's what the game is all about."},
        {"thomas", "The person who programmed this."},
        {"computer", "The thing running this program."},
        {"cplusplus", "The programing language we are using."},
        {"southriver", "The school we go to."},
        {"scott", "A crazy little boy."}
    };

  	srand(time(0));
	int choice = (rand() % NUM_WORDS);
    string theWord = WORDS[choice][WORD];  // word to guess
    string theHint = WORDS[choice][HINT];  // hint for word

    string jumble = theWord;  // jumbled version of word
    int length = jumble.size();
    for (int i=0; i<length; ++i)
    {
        int index1 = (rand() % length);
        int index2 = (rand() % length);
        char temp = jumble[index1];
        jumble[index1] = jumble[index2];
        jumble[index2] = temp;
    }

    cout << "\t\t\tWelcome to Word Jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter 'hint' for a hint.\n";
    cout << "Enter 'quit' to quit the game.\n\n";
    cout << "The jumble is: " << jumble;

    string guess;
    cout << "\n\nYour guess: ";
    cin >> guess;

    int points = 0;

    while ((guess != theWord) && (guess != "quit"))
    {
        if (guess == "hint")
        {
            points-=2;
            cout << theHint;
        }
        else
            cout << "Sorry, that's not it.";

        cout <<"\n\nYour guess: ";
        cin >> guess;
    }

    if (guess == theWord)
    {
        points += length*2;
        cout << "\nThat's it!  You guessed it!\n";
    }

    cout << "\nYou earned " << points << " points this game!\n";
    cout << "\nThanks for playing.\n";

    return 0;
}
