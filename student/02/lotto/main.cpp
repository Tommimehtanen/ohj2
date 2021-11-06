#include <iostream>

using namespace std;




int permutations (int lottery_balls, int drawn_balls)
{
    int ans = 1;
    if (drawn_balls > lottery_balls - drawn_balls)
       drawn_balls = lottery_balls - drawn_balls;
    for (int i = 0; i < drawn_balls; i++)
    {
        ans *= (lottery_balls-i);
        ans /= (i +1);
    }
    return ans;

}





int main()
{
    int lottery_balls = 0;
    int drawn_balls = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> lottery_balls ;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls ;
    if ((lottery_balls <= 0) || drawn_balls <= 0)
    {
        cout << "The number of balls must be a positive number.";
    }
    else if (drawn_balls > lottery_balls)
    {

        cout << "The maximum number of drawn balls is the total amount of balls.";
    }
    else
        cout << "The probability of guessing all " << drawn_balls <<" balls correctly is 1/" << permutations(lottery_balls, drawn_balls);
    return 0;
}
