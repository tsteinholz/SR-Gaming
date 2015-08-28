// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#include <iostream>

using namespace std;

int main()
{
    
    int nums[3] = {0,0,0};

    for (int i = 0; i < 3; i++)
    {
        cin >> nums[i];
    }

    for (int i = 0; i < 3; i++)
    {
        cout << "  -" <<  nums[i] << endl;
    }

    cout << "Sums: " << nums[0] + nums[1] + nums[2] << endl;
    cout << "Multiplied: " << nums[0] * nums[1] * nums[2] << endl;

    int smallest = nums[0], largest = nums[0];

    for (int i = 0; i < 3; i++)
    {
        smallest = nums[i] < smallest ? nums[i] : smallest;
        largest =  nums[i] > largest  ? nums[i] : largest;
    }

    cout << "Smallest Number: " << smallest << endl;
    cout << "Largest Number: " << largest << endl;
    cout << "Range: " << largest - smallest << endl;
    cout << "Mod of the Greatest and the Least: " << largest % smallest << endl;

#ifdef _WIN32
    system("pause");
#else
    //unix n stuff
#endif

    return 0;
}

/*
    Sample Output:
    
    5
    6
    4
    -5
    -6
    -4
    Sums: 15
    Multiplied: 120
    Smallest Number: 4
    Largest Number: 6
    Range: 2
    Mod of the Greatest and the Least: 2
    Press any key to continue . . .
*/