#include <cstdlib>
#include <iostream>

using namespace std;

void printState(int something[3])
{
    cout << something[0] << " : " 
         << something[1] << " : "
         << something[2] << endl;
}

int main(int argc, char *argv[])
{
    int rand[3] = {0,0,0};
    
    for (int i = 0; i < 3; i++)
    {
        cin >> rand[i];
    }
    
    printState(rand);
    
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
