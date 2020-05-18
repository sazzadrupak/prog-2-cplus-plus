#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number,
            result;
    std::cout << "Enter a number: ";
    std::cin >> number;
    result = pow(number, 3);
    if (result < number){
        std::cout << "TError! The cube of " << number << " is not " << result << "." << std::endl;
    } else {
        std::cout << "The cube of " << number <<" is " << result << "." << std::endl;
    }
    return 0;
}
