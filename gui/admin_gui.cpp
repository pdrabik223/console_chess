//
// Created by studio25 on 06.07.2021.
//

#include "admin_gui.h"
AdminGui::AdminGui() : game_(), gui_handle_() {
  gui_handle_.LoadBoard(game_);

  full_command user_input;
  std::string input;

  while (1 < 2) {
    gui_handle_.UpdateScreen();

    getline(std::cin, input);
    user_input.FromString(input);

    switch (user_input.comm) {

    case Task::MOVE:
      game_.DoMove(
          {(unsigned)user_input.data[0], (unsigned)user_input.data[1]});
      gui_handle_.LoadBoard(game_);

      gui_handle_.HighlightSquare(user_input.data[0], GuiColor::YELLOW);
      gui_handle_.HighlightCircle(user_input.data[1], GuiColor::YELLOW);
      break;
    case Task::SHOW_ALL:
      ShowPossible();
      break;
    case Task::SHOW_MOVES:
      ShowPossible(user_input.data[0]);
      break;
    case Task::HELP:
      Help();
      break;
    case Task::QUIT:
      goto quit;
    case Task::ALFA_BETA_MINMAX:
      AlfaBetaMinMax(user_input.data[1], user_input.data[0], 1);
      break;
    case Task::ALFA_BETA_MINMAX_ALL:
      AlfaBetaMinMaxAll(user_input.data[1], user_input.data[0], 1);
      break;
    case Task::EPIC_COMPUTER_FIGHT:
//      MakeEmFight(user_input.data);
      break;
    }
  }
quit:
  gui_handle_.ExitGui();
}


void AdminGui::DisplayMoves(std::vector<Move> &move_buffer, bool color) {
  std::sort(move_buffer.begin(), move_buffer.end());

  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (const auto &move : move_buffer) {
    std::cout << (std::string)move << std::endl;
    if (move == move_buffer.front()) {
      gui_handle_.HighlightSquare(move.from_, GuiColor::RED);
      gui_handle_.HighlightCircle(move.to_, GuiColor::RED, 30);
    } else {
      gui_handle_.HighlightSquare(move.from_, GuiColor::YELLOW);
      gui_handle_.HighlightCircle(move.to_, GuiColor::YELLOW, 30);
    }
  }
}
void AdminGui::DisplayBestMoves(std::vector<Move> &move_buffer, bool color) {
  std::sort(move_buffer.begin(), move_buffer.end());

  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer) {
    if (move == move_buffer.front()) {
      gui_handle_.HighlightSquare(move.from_, GuiColor::RED);
      gui_handle_.HighlightCircle(move.to_, GuiColor::RED, 30);
    } else
      return;
  }
}
void AdminGui::Help() {
  printf("help is coming\n"
      "add [color][piece][position]    : creates new [piece] in "
      "[position]\n"
      "add all                         : returns the chessboard to "
      "original "
      "[position]\n"
      "del [position]                  : removes piece from [position]\n"
      "del all                         : removes all pieces\n"
      "show [position]                 : shows moves that are possible "
      "to be made\n"
      "                                  by the piece under [position]\n"
      "quit                            : quit the program\n"
      "move [from][to]                 : moves chosen by "
      "[from] piece to square selected by [to] \n"
      "minmax all [color][depth]       : minmax\n"
      "minmax [position][depth]        : minmax but with target\n");
}
void AdminGui::ShowPossible(int position) {
  std::vector<Move> move_buffer;

  game_.GetElement(position).GenMoves(game_.plane_, position, move_buffer);
  for (auto &i : move_buffer)
    game_.EvaluateMove(i);

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
}
void AdminGui::ShowPossible() {
  std::vector<Move> white_move_buffer;

  game_.GenAllPossibleMoves(P_WHITE, white_move_buffer);

  for (auto &i : white_move_buffer)
    game_.EvaluateMove(i);

  std::vector<Move> black_move_buffer;
  game_.GenAllPossibleMoves(P_BLACK, black_move_buffer);

  for (auto &i : black_move_buffer)
    game_.EvaluateMove(i);

  printf("white moves count: %ld\n",white_move_buffer.size());

  DisplayMoves(white_move_buffer,P_WHITE);

  printf("black moves count: %ld\n",black_move_buffer.size());
  DisplayMoves(black_move_buffer,P_BLACK);
}

Move AdminGui::AlfaBetaMinMaxAll(int depth, bool color, int threads) {
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

  printf("elapsed time: %lf ms\n",elapsed_time);

  DisplayMoves(move_buffer, color);
  DisplayBestMoves(move_buffer, color); // he sorts move_buffer
  return move_buffer.front();
}

Move AdminGui::AlfaBetaMinMax(int depth, int position, int threads) {
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

  printf("elapsed time: %lf ms\n",elapsed_time);

  DisplayMoves(move_buffer, game_.GetElement(position).Color());
  DisplayBestMoves(move_buffer, game_.GetElement(position).Color());
  return move_buffer.front();
}

