#pragma once
#include "Piece.h"

class Queen : public Piece
{
  private:
    int m_x,m_y;
    bool m_start = true;
    //Board* board;
    PieceType m_type = PieceType::QUEEN;
    int m_color; //black = 0, white = 1
    Texture* m_texture;



  public:
    Queen(){}
    Queen(int x, int y, PieceColor color, Texture* texture)//Board* board;
    :m_x(x) , m_y(y), m_color(color),m_texture(texture)
    {
    }

    /*
    Queen(Pawn& pawn)
    :m_x =
    {}
    */
    ~Queen()
    {
    }
    int getX() const override  {return m_x;}
    int getY() const override  {return m_y;}
    Texture* getTexture() const override { return m_texture; }
    int getColor() const override{ return m_color;}
    int getType() const override {return m_type;}
    //major board moves
    void moveTo(int xpos, int ypos) override
    {
      m_x = xpos;
      m_y = ypos;
      m_start = true;
    }
    void moveTo(PieceInfo& position) override
    {
      m_x = position.x;
      m_y = position.y;
      m_start = false;
    }

      /*
    {
      m_x = pawn.getX();
      m_y = pawn.getY();
      m_start = false;
      m_texture = (pawn.getColor() == PieceColor::WHITE ? TEXTURE_QUEEN_W : TEXTURE_QUEEN_B);

      return Queen(pawn.getX(),pawn.getY(),(PieceColor)pawn.getColor(),
         (pawn.getColor() == PieceColor::WHITE ? TEXTURE_QUEEN_W : TEXTURE_QUEEN_B) );
    }
    */

};




