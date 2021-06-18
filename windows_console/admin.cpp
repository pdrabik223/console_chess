//
// Created by studio25 on 18.06.2021.
//

#include "admin.h"



Admin::Admin() : game_(), console_handle_() {

  console_handle_.UpdateDisplay(game_);
  full_command user_input;

  while (1 < 2) {
    console_handle_.UpdateScreen();
    user_input.FromString(console_handle_.GetLine());

    switch (user_input.comm) {
    case QUIT:
      goto quit;

    case MOVE:

      game_[user_input.data[1]] = game_[user_input.data[0]];
      game_[user_input.data[1]] = Piece();
      console_handle_.UpdateDisplay(game_);
      break;
    case ADD_PIECE:
      AddPiece(user_input);
      console_handle_.UpdateDisplay(game_);
      break;
    case ADD_ALL:

      game_ = ChessBoard();
      console_handle_.UpdateDisplay(game_);

      break;
    case DELETE_PIECE:

      game_[user_input.data[0]] = Piece();
      console_handle_.UpdateDisplay(game_);

      break;
    case DELL_ALL:
      for (int i = 0; i < 64; i++)
        game_[i] = Piece();
      console_handle_.UpdateDisplay(game_);
      break;
    case SHOW_MOVES:
      ShowPossible(user_input.data[0]);
      break;
    case SHOW_ALL:
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
  console_handle_.SetMessage(L"help is coming\n"
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
void Admin::ShowPossible(int position) {
  std::array<Move, 27> move_buffer;
  game_[position].GenMoves(game_.plane_, position, move_buffer);
  for (auto m : move_buffer) {
    std::cout << (std::string)m;
    console_handle_.SetBackgroundColor(m.to_ / 8, m.to_ % 8, col::LIGHT_AQUA);
  }

}
