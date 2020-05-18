#include <iostream>

// Write here a function counting the mean value

int main()
{
    int count = 1;
    int sum_of_value = 0;
    int number;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    std::cin >> number;

    if (number <= 0){
        std::cout << "Cannot count mean value from " << number << " numbers"<<std::endl;
    }
    else {
        int value;
        while (count <= number) {
            std::cout << "Input " << count << ". " << "number: ";
            std::cin >> value;
            sum_of_value += value;
            count++;
        }
        float mean_value = static_cast<float>(sum_of_value) / number;
        std::cout << "Mean value of the given numbers is " << mean_value << std::endl;
    }
    return 0;
}
