//
// Created by studio25 on 06.07.2021.
//

#include "admin_gui.h"
AdminGui::AdminGui() : game_(), gui_handle_() {
  gui_handle_.LoadBoard(game_);
  gui_handle_.UpdateScreen();
  full_command user_input;
  std::string input;

  while (1 < 2) {
    getline(std::cin, input);
    user_input.FromString(input);

    switch (user_input.comm) {

    case Task::MOVE:
      game_.DoMove(
          {(unsigned)user_input.data[0], (unsigned)user_input.data[1]});
      gui_handle_.LoadBoard(game_);

      gui_handle_.HighlightCircle(user_input.data[0], GuiColor::YELLOW, 30);
      gui_handle_.HighlightCircle(user_input.data[1], GuiColor::YELLOW, 30);

      gui_handle_.UpdateScreen();
      break;

    case Task::QUIT:
      goto quit;
    }
  }
quit:
  gui_handle_.ExitGui();
}

Move AdminGui::MinMaxAll(int depth, bool color, int threads) {
  auto t_1 = std::chrono::steady_clock::now();
  std::vector<Move> move_buffer;
  game_.GenAllPossibleMoves(color, move_buffer);

  //  DisplayMoves(move_buffer);

  for (auto &i : move_buffer) {
    ChessBoard i_board(game_);
    game_.TransposeChessboard(i_board, i);
    i.evaluation_ = game_.MinMax(i_board, depth, color);
  }

  double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t_1)
                            .count();

  std::cout << "elapsed time: ";
  std::cout << std::to_string(elapsed_time) << " ms\n";

  // DisplayBestMoves(move_buffer); // he sorts move_buffer
  return move_buffer.front();
}
void AdminGui::DisplayMoves(std::vector<Move> &move_buffer, bool color) {
  std::sort(move_buffer.begin(), move_buffer.end());

  if (color)
    std::reverse(move_buffer.begin(), move_buffer.end());

  for (auto &move : move_buffer) {
    if (move == move_buffer.front()) {
      gui_handle_.HighlightCircle(move.from_, GuiColor::RED, 30);
      gui_handle_.HighlightCircle(move.to_, GuiColor::RED, 30);
    } else {
      gui_handle_.HighlightCircle(move.from_, GuiColor::YELLOW, 30);
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
      gui_handle_.HighlightCircle(move.from_, GuiColor::RED, 30);
      gui_handle_.HighlightCircle(move.to_, GuiColor::RED, 30);
    } else
      return;
  }
}
