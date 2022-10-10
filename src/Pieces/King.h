#pragma once
#include "Piece.h"

class King : public Piece
{
  private:
    int m_x,m_y;
    bool m_start = true;
    //Board* board;
    PieceType m_type = PieceType::KING;
    PieceColor m_color; //black = 0, white = 1
    Texture* m_texture;
    bool m_leftCastled = false;
    bool m_rightCastled = false;



  public:
    King(){}
    King(int x, int y, PieceColor color, Texture* texture)//Board* board;
    :m_x(x) , m_y(y), m_color(color),m_texture(texture)
    {
      //assignTexture();
    }
    ~King()
    {
    }
    int getX() const override  {return m_x;}
    int getY() const override  {return m_y;}
    Texture* getTexture() const override { return m_texture; }
    int getColor() const override{ return m_color;}
    int getType() const override {return m_type;}
    bool firstMove() const override { return m_start;}

    bool leftCastled() const override { return m_leftCastled;}
    bool rightCastled() const override { return m_rightCastled;}
    void setRightCastled() override { m_leftCastled = true; }
    void setLeftCastled() override { m_rightCastled = true; }

    void moveTo(PieceInfo& position) override
    {
      if(position.x - m_x == 2)
        m_rightCastled = true;
      else if(position.x - m_x == -2)
        m_leftCastled = true;

      m_x = position.x;
      m_y = position.y;
      m_start = false;
    }

    void moveTo(int xpos,int ypos) override
    {
      m_x = xpos;
      m_y = ypos;
      m_start = true;
      m_rightCastled = false;
      m_leftCastled = false;
    }

};

