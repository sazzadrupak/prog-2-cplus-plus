#include <iostream>

using namespace std;
const int ARRAY_SIZE = 200;

int* populate_array_with_values(int upper_bound, int * value_array);
void print_array_with_values(int * value_array, int upper_bound);
bool check_prime(int  number, int count);

int main()
{
    int value_array[ARRAY_SIZE];
    int upper_bound;
    std::cout << "Enter an upper bound: ";
    std::cin>>upper_bound;

    int * p;
    p = populate_array_with_values(upper_bound, value_array);
    print_array_with_values(p, upper_bound);
    return 0;
}

int* populate_array_with_values(int upper_bound, int * value_array){
    for (int i = 0; i <= upper_bound; i++) {
        int count = 0;
        if(i == 0 || i == 1){
            value_array[i] = false;
        } else {
            value_array[i] = check_prime(i, count);
        }
    }
    return value_array;
}

bool check_prime(int num, int count){
    for(int j = 2; j <= num/2; j++){
        if(num%j == 0){
            count++;
            break;
        }
    }
    if(count == 0 && num != 1)
        return true;
    return false;
}

void print_array_with_values(int *value_array, int upper_bound){
    std::cout<<"Prime numbers smaller than "<<upper_bound<<":"<<std::endl;
    for (int i = 2; i <= upper_bound; i++){
        if(*(value_array + i) == true){
            std::cout << i <<" ";
        }
    }
    std::cout<<std::endl;
}
