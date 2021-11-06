#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

enum Slot_type {RED, GREEN, EMPTY, UNUSED};
const unsigned int ROWS = 5;
const unsigned int COLUMS = 4;
unsigned int MOVES = 0;

const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";

// Prints the grid
void print(const vector<vector<Slot_type>>/*vector of vectors or a compatible type*/& g)
{
    cout << "===============" << endl;
    cout << "|   | 1 2 3 4 |" << endl;
    cout << "---------------" << endl;
    for(unsigned int i = 0; i < ROWS; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < COLUMS; ++j)
        {
            switch(g.at(i).at(j))
            {
            case GREEN: cout << "G "; break;
            case RED: cout << "R "; break;
            case EMPTY: cout << "o "; break;
            case UNUSED: cout << "  "; break;
            }
        }
        cout << "|" << endl;
    }
    cout << "===============" << endl;
}

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// More functions


// initializes game_board
//
vector<vector<Slot_type>>initialize_board()
{
    vector<vector<Slot_type>> game_board;
    for (unsigned int i = 0; i <= 4; ++i)
    {
        game_board.push_back({});
        for (unsigned int j = 0; j <= 4; ++j)
        {
            if(i == 0)
            {
            game_board.at(i).push_back(GREEN);
            }
            else if(i == 1 && j == 1)
            {
                game_board.at(i).push_back(EMPTY);
            }
            else if (i == 2 &&  (j == 1 or j == 2))
            {
                game_board.at(i).push_back(EMPTY);
            }
            else if(i == 3 && j == 1)
            {
                game_board.at(i).push_back(EMPTY);
            }
            else if ( i == 4)
            {
                game_board.at(i).push_back(RED);
            }
            else
            {
                game_board.at(i).push_back(UNUSED);
            }
        }
    }
    return game_board;
}


//Turns (x1,y1) point empty and changes value of (x2.y2) into whatever was in (x1,y2)
vector<vector<Slot_type>> make_move(vector<vector<Slot_type>> board, int x1, int y1, int x2, int y2)
{
     board.at(y2-1).at(x2-1) = board.at(y1-1).at(x1-1);
     board.at(y1-1).at(x1-1) = (EMPTY);
     MOVES = MOVES + 1;
     std::cout << "moves made: " << MOVES << std::endl;

     return board;
}


bool check_vertical_path(vector<vector<Slot_type>> board, int x1, int y1, int x2){


    if(x1 > x2){
       /* for (int i = 1; i < ((x1-1)-(x2-1)); ++i){
            Slot_type homo = board.at(y1-i).at(x1);
            std::cout<<homo;
            if(board.at(y2-1).at(i) != EMPTY){
                return false;
            }
            else{
                return true;
            }*/
        for(int i = x1-1; i >= x2-1; --i){
            Slot_type homo = board.at(y1-1).at(i-1);
            std::cout<<homo;
            if(board.at(y1-1).at(i-1) != EMPTY){
                return false;
            }
            else {
                return true;
            }

        }
    }
    if(x2 > x1){
        for (int j = x1-1; j <= (x2-1) ; ++j){
            Slot_type huara = board.at(y1-1).at(j+1);
            std::cout<<huara;
            if(board.at(y1-1).at(j+1) != EMPTY){
                return false;
            }
            else{
                return true;
            }
        }
    }
    return true;



}

bool check_horizontal_path(vector<vector<Slot_type>> board, int x1, int y1, int x2, int y2){

    // liikkuminen alhaala ylös
   
    if(y1 > y2){
        for (int i = y1-1; i > y2; --i){
            Slot_type kalle = board.at(i-1).at(x1-1);
            std::cout<<kalle;
            if(board.at(i-1).at(x1-1) != EMPTY){
                return false;
            }
        }
    }
    //liikkminen ylhäälä alas
    else {
        for(int j = 1; j < (y2-1) -(y1-1); ++j){
            Slot_type pekka = board.at(y1+j-1).at(x1-1);
            std::cout<<pekka;
            if(board.at(y1+j-1).at(x1-1) != EMPTY){
                return false;
            }
        }
    }




    return true;


}
bool check_path(vector<vector<Slot_type>> board, int x1, int y1, int x2, int y2)
{

    //checks vertical path when both cordinates locate in the same row
    if(y1 == y2){
        if(!check_vertical_path(board, x1, y1, x2)){
            return false;
        }
        else{
            return true;
        }

    }
     //checks horizontal path when both cordinates locate in column 2
      if((x1 == 2) and (x2 == 2)) {
        if(!check_horizontal_path(board, x1, y1, x2, y2)){
            return false;
        }
        else{
            return true;
        }

    }
    if(x1 != 2){
    if(board[y1-1][1] != EMPTY){
            return false;
        }
    }
    if(!check_vertical_path(board, x1, y1, 2)){
            return false;
        }


        if(!check_horizontal_path(board, 2, y1, 2, y2)){
            return false;


            if(check_vertical_path(board, 2, y2, x2)){
                return true;
            }
            else{
                return true;

            }
    return true;
}




}




bool check_move(vector<vector<Slot_type>> board, int x1, int y1, int x2, int y2)
{
    // checks if input cordinates are out of board
    if(((x1) > 0) && ((x1) < 5)){
        if(((x2) > 0) && ((x2) < 5)){
            if(((y1) > 0) && ((y1) < 6)){
                if(((y2) > 0) && ((y2) < 6)){
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }


   if ((board.at(y1-1)[x1-1] != (GREEN) && (board.at(y1-1)[x1-1] != (RED))) ){
        return false;
    }
    else if(board.at(y2-1)[x2-1] != (EMPTY)){
        return false;
    }

    else{
        return true;
    }

}


int main()
{
    // More code


    vector<vector<Slot_type>>game_board = initialize_board();
    print(game_board);

    //return 0;


    //asks for input
    while(true) {



        std::cout << INPUT_TEXT;
        std::string commands;
        getline(std::cin, commands);

        std::string numbers = "";

        if (commands == "q"){
            return EXIT_SUCCESS;
        }

        for (auto x : commands)
        {
            if (x != ' '){
                    numbers.push_back(x);
            }
        }


        std::cout << numbers << std::endl;
        if (stoi_with_check(numbers) == 0){
            std::cout << INVALID_POINT << std::endl;
            continue;
        }

        else if (numbers.size() != 4){
            std::cout << INVALID_POINT << std::endl;
            continue;
        }


        int x1 = numbers.at(0) - '0';
        int y1 = numbers.at(1) - '0';
        int x2 = numbers.at(2) - '0';
        int y2 = numbers.at(3) - '0';


        if (check_move(game_board, x1, y1, x2, y2)){
            if(check_path(game_board, x1, y1, x2, y2)){
            game_board = make_move(game_board, x1, y1, x2, y2);
            }
            else{
                std::cout << CANNOT_MOVE << std::endl;
            }
        }
        else{
            std::cout << INVALID_POINT << std::endl;

        }
        print (game_board);
    }
}
