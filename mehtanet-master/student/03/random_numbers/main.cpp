#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    default_random_engine rand_gen;
    string seed_value;
    string syote = "";
    cout << "Enter a seed value or an empty line: ";
    getline(cin, seed_value);


    if (seed_value == "")
    {
        rand_gen.seed(time(NULL));
    }
    else
    {
        int value = stoi(seed_value);
        rand_gen.seed((value));
    }
    cout <<""<<endl;
    uniform_int_distribution<int> distribution(lower, upper);
    int number = distribution(rand_gen);
    cout <<"Your drawn random number is "<<number<<endl;
    cout << "Press enter to continue or q to quit: ";
    getline(cin, syote);

    while(syote == "")
    {
        cout <<""<<endl;
        uniform_int_distribution<int> distribution(lower, upper);
        int number = distribution(rand_gen);
        cout <<"Your drawn random number is "<<number<<endl;
        cout << "Press enter to continue or q to quit: ";


        getline(cin, syote);



    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    // Reading the line feed, which was left unread by >> operator above.
    // This is necessary since the seed value will be read by getline
    // in the function produce_random_numbers.
    string line_feed = "";
    getline(cin, line_feed);

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
