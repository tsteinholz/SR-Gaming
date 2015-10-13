// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name = "";
    int age = 0;

    cout << "Hello! What's your name?" << endl;
    getline(cin, name);
    cout << "Ohh " << name << "! What a beautiful name!" << endl;
    cout << "How old are you then " << name << "??" << endl;
    cin >> age;

    if (age < 1 || age > 130)
    { 
        cout << "WOW! You're " << age << " years old and you know how a computer works!?" << endl; 
    }
    else if (age < 13)
    {
        cout << "Oh " << age << ", you're still a child!" << endl;
    }
    else if (age < 20)
    {
        cout << "Ahh " << age << ", I loved my teenage years!" << endl;
    }
    else if (age < 31)
    {
        cout << age << "!? Very nice! You're a good aged young adult!" << endl;
    }
    else if (age < 66)
    {
            cout << "Ahh " << age << ", a hard-working adult!" << endl;
    }
    else
    {
        cout << "You're " << age << "!? You don't look like it!? You must be retired!" << endl;
    }

// Windows only call so...
#ifdef _WIN32
    system("pause");
#else
    // alternitive for unix based systems
#endif

    return 0;
}