//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_MOVE_H
#define CONSOLE_CHESS_MOVE_H


class move {
public:
    move() : from(0), to(0), evaluation(0.0) {};

    move(int from, int to, double evaluation) : from(from), to(to), evaluation(evaluation) {};;

    /// \brief
    /// valid move is only that witch moves somewhere
    /// \return true if the move can be made, note that it doesn't check if the move is inside board
    explicit operator bool() const { return from != to; }
    // todo show in console
    // from: \t to: \t evaluaion:


    /// \note fields of the class are public!
    int from;
    int to;
    double evaluation;


    move(int from, int to) : from(from), to(to), evaluation(0.0) {}
};
// todo derive en_passant
// todo derive castle

#endif //CONSOLE_CHESS_MOVE_H
