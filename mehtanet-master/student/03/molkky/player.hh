#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

using namespace std;
class Player {
    public:
        Player(string name);
        string get_name() const;
        int get_points() const;
        bool has_won() const;
        void add_points(int pts);
    private:
        string name_;
        int points_ = 0;

};

#endif // PLAYER_HH
