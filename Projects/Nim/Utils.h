// Thomas Alexander Steinholz
// South River High School
// C++ w/ Gaming : 1A

#ifndef MASTERMINE_UTILS_H
#define MASTERMINE_UTILS_H

#include <iostream>
#include <string>

namespace SRHSCode
{
    struct Utils
    {
        void prompt(const std::string& s)
        {
            std::cout << s << " : ";
        }

        template<typename T>
        void prompt(const std::string& s, T& t)
        {
            prompt(s);
            std::cin >> t;
        }

        void prompt(const std::string& s, std::string& str)
        {
            prompt(s);
            std::getline(std::cin, str);
        }

    };
}

#endif //MASTERMINE_UTILS_H
