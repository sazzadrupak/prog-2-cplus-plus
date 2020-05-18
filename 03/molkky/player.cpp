#include "player.hh"
#include <iostream>

Player::Player(string name, int pts): name_(name), pts_(pts)
{

}

string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return pts_;
}

bool Player::has_won() const
{
    if ( pts_ == 50 ){
        return true;
    }
    else{
        return false;
    }
}

void Player::add_points(int new_pts)
{
    pts_ = pts_ + new_pts;
    if(pts_ > 50){
        pts_ = 25;
        std::cout  << name_ << " gets penalty points!" << endl;
    }
}
