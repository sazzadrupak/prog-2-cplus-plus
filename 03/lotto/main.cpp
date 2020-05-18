#include <iostream>

using namespace std;

int user_input( string message );
unsigned long int factorial( int number );
void lotto( int number1, int number2 );

int main()
{
    int num_of_lottery_balls , num_of_drawn_balls = 0;
    num_of_lottery_balls = user_input("Enter the total number of lottery balls: ");

    num_of_drawn_balls = user_input("Enter the number of drawn balls: ");

    if(num_of_lottery_balls < 0 || num_of_drawn_balls < 0){
        cout << "The number of balls must be a positive number." << endl;
    } else if(num_of_drawn_balls > num_of_lottery_balls){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else {
        lotto(num_of_lottery_balls, num_of_drawn_balls);
    }
    return 0;
}

int user_input( string message ){
    int number;
    cout << message;
    cin >> number;
    return number;
}

unsigned long int factorial(int number){
    if(number > 0){
        return number * factorial(number - 1);
    } else {
        return 1;
    }
}

void lotto( int number1, int number2 ){
    unsigned long int probability;
    int number3 = number1 - number2;

    probability = factorial(number1) / (factorial(number3) * factorial(number2));
    cout << "The probability of guessing all "<< number2 <<" balls correctly is 1/" << probability << endl;
}
