//
// Created by studio25 on 18.06.2021.
//

#include "admin.h"
#include <algorithm>
#include <cassert>
#include <conio.h>

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
    case ALFA_BETA_MINMAX:
      AlfaBetaMinMax(user_input.data[1], user_input.data[0]);
      break;
    case ALFA_BETA_MINMAX_ALL:
      AlfaBetaMinMaxAll(user_input.data[1], user_input.data[0]);
      break;
    case EPIC_COMPUTER_FIGHT:
      MakeEmFight((Task)user_input.data[0],user_input.data[1],(Task)user_input.data[2],user_input.data[3]);
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

  console_handle_.message_ += L" white moves count: ";
  console_handle_.message_ += std::to_wstring(white_move_buffer.size());
  console_handle_.message_ += L" \n";

  for (auto &move : white_move_buffer) {

    console_handle_.message_ += (std::wstring)move;
    console_handle_.message_ += L"\n";
  }

  console_handle_.message_ += L" black moves count: ";
  console_handle_.message_ += std::to_wstring(black_move_buffer.size());
  console_handle_.message_ += L" \n";

  for (auto &move : black_move_buffer) {

    console_handle_.message_ += (std::wstring)move;
    console_handle_.message_ += L"\n";
  }
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

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
}

void Admin::MinMax(int depth, int position) {

  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  auto t_1 = std::chrono::steady_clock::now();

  std::vector<Move> move_buffer;
  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ =
        game_.MinMax(i_board, depth, game_.GetElement(position).Color());
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time);
  console_handle_.message_ += L" ms\n";

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
  DisplayBestMoves(move_buffer, game_.GetElement(position).Color());
}

Move Admin::MinMaxAll(int depth, bool color) {

  auto t_1 = std::chrono::steady_clock::now();
  std::vector<Move> move_buffer;
  game_.GenAllPossibleMoves(color, move_buffer);

  DisplayMoves(move_buffer, color);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.MinMax(i_board, depth, color);
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time) + L" ms\n";


  std::sort(move_buffer.begin(), move_buffer.end());
  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());
  DisplayBestMoves(move_buffer, color);
  return move_buffer.front();
}

void Admin::MakeEmFight(Task white_algorytm, int white_depth,Task black_algorytm, int black_depth) {

 // white is true
 // black is false

  while (1 < 2) {
    /// white is first
    switch(white_algorytm) {
    case MINMAX:
      game_.DoMove(MinMaxAll(white_depth, true));
      break;
    case ALFA_BETA_MINMAX:
      game_.DoMove(AlfaBetaMinMaxAll(white_depth, true));
      break;
    default:
      break;
    }

    console_handle_.UpdateScreen();
    console_handle_.ClearHighlight();
    console_handle_.UpdateDisplay(game_);

    if (game_.EvaluatePosition() > 900 )
      break;
    /// black is first

    switch(black_algorytm) {
    case MINMAX:
      game_.DoMove(MinMaxAll(black_depth, false));
      break;
    case ALFA_BETA_MINMAX:
      game_.DoMove(AlfaBetaMinMaxAll(black_depth, false));
      break;
    default:
      break;
    }

    console_handle_.UpdateScreen();
    console_handle_.ClearHighlight();
    console_handle_.UpdateDisplay(game_);

    if (game_.EvaluatePosition() > 900 )
      break;


  }
}

Move Admin::AlfaBetaMinMaxAll(int depth, bool color) {
  auto t_1 = std::chrono::steady_clock::now();
  std::vector<Move> move_buffer;
  game_.GenAllPossibleMoves(color, move_buffer);

  DisplayMoves(move_buffer, color);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.AlfaBetaMinMax(i_board,-1000,1000, depth, color);
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - t_1)
      .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time) + L" ms\n";


  std::sort(move_buffer.begin(), move_buffer.end());
  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  DisplayBestMoves(move_buffer, color);
  return move_buffer.front();

}

void Admin::AlfaBetaMinMax(int depth, int position) {

  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  auto t_1 = std::chrono::steady_clock::now();

  std::vector<Move> move_buffer;
  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ =
        game_.AlfaBetaMinMax(i_board, depth,-1000,1000, game_.GetElement(position).Color());
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - t_1)
      .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time);
  console_handle_.message_ += L" ms\n";

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
  DisplayBestMoves(move_buffer, game_.GetElement(position).Color());
}

void Admin::DisplayMoves(std::vector<Move> &move_buffer, bool color) {

  std::sort(move_buffer.begin(), move_buffer.end());

  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer) {

    console_handle_.message_ += (std::wstring)move;
    console_handle_.message_ += L"\n";

     console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8, col::AQUA);
  }
}


void Admin::DisplayBestMoves(std::vector<Move> &move_buffer, bool color) {
  std::sort(move_buffer.begin(), move_buffer.end());

  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer) {

    if (move == move_buffer.front())
      console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                         col::LIGHT_AQUA);
    else return;
  }
}
