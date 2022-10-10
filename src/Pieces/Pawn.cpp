#include "Pawn.h"
#include <iostream>

//TODO
std::vector<PieceInfo> Pawn::getPossibleMoves()
{
  std::cout << "The possible moves for pawn at (" << m_x << "," << m_y << ") are: " << std::endl;
  std::vector<PieceInfo> moves;
  if(this->m_color == PieceColor::WHITE)
  {
    if(!m_start)
    {
      if (m_y != 7)
      {
        PieceInfo move{m_x, m_y + 1};
        moves.push_back(move);
      }
    }
    else
    {
      if (m_y != 7)
      {
        PieceInfo move1{m_x, m_y +1};
        PieceInfo move2{m_x, m_y +1};
        moves.push_back(move1);
        moves.push_back(move2);
      }
    }
  }
  else
  {
    if(!m_start)
    {
      if (m_y != 7)
      {
        PieceInfo move{m_x, m_y + 1};
        moves.push_back(move);
      }
    }
    else
    {
      if (m_y != 7)
      {
        PieceInfo move1{m_x, m_y +1};
        PieceInfo move2{m_x, m_y +1};
        moves.push_back(move1);
        moves.push_back(move2);
      }
    }

  }
  return moves;
}
