#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Load(const string& file, string s[2])
{
    fstream stream(file.c_str(), ios_base::in);
    if (stream.good())
    {
        cout << "Loading " << file << "..." << endl;
        string line; unsigned int x = 0;
        while (getline(stream ,line))
        { if (line.compare("")) { s[x] = line; x++; } }
    }
    else cout << "Unable to load " << file << "..." << endl << endl;
}

void Talent(unsigned int x)
{
    stringstream oss;
    string data[2];
    oss << "talent" << x << ".txt";
    Load(oss.str(), data);
    if (!data[0].compare("")) return;
    cout << oss.str() << ":" << endl;
    cout << "\t~ " << data[0] << endl;
    cout << "\t~ " << data[1] << endl;
    oss.clear();
    cout << "Results : ";
    for (unsigned int i = (unsigned int) data[0].length(); i > 0; i--)
    {
        string temp = data[0].substr(0, i);
        if (data[1].rfind(temp) != string::npos && temp[temp.length()-1] == data[1][data[1].length()-1])
        {
            cout << temp << " " << temp.length() << endl << endl;
            return;
        }
    }
    cout << "0" << endl << endl;
}

int main(int argc, char* argv[])
{
    for (unsigned int x = 1; x < 12; x++)
    { Talent(x); }
    return 0;
}