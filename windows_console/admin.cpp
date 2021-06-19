//
// Created by studio25 on 18.06.2021.
//

#include "admin.h"
#include <algorithm>
#include <cassert>

Admin::Admin() : game_(), console_handle_() {

  console_handle_.UpdateDisplay(game_);
  full_command user_input;

  std::vector<std::string> commands;
  //   commands.emplace_back("c7");

  while (1 < 2) {
    console_handle_.UpdateScreen();
    if (!commands.empty()) {
      user_input.FromString(commands.front());
      commands.erase(commands.begin());
    } else
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
    case MINMAX:
      MinMax(user_input.data[1], user_input.data[0]);
      break;
    case MINMAX_ALL:
      MinMaxAll(user_input.data[1], user_input.data[0]);
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
      "[from] piece to square selected by [to] \n"
      "minmax all [color][depth]       : minmax\n"
      "minmax [position][depth]        : minmax but with target\n");
}

void Admin::ShowPossible() {

  std::vector<Move> white_move_buffer;
  game_.GenAllPossibleMoves(P_WHITE, white_move_buffer);
  for (auto &i : white_move_buffer)
    game_.EvaluateMove(i);

  std::sort(white_move_buffer.begin(), white_move_buffer.end());

  std::vector<Move> black_move_buffer;
  game_.GenAllPossibleMoves(P_BLACK, black_move_buffer);
  for (auto &i : black_move_buffer)
    game_.EvaluateMove(i);

  std::sort(black_move_buffer.begin(), black_move_buffer.end());

  std::wstring message = L"";
  message += L" white moves count: ";
  message += std::to_wstring(white_move_buffer.size());
  message += L" \n";

  for (auto &move : white_move_buffer) {

    message += (std::wstring)move;
    message += L"\n";
  }
  message += L" black moves count: ";
  message += std::to_wstring(black_move_buffer.size());
  message += L" \n";

  for (auto &move : black_move_buffer) {

    message += (std::wstring)move;
    message += L"\n";
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
  for (auto &i : move_buffer)
    game_.EvaluateMove(i);

  std::wstring message;
  std::sort(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer){

    message += (std::wstring)move;
    message += L"\n";
    console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                       col::LIGHT_AQUA);
  }
  console_handle_.SetMessage(message);
}
void Admin::MinMax(int depth, int position) {

  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  auto t_1 = std::chrono::steady_clock::now();

  std::vector<Move> move_buffer;
  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);

  for (auto &i : move_buffer)
  i.evaluation_ =   game_.MinMax(i, depth, game_.GetElement(position).Color());


  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  std::wstring message = L"elapsed time: ";
  message += std::to_wstring(elapsed_time);
  message += L" ms\n";

  std::sort(move_buffer.begin(), move_buffer.end());
  for (auto &move : move_buffer) {

    message += (std::wstring)move;
    message += L"\n";
    console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                       col::LIGHT_AQUA);
  }
  console_handle_.SetMessage(message);
}
void Admin::MinMaxAll(int depth, bool color) {

  auto t_1 = std::chrono::steady_clock::now();
  std::vector<Move> move_buffer;
  game_.GenAllPossibleMoves(color, move_buffer);

  for (auto &i : move_buffer)
    i.evaluation_ =  game_.MinMax(i, depth, color);

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  std::wstring message = L"elapsed time: ";
  message += std::to_wstring(elapsed_time);
  message += L" ms\n";

  std::sort(move_buffer.begin(), move_buffer.end());
  for (auto &move : move_buffer) {

    message += (std::wstring)move;
    message += L"\n";
    console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                       col::LIGHT_AQUA);
  }
  console_handle_.SetMessage(message);
}
