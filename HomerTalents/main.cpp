#include <iostream>
#include <fstream>

using namespace std;

void Load(const string& file, string s[2])
{
    fstream stream(file, ios_base::in);
    if (stream.good())
    {
        cout << "Loading " << file << "..." << endl;
        string line; unsigned int x = 0;
        while (getline(stream ,line))
        {
            if (line.compare("")) { s[x] = line; x++; }
        }
    }
    else
    {
        cout << "Not loading " << file << "..." << endl;
    }
}

int main()
{
    string s[2];
    Load("talent1.txt", s);
    cout << s[0] << endl;
    cout << s[1] << endl;
    return 0;
}