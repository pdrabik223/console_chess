//
// Created by studio25 on 24.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_ARROW_H_
#define CONSOLE_CHESS_GUI_ARROW_H_

#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <vector>
#include <ciso646>
struct Coord {
  Coord(unsigned int x, unsigned int y);
  Coord();
  bool operator==(const Coord &rhs) const;
  bool operator!=(const Coord &rhs) const;
  unsigned x, y;
};


/// arrow is made out of 4 points
/// later I''ll ecxplain it
class Arrow {
public:
  Arrow(const Coord &from, const Coord &to, const SDL_Color &color,
        unsigned int size);

  void DisplayArrow(SDL_Renderer *renderer,bool flip_axis, unsigned window_height);


private:
  ///
  /// \param middle_point the center of generated semicircle
  /// \param relation the semicircle will be generated on the opposite side of this point
  /// \return points generating semicircle
  std::vector<Coord> GenSemicircle(Coord middle_point,Coord relation);

  std::vector<Coord> GenArmsPoints(Coord from_point,Coord to_point);

  static double FindAngle(const Coord &p0, const Coord &p1, const Coord &p2);

  std::vector<Coord> GenCircle(Coord middle_point);

protected:
  Coord from_;
  Coord to_;
  SDL_Color color_;

  /// the radius of a circle around the points
  unsigned radius_;

  unsigned arm_length;
  /// the angle between arms of an arrow and it's body
  /// described in   Degrees  <0,360>
  double arm_angle_;


};

#endif // CONSOLE_CHESS_GUI_ARROW_H_
