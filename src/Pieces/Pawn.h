#pragma once
#include "../pch.h"
#include "../Constants.h"
#include "../Texture.h"
#include "Piece.h"




class Pawn : public Piece
{

  private:
    int m_x,m_y;
    bool m_start = true;

    //Board* board;
    PieceType m_type = PieceType::PAWN;
    PieceColor m_color; //black = 0, white = 1
    Texture* m_texture;


  public:
    Pawn(){}
    Pawn(int x, int y, PieceColor color, Texture* texture)//Board* board;
    :m_x(x) , m_y(y), m_color(color),m_texture(texture)
    {
      //assignTexture();
    }
    ~Pawn()
    {
    }
    int getX() const override  {return m_x;}
    int getY() const override  {return m_y;}
    int getType() const override { return m_type; }
    int getColor() const override { return m_color;}
    bool firstMove() const override {return m_start;}
    //void moved() override { m_start = !m_start; }


    Texture* getTexture() const override {return m_texture;}

    std::vector<PieceInfo>  getPossibleMoves() override;
    void move() override
    {
      m_y++;
      m_start = false;
    }

    void moveTo(int xpos,int ypos) override
    {
      m_x = xpos;
      m_y = ypos;
      //m_start = ;
    }
    void moveTo(PieceInfo& position) override
    {
        m_x = position.x;
        m_y = position.y;
        m_start=false;
    }
    bool canTransform()
    {
      if(m_y == 0 || m_y == 7)
        return true;
      else
        return false;
    }
};


