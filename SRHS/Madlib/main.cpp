#include <iostream>
#include <string>

using namespace std;

void prompt(const string& s, int& i)
{
    cout << s << endl;
    cin >> i;
}

void prompt(const string& s, string& str)
{
    cout << s << endl;
    getline(cin, str);
}

void prompt(const string& s, double& d)
{
    cout << s << endl;
    cin >> d;
}

int main()
{
    string name;
    int test = 0;
    prompt("insert nums: ", test);

    /*
     * I'll never forget that  I went poaching with Tam. The  was so thick, you'd've needed four pairs of  to see anything.
     * There was nothing to be heard, save the water running in the . Suddenly there was a noise from above us. What a
     * I got! I thought I was going to  my  . "Haud yer  " Tam hissed, "It's just a ". We crept on and I was glad I had
     * my  on, for the  were everywhere. "Who's there?" came a voice from ahead. "Run!" said Tam, as he . "It's the !".
     * I took off in the other direction and ran straight into the  I was absolutely through to my  and up to my  in water.
     * Fortunately, the  was going after Tam, so I managed to get away. I began to  home, absolutely , and took off my wet
     * before having a . Never again, I thought.
     */
    return 0;
}