#ifndef PLAYER_H
#define PLAYER_H
#include <string>

using namespace std;

class Player
{
public:
    Player(string name, int pts = 0);
    string get_name() const;
    int get_points() const;
    bool has_won() const;
    void add_points(int new_pts);

private:
    string name_;
    int pts_;
};

#endif // PLAYER_H
