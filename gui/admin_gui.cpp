//
// Created by studio25 on 06.07.2021.
//

#include "admin_gui.h"
AdminGui::AdminGui() {}

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
void AdminGui::DisplayBestMoves(std::vector<Move> &move_buffer) {
  for (auto i : move_buffer) {
    gui_handle_.HighlightSquare(i.from_);
    gui_handle_.HighlightSquare(i.to_);
  }
}
