
#include "chess_board.h"
#include <cassert>
#include <fstream>
#include <vector>

double &Max(double &x, double &y) {
  if (x > y)
    return x;
  else
    return y;
}
double &Min(double &x, double &y) {
  if (x < y)
    return x;
  else
    return y;
}
double Abs(double &x) {
  if (x < 0)
    return -x;
  else
    return x;
}

size_t Pow(size_t &base, size_t &exp) {
  size_t sum = 1;
  while (exp > 0)
    base *= exp--;
  return base;
}

size_t Pow13(unsigned int exp) {
  size_t solution = 1;

  for (int i = 1; i < exp; i++)
    solution *= 13;

  return solution;
}

ChessBoard::ChessBoard(const ChessBoard &other) {
  plane_ = other.plane_;
  move_counter_ = other.move_counter_;
}

ChessBoard::ChessBoard() {

  plane_[0] = new Rook(P_BLACK);
  plane_[1] = new Night(P_BLACK);
  plane_[2] = new Bishop(P_BLACK);
  plane_[3] = new Queen(P_BLACK);
  plane_[4] = new King(P_BLACK);
  plane_[5] = new Bishop(P_BLACK);
  plane_[6] = new Night(P_BLACK);
  plane_[7] = new Rook(P_BLACK);
  for (int i = 8; i < 16; ++i)
    plane_[i] = new Pawn(P_BLACK);

  for (int i = 16; i < 48; ++i)
    plane_[i] = new Piece();

  for (int i = 48; i < 56; ++i)
    plane_[i] = new Pawn(P_WHITE);

  plane_[56] = new Rook(P_WHITE);
  plane_[57] = new Night(P_WHITE);
  plane_[58] = new Bishop(P_WHITE);
  plane_[59] = new Queen(P_WHITE);
  plane_[60] = new King(P_WHITE);
  plane_[61] = new Bishop(P_WHITE);
  plane_[62] = new Night(P_WHITE);
  plane_[63] = new Rook(P_WHITE);
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other) {
  if (&other == this)
    return *this;
  plane_ = other.plane_;
  move_counter_ = other.move_counter_;
  return *this;
}

Piece *&ChessBoard::operator[](unsigned int position) {
  return plane_[position];
}

Piece &ChessBoard::GetElement(unsigned int h, unsigned int w) {
  return *plane_[h * B_WIDTH + w];
}

double ChessBoard::EvaluatePosition() {

  double white_weight_of_move = 0.1;
  double black_weight_of_move = 0.1;

  /// if next round is white to move we boost wite evaluation
  //  if (move_counter_ % 2 == 0)
  //    black_weight_of_move += 0.07;
  //  else
  //    white_weight_of_move += 0.07;

  std::vector<Move> white_move_buffer;
  std::vector<Move> black_move_buffer;
  double eva = 0.0;

  for (int i = 0; i < 64; i++) {

    if (plane_[i]->Color()) {

      white_move_buffer.reserve(white_move_buffer.size() + 27);
      plane_[i]->GenMoves(plane_, i, white_move_buffer);

    } else {
      black_move_buffer.reserve(black_move_buffer.size() + 27);

      plane_[i]->GenMoves(plane_, i, black_move_buffer);
    }

    eva += plane_[i]->Value();
  }
  eva += white_move_buffer.size() * white_weight_of_move;
  eva -= black_move_buffer.size() * black_weight_of_move;

  return eva;
}

Piece &ChessBoard::GetElement(unsigned int position) {
  return *plane_[position];
}

void ChessBoard::DoMove(const Move &target) {
  plane_[target.to_] = plane_[target.from_]->Clone();
  plane_[target.to_]->SetMoved();

  // delete plane_[target.from_];
  plane_[target.from_] = new Piece();
  move_counter_++;
}

void ChessBoard::TransposeChessboard(ChessBoard &new_board,
                                     const Move &target) {

  new_board[target.to_] = new_board[target.from_]->Clone();
  new_board[target.to_]->SetMoved();

  // delete plane_[target.from_];
  new_board[target.from_] = new Piece();
  new_board.move_counter_++;
}

/// todo debate over it
void ChessBoard::GenAllPossibleMoves(bool color,
                                     std::vector<Move> &possible_moves) {

  for (int i = 0; i < plane_.size(); i++) {
    if (plane_[i]->Color() == color) {

      possible_moves.reserve(possible_moves.size() + 27);

      plane_[i]->GenMoves(plane_, i, possible_moves);
    }
  }
}

void ChessBoard::LoadPosition(const std::string &path) {

  for (auto &i : plane_)
    delete i;

  std::ifstream file;
  file.open(path);
  std::string moves;
  while (moves.substr(0, 4) != "[FEN")
    getline(file, moves);
  // ok example board state :
  // [FEN "6k1/ppp2pp1/1q4b1/5rQp/8/1P6/PBP2PPP/3R2K1 w - - 0 1"]

  moves.erase(0, 6); // remove [FEN "

  int current_square = 0;
  char input;

  for (int i = 0; i < 8;) {

    input = moves[0];
    moves.erase(0, 1);
    if (input >= '1' && input <= '9') {
      int j;
      for (j = current_square; j < current_square + (int)(input - '0'); j++)
        plane_[j] = new Piece();
      current_square = j;
      continue;
    }

    switch (input) {
    case 'p':
      plane_[current_square++] = new Pawn(P_BLACK);
      break;
    case 'n':
      plane_[current_square++] = new Night(P_BLACK);
      break;
    case 'b':
      plane_[current_square++] = new Bishop(P_BLACK);
      break;
    case 'r':
      plane_[current_square++] = new Rook(P_BLACK);
      break;
    case 'q':
      plane_[current_square++] = new Queen(P_BLACK);
      break;
    case 'k':
      plane_[current_square++] = new King(P_BLACK);
      break;
    case 'P':
      plane_[current_square++] = new Pawn(P_WHITE);
      break;
    case 'N':
      plane_[current_square++] = new Night(P_WHITE);
      break;
    case 'B':
      plane_[current_square++] = new Bishop(P_WHITE);
      break;
    case 'R':
      plane_[current_square++] = new Rook(P_WHITE);
      break;
    case 'Q':
      plane_[current_square++] = new Queen(P_WHITE);
      break;
    case 'K':
      plane_[current_square++] = new King(P_WHITE);
      break;
    case '/':
      ++i;
      break;
    case ' ':
      goto end;
    default:
      assert(false);
    }
    assert(current_square < 64);
  }
end:

  file.close();
}

void ChessBoard::EvaluateMove(Move &target) {
  auto temp_board(*this);
  temp_board.DoMove(target);
  target.evaluation_ = temp_board.EvaluatePosition();
}

double ChessBoard::MinMax(ChessBoard &target, int depth, bool color) {

  double current_evaluation = EvaluatePosition();
  if (depth == 0 ||
      Abs(current_evaluation) > 900) // abs(current_evaluation) is > 900 when
    // someone mated the other player
    return current_evaluation;

  if (color) { // for white

    current_evaluation = -1000;

    std::vector<Move> move_buffer;
    GenAllPossibleMoves(P_WHITE, move_buffer);

    for (auto &move : move_buffer) {
      ChessBoard m_board(*this);
      TransposeChessboard(m_board, move);

      move.evaluation_ = target.MinMax(m_board, depth - 1, P_BLACK);

      current_evaluation = Max(move.evaluation_, current_evaluation);
    }

    return current_evaluation;

  } else { // for black

    std::vector<Move> move_buffer;
    current_evaluation = 1000;

    GenAllPossibleMoves(P_WHITE, move_buffer);

    for (auto &move : move_buffer) {
      ChessBoard m_board(*this);
      TransposeChessboard(m_board, move);

      move.evaluation_ = target.MinMax(m_board, depth - 1, P_WHITE);

      current_evaluation = Min(move.evaluation_, current_evaluation);
    }
    return current_evaluation;
  }
}

double ChessBoard::AlfaBetaMinMax(ChessBoard &target, int depth, double alfa,
                                  double beta, bool color) {

  double current_evaluation = EvaluatePosition();
  if (depth == 0 ||
      Abs(current_evaluation) > 900) // abs(current_evaluation) is > 900 when
    // someone mated the other player
    return current_evaluation;

  if (color) { // for white

    current_evaluation = -1000;

    std::vector<Move> move_buffer;
    GenAllPossibleMoves(P_WHITE, move_buffer);

    for (auto &move : move_buffer) {
      ChessBoard m_board(*this);
      TransposeChessboard(m_board, move);

      move.evaluation_ =
          target.AlfaBetaMinMax(m_board, depth - 1, alfa, beta, P_BLACK);

      current_evaluation = Max(move.evaluation_, current_evaluation);

      if (current_evaluation >= beta)
        break;

      alfa = Max(current_evaluation, alfa);
    }
    return current_evaluation;
  } else { // for black

    std::vector<Move> move_buffer;
    current_evaluation = 1000;

    GenAllPossibleMoves(P_BLACK, move_buffer);

    for (auto &move : move_buffer) {
      ChessBoard m_board(*this);
      TransposeChessboard(m_board, move);

      move.evaluation_ =
          target.AlfaBetaMinMax(m_board, depth - 1, alfa, beta, P_WHITE);

      current_evaluation = Min(move.evaluation_, current_evaluation);
      if (current_evaluation <= alfa)
        break;
      beta = Min(beta, current_evaluation);
    }
    return current_evaluation;
  }
}

unsigned int ChessBoard::Hash() {
  int i = 0;
  unsigned int sum = 0;
  for (auto &piece : plane_) {
    sum += piece->Hash() * Pow13(i);
    i++;
  }
  return sum;
}

double ChessBoard::AlfaBetaMinMaxTranspositionTable(
    ChessBoard &target, int depth, double alfa, double beta, bool color,
    std::map<size_t, double> &transposition_table) {

  size_t  current_hash = Hash();

    std::wcout<<L"size:"<<transposition_table.size();
  if (transposition_table.find(current_hash) != transposition_table.end())
    return transposition_table[current_hash];

  double current_evaluation = EvaluatePosition();

  // abs(current_evaluation) is > 900 when
  // someone mated the other player
  if (depth == 0 || Abs(current_evaluation) > 900)
    return current_evaluation;

  if (color) { // for white

    current_evaluation = -1000;

    std::vector<Move> move_buffer;
    GenAllPossibleMoves(P_WHITE, move_buffer);

    for (auto &move : move_buffer) {
      ChessBoard m_board(*this);
      TransposeChessboard(m_board, move);

      move.evaluation_ =
          target.AlfaBetaMinMaxTranspositionTable(m_board, depth - 1, alfa, beta, P_BLACK, transposition_table);

      current_evaluation = Max(move.evaluation_, current_evaluation);

      if (current_evaluation >= beta)
        break;

      alfa = Max(current_evaluation, alfa);
    }
    transposition_table.insert({current_hash, current_evaluation});
    return current_evaluation;
  } else { // for black

    std::vector<Move> move_buffer;
    current_evaluation = 1000;

    GenAllPossibleMoves(P_BLACK, move_buffer);

    for (auto &move : move_buffer) {
      ChessBoard m_board(*this);
      TransposeChessboard(m_board, move);

      move.evaluation_ =
          target.AlfaBetaMinMaxTranspositionTable(m_board, depth - 1, alfa, beta, P_WHITE,transposition_table);

      current_evaluation = Min(move.evaluation_, current_evaluation);
      if (current_evaluation <= alfa)
        break;
      beta = Min(beta, current_evaluation);
    }
    transposition_table.insert({current_hash, current_evaluation});
    return current_evaluation;
  }
}
