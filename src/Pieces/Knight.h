#pragma once
#include "Piece.h"

class Knight : public Piece
{
  private:
    int m_x,m_y;
    bool m_start = true;
    //Board* board;
    PieceType m_type = PieceType::KNIGHT;
    PieceColor m_color; //black = 0, white = 1
    Texture* m_texture;



  public:
    Knight(){}
    Knight(int x, int y, PieceColor color, Texture* texture)//Board* board;
    :m_x(x) , m_y(y), m_color(color),m_texture(texture)
    {
      //assignTexture();
    }
    ~Knight()
    {
    }
    int getX() const override  {return m_x;}
    int getY() const override  {return m_y;}

    Texture* getTexture() const override { return m_texture; }
    int getColor() const override{ return m_color;}
    int getType() const override {return m_type;}
    void moveTo(PieceInfo& position) override { m_x = position.x; m_y = position.y;}
    void moveTo(int xpos,int ypos) override { m_x = xpos; m_y = ypos;}
};

