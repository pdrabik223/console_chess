//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_MOVE_H
#define CONSOLE_CHESS_MOVE_H


#include <string>

class move {
public:
    move() : from(0), to(0), evaluation(0.0) {};

    move(int from, int to, double evaluation) : from(from), to(to), evaluation(evaluation) {};
   // move(unsigned from, unsigned to, double evaluation) : from(from), to(to), evaluation(evaluation) {};

    move(int from, int to) : from(from), to(to), evaluation(0.0) {}
   // move(unsigned from, unsigned to) : from(from), to(to), evaluation(0.0) {}


    /// \brief
    /// valid move is only that witch moves somewhere
    /// \return true if the move can be made, note that it doesn't check if the move is inside board
    explicit operator bool() const { return from != to; }

    explicit operator std::string() const {
        std::string temp =  "from:\t";
        temp+= std::to_string(from);
        temp+= " to:\t";
        temp+= std::to_string(to);
        temp+= " evaluation:\t";
        temp+= std::to_string(evaluation);
        return temp;
    }

    /// \note fields of the class are public!
    int from;
    int to;
    double evaluation;


};

class promote:public move{


    char promotion;

};
// these we'll do later
// todo derive en_passant
// todo derive castle
// todo promote
#endif //CONSOLE_CHESS_MOVE_H
