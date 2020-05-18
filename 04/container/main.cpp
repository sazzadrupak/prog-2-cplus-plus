#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, unsigned int count)
{
    int new_integer = 0;
    for(unsigned int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(std::vector< int >& ints, unsigned int length){
    if(length == 0){
        return false;
    } else if (length == 1) {
        return true;
    } else {
        for(unsigned int i = 0; i < length; i++)
        {
            if(ints[i] != ints[0]){
                return false;
            }
        }
        return true;
    }
}

bool is_ordered_ascending(std::vector< int >& ints, unsigned int length){
    if(length == 0){
        return false;
    } else if (length == 1) {
        return true;
    } else {
        for (unsigned int i = 0; i < length - 1; i++) {
            if(ints[i] > ints[i + 1]){
            return false;
            }
        }
        return true;
    }
}

bool is_arithmetic_series(std::vector< int >& ints, unsigned int n){
    if(n == 0){
        return false;
    } else if (n == 1) {
        return true;
    } else {
        unsigned int d = (ints[n - 1] - ints[0]) / (n - 1);
        for (unsigned int i = 0; i < n - 1; i++) {
            if(static_cast<unsigned int>(ints[i + 1] - ints[i]) != d){
                return false;
            }
        }
        return true;
    }
}

bool is_geometric_series(std::vector< int >& ints, unsigned int n){
    if(n == 0){
        return false;
    } else if (n == 1) {
        return true;
    } else {
        int r = ints[1] / ints[0];
        for (unsigned int i = 1; i < n - 1; i++) {
            if(static_cast<int>(ints[i + 1] / ints[i]) != r){
                return false;
            }
        }
        return true;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    std::vector<unsigned int>::size_type number_of_scores = integers.size();
    number_of_scores = integers.size();

    if(same_values(integers, number_of_scores))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_ascending(integers, number_of_scores))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers, number_of_scores))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers, number_of_scores))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
