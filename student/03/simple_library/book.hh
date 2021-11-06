#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include <date.hh>
using namespace std;
class Book
{
public:
    Book();
    Book(string writer, string book_name);
    ~Book();
    void print();
    void loan(Date lainauspaiva);
    void renew();
    void give_back();


private:
    string writer_;
    string book_name_;
    Date when_loaned_;
    Date return_day_;
    bool loaned_ = false;


};

#endif // BOOK_HH
