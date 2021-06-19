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
    case CLEAR:
      console_handle_.ClearHighlight();
      break;
    case MOVE:

      game_[user_input.data[1]] = game_[user_input.data[0]]->Clone();

      delete game_[user_input.data[0]];
      game_[user_input.data[0]] = new Piece();

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

      game_[user_input.data[0]] = new Piece();
      console_handle_.UpdateDisplay(game_);

      break;
    case DELL_ALL:
      for (int i = 0; i < 64; i++)
        game_[i] = new Piece();

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
  console_handle_.SetMessage(
      L"help is coming\n"
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
    std::wstring message = L"";
  for (int i = 0; i < 64; i++) {

    game_.GetElement(i).GenMoves(game_.plane_, i, move_buffer);

    for (auto &move : move_buffer) {
      if (move) {
        message += (std::wstring)move;
        message += L"\n";
        console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                           col::LIGHT_AQUA);
      }
    }
  }
    console_handle_.SetMessage(message);
}
void Admin::AddPiece(full_command input) {

  switch (input.data[1]) {
  case 'p':
    game_[input.data[0]] = new Pawn(input.data[2]);
    break;
  case 'n':
    game_[input.data[0]] = new Night(input.data[2]);
    break;
  case 'b':
    game_[input.data[0]] = new Bishop(input.data[2]);
    break;
  case 'r':
    game_[input.data[0]] = new Rook(input.data[2]);
    break;
  case 'q':
    game_[input.data[0]] = new Queen(input.data[2]);
    break;
  case 'k':
    game_[input.data[0]] = new King(input.data[2]);
    break;
  }
}
void Admin::ShowPossible(int position) {
  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  std::array<Move, 27> move_buffer;

  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);
  std::wstring message;

  for (auto &move : move_buffer) {
    if (move) {
      message += (std::wstring)move;
      message += L"\n";
      console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8, col::LIGHT_AQUA);
    }
  }
  console_handle_.SetMessage(message);
}
