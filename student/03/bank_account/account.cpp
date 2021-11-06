#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();


}

void Account::print() const
{

    std::cout<<owner_<<" : "<<iban_<<" : "<<balance_<<" euros"<< std::endl;
}

void Account::set_credit_limit(int limit)
{
    if(has_credit_){
    credit_limit_ = limit;
    }
    else{
        std::cout<<"Cannot set credit limit: the account has no credit card"<<std::endl;
        return;
    }
}

void Account::save_money(int amount)
{
    balance_ += amount;
}

void Account::take_money(int withdrawal_amount)
{
    if(balance_ > withdrawal_amount){
        balance_ -= withdrawal_amount;
        std::cout<<withdrawal_amount<<" euros taken: newbalance of "<<iban_<<" is "<<balance_<<" euros"<<std::endl;
    }
    else if(has_credit_){
        balance_ -= withdrawal_amount;
    }
    else{
        std::cout<<"Cannot take money : balance underflow"<<std::endl;
        return;
    }
}

void Account::transfer_to(Account& account, int transfer_amount)
{




    if(balance_>transfer_amount){
        balance_ -= transfer_amount;
        account.save_money(transfer_amount);
        std::cout<<transfer_amount<<" euros taken: new balance of "<< iban_<<" is "<<balance_<<" euros "<<std::endl;

    }
    else if( has_credit_){
        if((balance_ + credit_limit_) > transfer_amount){
            balance_ -= transfer_amount;
            std::cout<<transfer_amount<<" euros taken: new balance of "<<iban_<<" is "<<balance_<<std::endl;
            account.save_money(transfer_amount);
        }
        else{
            std::cout<<"Cannot take money: credit limit overflow"<<std::endl;
            std::cout<<"Transfer from "<< iban_<<" failed"<<std::endl;
            return;
        }
    }
    else{
        std::cout<<"Cannot take money: balance underflow"<<std::endl;
        std::cout<<"Transfer from"<<iban_<<" failed "<<std::endl;

    }





}

std::string Account::get_name() const
{
    return owner_;
}

int Account::get_balance() const
{
    return balance_;
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}


