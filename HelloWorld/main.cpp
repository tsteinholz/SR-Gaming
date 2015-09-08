// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

// Include the 'iostream' file with this application so that
// we can use the functions like 'cout' from the 'std' namespace.
#include <iostream>

// The main function in C++ that can also take some certain parameters
// that are not at all necessary in this example.
int main()
{
    // This is the line of code used to send the "Hello World!" string
    // to the standard output of the application, this is followed by the
    // endl which is equivilent to sending '\n' through the stream.
    std::cout << "Hello World!" << std::endl;

// This is an if-statment that checks if the '_WIN32' macro is activated
// to see if the running application is running on Windows or not.
#ifdef _WIN32
    // This is the Window's exclusive command to 'pause' the output of the
    // command console.
    system("pause");
#endif

    // You need to return '0' from the main function to exit successfully.
    return 0;
}