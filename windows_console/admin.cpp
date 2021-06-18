//
// Created by studio25 on 18.06.2021.
//

#include "admin.h"

int ChessToInt(std::string coord) {

  switch (coord[0]) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
    return (B_HEIGHT - coord[1] + 1) * B_HEIGHT + coord[3] - 1;
  default:
    return -1;
  }
}

Admin::Admin() : game_(), console_handle_() {

  console_handle_.UpdateDisplay(game_);
  full_command user_input;

  while (1 < 2) {
    console_handle_.UpdateScreen();
    std::cin >> user_input;
    switch (user_input.comm) {
    case QUIT:
      goto quit;

    case MOVE:
      game_[user_input.data[1]] = game_[user_input.data[0]];
      game_[user_input.data[1]] = Piece();
      break;
    case ADD_PIECE:
      AddPiece(user_input);
      break;
    case ADD_ALL:
      game_ = ChessBoard();
      break;
    case DELETE_PIECE:
      game_[user_input.data[0]] = Piece();
      break;
    case DELL_ALL:
      for (int i = 0; i < 64; i++)
        game_[i] = Piece();
      break;
    case SHOW_MOVES:

      break;
    case SHOW_POSSIBLE:
      ShowPossible();
      break;
    case HELP:
      Help();
      break;

    case NONE:
      break;
    }
  }

quit:;
}

void Admin::Help() {
  printf("help is coming\n"
         "add [color][piece][position]    : creates new [piece] in "
         "[position]\n"
         "add all                         : returns the chessboard to "
         "original "
         "[position]\n"
         "del [position]                  : removes piece from [position]\n"
         "del all                         : removes all pieces\n"
         "show moves [position]           : shows moves that are possible "
         "to be "
         "made\n"
         "                                  by the piece under [position]\n"
         "quit                            : quit the program\n"
         "move [from][to]                 : moves chosen by "
         "[from] piece to square selected by [to] \n");
}

void Admin::ShowPossible() {

  std::array<Move, 27> move_buffer;
  for (int i = 0; i < 64; i++) {

    game_[i].GenMoves(game_.plane_, i, move_buffer);
    for (auto m : move_buffer)
      std::cout << (std::string)m;
  }
}

void Admin::AddPiece(full_command input) {

  switch (input.data[1]) {
  case 0:
    game_[input.data[2]] = Pawn(input.data[0]);
    break;
  case 1:
    game_[input.data[2]] = Night(input.data[0]);
    break;
  case 2:
    game_[input.data[2]] = Bishop(input.data[0]);
    break;
  case 3:
    game_[input.data[2]] = Rook(input.data[0]);
    break;
  case 4:
    game_[input.data[2]] = Queen(input.data[0]);
    break;
  case 5:
    game_[input.data[2]] = King(input.data[0]);
    break;
  }
}
