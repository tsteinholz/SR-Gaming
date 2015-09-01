#include <iostream>
#include <string>

using namespace std;

void prompt(const string& s)
{
    cout << s << " : ";
}

template<typename T>
void prompt(const string& s, T& t)
{
    prompt(s);
    cin >> t;
}

void prompt(const string& s, string& str)
{
    prompt(s);
    getline(cin, str);
}

int main()
{
    // The Variables
    string fName, lName;
    int age, battles;
    double weight, height;

    // Strings
    prompt("First Name", fName);
    prompt("Last Name", lName);

    // Integers
    prompt("Age", age);
    prompt("How many battles you have been in", battles);

    // Doubles
    prompt("Weight", weight);
    prompt("Height", height);

    cout << endl << "All done information gathering!" << endl;
    cout << "Computing Personalized Story..." << endl;
    cout << "Done!" << endl << endl;

    // The Story
    cout << "One day, " << fName << " of the " << lName << " Dynasty had shown up to the battle field." << endl;
    cout << "This dangerous solider stood " << height << "ft tall! Weighing in at an amazing " << weight << "!!" << endl;
    cout << "The opponent was obviously out-matched, " << fName << " has already won " << battles << " battles and was" << endl;
    cout << "no stranger to the battle-field. This is suprising for " << fName << " being only " << age << " years old!" << endl;
    cout << "None the less " << fName << " won the battle as expected! Three cheers for the " << lName << " Dynasty!!" << endl;

    return 0;
}

/*
 * Program I/O
 *
 * First Name : Thomas
 * Last Name : Steinholz
 * Age : 15
 * How many battles you have been in : 69
 * Weight : 524.32
 * Height : 6.1
 *
 * All done information gathering!
 * Computing Personalized Story...
 * Done!
 *
 * One day, Thomas of the Steinholz Dynasty had shown up to the battle field.
 * This dangerous solider stood 6.1ft tall! Weighing in at an amazing 524.32!!
 * The opponent was obviously out-matched, Thomas has already won 69 battles and was
 * no stranger to the battle-field. This is suprising for Thomas being only 15 years old!
 * None the less Thomas won the battle as expected! Three cheers for the Steinholz Dynasty!!
 *
 * Process finished with exit code 0
 *
 */