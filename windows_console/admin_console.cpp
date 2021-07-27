//
// Created by studio25 on 18.06.2021.
//

#include "admin_console.h"
#include <algorithm>
#include <cassert>
#include <conio.h>

AdminConsole::AdminConsole() : game_(), console_handle_() {

  console_handle_.UpdateDisplay(game_);
  full_command user_input;

  std::vector<std::string> commands;
  //commands.emplace_back("abminmaxtt all white 3");

  while (1 < 2) {

    console_handle_.UpdateScreen();

    if (!commands.empty()) {
      user_input.FromString(commands.front());
      commands.erase(commands.begin());
    } else
      user_input.FromString(console_handle_.GetLine());

    switch (user_input.comm) {
    case Task::QUIT:
      goto quit;
    case Task::CLEAR:
      console_handle_.ClearHighlight();
      break;
    case Task::MOVE:
      game_.DoMove(
          {(unsigned)user_input.data[0], (unsigned)user_input.data[1]});
      console_handle_.UpdateDisplay(game_);
      break;
    case Task::ADD_PIECE:

      AddPiece(user_input);
      console_handle_.UpdateDisplay(game_);

      break;
    case Task::ADD_ALL:

      game_ = ChessBoard();
      console_handle_.UpdateDisplay(game_);

      break;
    case Task::DELETE_PIECE:

      game_[user_input.data[0]] = new Piece();
      console_handle_.UpdateDisplay(game_);

      break;
    case Task::DELL_ALL:
      for (int i = 0; i < 64; i++)
        game_[i] = new Piece();

      console_handle_.UpdateDisplay(game_);
      break;
    case Task::SHOW_MOVES:
      ShowPossible(user_input.data[0]);
      break;
    case Task::SHOW_ALL:
      ShowPossible();
      break;
    case Task::HELP:
      Help();
      break;

    case Task::LOAD:
      Load();
      console_handle_.UpdateDisplay(game_);
      break;
    case Task::MINMAX:
      MinMax(user_input.data[1], user_input.data[0], 1);
      break;
    case Task::MINMAX_ALL:
      MinMaxAll(user_input.data[1], user_input.data[0], 1);
      break;
    case Task::ALFA_BETA_MINMAX:
      AlfaBetaMinMax(user_input.data[1], user_input.data[0], 1);
      break;
    case Task::ALFA_BETA_MINMAX_ALL:
      AlfaBetaMinMaxAll(user_input.data[1], user_input.data[0], 1);
      break;

    case Task::ALFA_BETA_MINMAX_W_TRANSPOSITION_TABLE_ALL:
      AlfaBetaMinMaxWTranspositionTableAll(user_input.data[1],
                                           user_input.data[0], 1);
      break;
    case Task::ALFA_BETA_MINMAX_W_TRANSPOSITION_TABLE:
      AlfaBetaMinMaxWTranspositionTable(user_input.data[1], user_input.data[0],
                                        1);
      break;

    case Task::EPIC_COMPUTER_FIGHT:
      MakeEmFight(user_input.data);
      break;
    case Task::NONE:
      break;
    }
  }

quit:;
}

void AdminConsole::Help() {
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

void AdminConsole::ShowPossible() {

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

void AdminConsole::AddPiece(full_command input) {

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

void AdminConsole::ShowPossible(int position) {
  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  std::vector<Move> move_buffer;

  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);
  for (auto &i : move_buffer)
    game_.EvaluateMove(i);

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
}

void AdminConsole::MinMax(int depth, int position, int threads) {

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

Move AdminConsole::MinMaxAll(int depth, bool color, int threads) {

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

  DisplayBestMoves(move_buffer, color); // he sorts move_buffer
  return move_buffer.front();
}

void AdminConsole::MakeEmFight(std::vector<int> settings) {

  int white_algorytm = settings[0];
  int black_algorytm = settings[3];

  int white_depth = settings[1];
  int black_depth = settings[4];

  int white_threads = settings[2];
  int black_threads = settings[5];

  // white is true
  // black is false

  while (1 < 2) {
    /// white is first
    switch ((Task)white_algorytm) {
    case Task::MINMAX:
      game_.DoMove(MinMaxAll(white_depth, true, white_threads));
      break;
    case Task::ALFA_BETA_MINMAX:
      game_.DoMove(AlfaBetaMinMaxAll(white_depth, true, white_threads));
      break;
    default:
      break;
    }

    console_handle_.UpdateDisplay(game_);
    console_handle_.UpdateScreen();
    console_handle_.ClearHighlight();

    if (game_.EvaluatePosition() > 900)
      break;

    /// black is second
    console_handle_.GetLine();
    switch ((Task)black_algorytm) {
    case Task::MINMAX:
      game_.DoMove(MinMaxAll(black_depth, false, black_threads));
      break;
    case Task::ALFA_BETA_MINMAX:
      game_.DoMove(AlfaBetaMinMaxAll(black_depth, false, black_threads));
      break;
    default:
      break;
    }

    console_handle_.UpdateDisplay(game_);
    console_handle_.UpdateScreen();
    console_handle_.ClearHighlight();
    console_handle_.GetLine();
    if (game_.EvaluatePosition() < -900)
      break;
  }
}

Move AdminConsole::AlfaBetaMinMaxAll(int depth, bool color, int threads) {
  auto t_1 = std::chrono::steady_clock::now();
  std::vector<Move> move_buffer;
  game_.GenAllPossibleMoves(color, move_buffer);

  DisplayMoves(move_buffer, color);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.AlfaBetaMinMax(i_board, depth, -1000, 1000, color);
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time) + L" ms\n";

  DisplayMoves(move_buffer, color);
  DisplayBestMoves(move_buffer, color); // he sorts move_buffer
  return move_buffer.front();
}

void AdminConsole::AlfaBetaMinMax(int depth, int position, int threads) {

  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  auto t_1 = std::chrono::steady_clock::now();

  std::vector<Move> move_buffer;
  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.AlfaBetaMinMax(i_board, depth, -1000, 1000,
                                         game_.GetElement(position).Color());
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time) + L" ms\n";

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
  DisplayBestMoves(move_buffer, game_.GetElement(position).Color());
}

void AdminConsole::DisplayMoves(std::vector<Move> &move_buffer, bool color) {

  std::sort(move_buffer.begin(), move_buffer.end());

  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer) {

    console_handle_.message_ += (std::wstring)move;
    console_handle_.message_ += L"\n";

    console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8, col::AQUA);
  }
}

void AdminConsole::DisplayBestMoves(std::vector<Move> &move_buffer, bool color) {
  std::sort(move_buffer.begin(), move_buffer.end());
  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer) {

    if (move == move_buffer.front())
      console_handle_.SetBackgroundColor(move.to_ / 8, move.to_ % 8,
                                         col::LIGHT_AQUA);
    else
      return;
  }
}

void AdminConsole::Load() {

  std::string path = "../positions/";
  path += console_handle_.GetLine();
  game_.LoadPosition(path);
}

Move AdminConsole::AlfaBetaMinMaxWTranspositionTableAll(int depth, bool color,
                                                 int threads) {
  auto t_1 = std::chrono::steady_clock::now();
  std::vector<Move> move_buffer;
  game_.GenAllPossibleMoves(color, move_buffer);

  DisplayMoves(move_buffer, color);
  std::map<size_t, double> t_table;

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.AlfaBetaMInMaxTranspositionTable(
        i_board, depth, -1000, 1000, color, t_table);
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time) + L" ms\n";

  DisplayMoves(move_buffer, color);
  DisplayBestMoves(move_buffer, color); // he sorts move_buffer
  return move_buffer.front();
}

void AdminConsole::AlfaBetaMinMaxWTranspositionTable(int depth, int position,
                                              int threads) {
  console_handle_.SetBackgroundColor(position / 8, position % 8,
                                     col::LIGHT_PURPLE);
  auto t_1 = std::chrono::steady_clock::now();

  std::vector<Move> move_buffer;
  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);
  static std::map<size_t, double> t_table;

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.AlfaBetaMInMaxTranspositionTable(
        i_board, depth, -1000, 1000, game_.GetElement(position).Color(),
        t_table);
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  console_handle_.message_ = L"elapsed time: ";
  console_handle_.message_ += std::to_wstring(elapsed_time) + L" ms\n";

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
  DisplayBestMoves(move_buffer, game_.GetElement(position).Color());
}
