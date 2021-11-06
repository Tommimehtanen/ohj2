#include <iostream>

using namespace std;


int main() {

    int number1 = 222;
    int number2 = 111;
    int *ptr1 = new int(111);
    int *ptr2 = new int(222);

    cout << number1 << " "
         << number2 << " "
         << *ptr1 << " "
         << *ptr2 << endl;



    *ptr1 = 333;
    delete ptr1;
    delete ptr2;
}
