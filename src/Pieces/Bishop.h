#pragma once
#include "Piece.h"

class Bishop : public Piece
{
  private:
    int m_x,m_y;
    bool m_start = true;
    //Board* board;
    PieceType m_type = PieceType::BISHOP;
    PieceColor m_color; //black = 0, white = 1
    Texture* m_texture;



  public:
    Bishop(){}
    Bishop(int x, int y, PieceColor color, Texture* texture)//Board* board;
    :m_x(x) , m_y(y), m_color(color),m_texture(texture)
    {
      //assignTexture();
    }
    ~Bishop()
    {
    }
    int getX() const override  {return m_x;}
    int getY() const override  {return m_y;}
    Texture* getTexture() const override { return m_texture; }
    int getColor() const override{ return m_color;}
    int getType() const override {return m_type;}


    //used to make major board moves
    void moveTo(int xpos,int ypos) override
    {
      m_x = xpos;
      m_y = ypos;
      m_start = true;
    }
    //comon move
    void moveTo(PieceInfo& position) override
    {
      m_x = position.x ;
      m_y = position.y;
      m_start = false;
    }
};
