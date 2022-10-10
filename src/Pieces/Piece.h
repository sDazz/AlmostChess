#pragma once

#include "../Constants.h"
#include "../Texture.h"
#include "../pch.h"


struct PieceInfo
{
  int x;
  int y;
  int color;
  int type;
  PieceInfo(int inpt_x=-1, int inpt_y=-1,int inpt_color=-1,int inpt_type=-1)
  :x(inpt_x),y(inpt_y),color(inpt_color),type(inpt_type)
  {}
  void empty()
  {
    x = -1; y = -1;
  }
  bool isEmpty() const
  {
    if ( x==-1 && y == -1) return true;
    else return false;
  }
};

//this was supposed to be basically an interface but it got out of hand
class Piece {
  private:
    int m_x;
    int m_y;
public:
  Piece() {}
  virtual ~Piece() {}
  virtual std::vector<PieceInfo> getPossibleMoves() {
    std::cout << "PIECE METHOD CALLED, NOT SUPPOSED TO HAPPEN" << std::endl;
    std::vector<PieceInfo> what;
    return what;
  };

  virtual bool firstMove() const{return 0;}

  virtual int getX() const {
    std::cout << "GETX FROM PIECE CALLED" << std::endl;
    return 0;
  };
  virtual int getY() const {
    std::cout << "GETY FROM PIECE CALLED" << std::endl;
    return 0;
  };

  virtual int getColor() const {
    std::cout << "GETCOLOR FROM PIECE CALLED " << std::endl;
    return 0;
  }

  virtual int getType() const {
    std::cout << "gettype from piece" << std::endl;
    return 0;
  };

  virtual Texture *getTexture() const {
    std::cout << "GET TEXTURE FROM PIECE CALLED" << std::endl;
    return 0;
  }

  virtual void move(){}
  virtual void moved(){}
  virtual void moveTo(PieceInfo& position)
  {
    m_x = position.x;
    m_y = position.y;
  }
  //king shi
  virtual void moveTo(int xpos, int ypos){}
  virtual void resetPos(){}

  virtual bool leftCastled() const {return 0;}
  virtual bool rightCastled() const {return 0;}
  virtual void setRightCastled() {}
  virtual void setLeftCastled() {}
};


