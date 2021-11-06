#include "book.hh"
#include <iostream>
Book::Book()
{

}

Book::Book(string writer, string book_name)
{
    writer_ = writer;
    book_name_ = book_name;
    loaned_ = false;
}
Book::~Book()
{
}

void Book::print()
{
    cout <<writer_<<" : "<<book_name_<<endl;
    if(!loaned_){
        cout<<"- available"<<endl;
    }
    else{
        cout<<"- loaned: ";
        when_loaned_.print();
        cout<<"- to be returned: ";
        return_day_.print();
    }
}

void Book::loan(Date lainauspaiva)
{
    if (loaned_ == true){
        cout<< "Already loaned: cannot be loaned"<<endl;
    }
    else{
        loaned_ = true;

        when_loaned_ = lainauspaiva;
        return_day_ = lainauspaiva;
        return_day_.advance(28);
    }
}

void Book::renew()
{
    if(loaned_){
        return_day_.advance(28);
    }
    else{
        cout<<"Not loaned: cannot be renewed"<<endl;
    }
}

void Book::give_back()
{
    loaned_ = false;
}

