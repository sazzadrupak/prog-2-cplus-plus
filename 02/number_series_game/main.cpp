#include <iostream>


int main()
{
    int number;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> number;

    for(int i = 1; i<=number; i++){
        if((i % 3) == 0 && (i % 7) == 0){
            std::cout << "zip boing" << std::endl;
        } else if ((i % 7) == 0) {
            std::cout << "boing" << std::endl;
        } else if((i % 3) == 0){
            std::cout << "zip" << std::endl;
        } else {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
