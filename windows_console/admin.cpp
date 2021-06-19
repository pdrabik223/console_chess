//
// Created by studio25 on 18.06.2021.
//

#include "admin.h"
#include <cassert>

Admin::Admin() : game_(), console_handle_() {

  console_handle_.UpdateDisplay(game_);
  full_command user_input;
  int counter = 0;

  int position_x = rand() % 8;
  int position_y = rand() % 8 + 1;

  std::string random_position = "";
  random_position.push_back((char)('a' + position_x));
  random_position += std::to_string(position_y);

  int piece = rand() % 12 + 1;


  std::string random_piece;
  switch (piece) {
  case 1:
    random_piece = "p";
    break;
  case 2:
    random_piece = "n";
    break;
  case 3:
    random_piece = "b";
    break;
  case 4:
    random_piece = "r";
    break;
  case 5:
    random_piece = "q";
    break;
  case 6:
    random_piece = "k";
    break;
  case 7:
    random_piece = "P";
    break;
  case 8:
    random_piece = "N";
    break;
  case 9:
    random_piece = "B";
    break;
  case 10:
    random_piece = "R";
    break;
  case 11:
    random_piece = "Q";
    break;
  case 12:
    random_piece = "K";
    break;
  default:
    assert(false);
  }

  std::vector<std::string> to_start_with;
  std::string complete_message = random_position + " " + random_piece;
  std::string add = "add " + complete_message;
  std::string show = complete_message;

  // to_start_with.push_back("del all");
  to_start_with.push_back(add);
  to_start_with.push_back(show);

  while (1 < 2) {
    console_handle_.UpdateScreen();

    if (counter >= to_start_with.size()) {
      goto quit;
      user_input.FromString(console_handle_.GetLine());
    } else {
      user_input.FromString(to_start_with[counter]);
      counter++;
    }
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

  std::vector<Move> move_buffer;
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
  std::vector<Move> move_buffer;

  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);
  std::wstring message;

  for (auto &move : move_buffer) {
    if (move) {
      message += (std::wstring)move;
      message += L"\n";
      console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                         col::LIGHT_AQUA);
    }
  }
  console_handle_.SetMessage(message);
}
