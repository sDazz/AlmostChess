#pragma once

#include "Piece.h"
#include "../Constants.h"
#include "../pch.h"

class Rook : public Piece
{
  private:
    int m_x,m_y;
    bool m_start = true;
    PieceColor m_color; //black = 0, white = 1
    PieceType m_type = PieceType::ROOK;
    Texture* m_texture;

  public:

    Rook(){}
    Rook(int x, int y, PieceColor color, Texture* texture)//Board* board;
    :m_x(x) , m_y(y), m_color(color),m_texture(texture)
    {
      //std::cout << "about to call assign" << std::endl;
      //Texture* m_texture = &TEXTURE_ROOK_W;
      //std::cout << m_texture->getTextureID() << std::endl;
    }
    ~Rook()
    {
    }

    int getType() const override {return m_type;}
    int getX() const override  {return m_x;}
    int getY() const override  {return m_y;}
    int getColor() const override{ return m_color;}

    bool firstMove() const override {return m_start;}

    //major board moves
    void moveTo(int xpos, int ypos) override
    {
      m_x = xpos;
      m_y = ypos;
      m_start = true;
    }
    //common moves
    void moveTo(PieceInfo& position) override
    {
      m_x = position.x;
      m_y = position.y;
      m_start = false;
    }

    Texture* getTexture() const override { return m_texture; }

};

