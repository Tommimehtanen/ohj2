#include <iostream>
#include "player.hh"
#include <string>
Player::Player(string name):
    name_(name)
{

}

string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return points_;
}
bool Player::has_won() const
{
    if (points_ != 50)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Player::add_points(int pts)
{
    points_ += pts;
    if ( points_ > 50)
    {
        points_ = 25;
        cout << name_ <<" gets penalty points!";
        cout <<endl;
    }
    else
    {
        points_ = points_;
    }
}





