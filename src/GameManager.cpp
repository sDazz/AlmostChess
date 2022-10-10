#include "GameManager.h"
#include "Constants.h"
#include "external/glm/ext/matrix_clip_space.hpp"
#include <iterator>



bool operator==(const PieceInfo& rhs,const PieceInfo& lhs)
{
  return( rhs.x == lhs.x && rhs.y == lhs.y);
}

GameManager::~GameManager()
{
}
void GameManager::genFullBoard()
{
  //__________DARK REALM_________
  //royal
  m_blackPieces.push_back(&b_queen);
  m_blackPieces.push_back(&b_king);

  //brick
  m_blackPieces.push_back(&b_rook_1);
  m_blackPieces.push_back(&b_rook_2);

  //church
  m_blackPieces.push_back(&b_bishop_1);
  m_blackPieces.push_back(&b_bishop_2);

  //jumpy
  m_blackPieces.push_back(&b_knight_1);
  m_blackPieces.push_back(&b_knight_2);

  //slaves
  m_blackPieces.push_back(&b_pawn_1);
  m_blackPieces.push_back(&b_pawn_2);
  m_blackPieces.push_back(&b_pawn_3);
  m_blackPieces.push_back(&b_pawn_4);
  m_blackPieces.push_back(&b_pawn_5);
  m_blackPieces.push_back(&b_pawn_6);
  m_blackPieces.push_back(&b_pawn_7);
  m_blackPieces.push_back(&b_pawn_8);

  //__________TOOTHPASTE________
  //royal
  m_whitePieces.push_back(&w_queen);
  m_whitePieces.push_back(&w_king);

  //brick
  m_whitePieces.push_back(&w_rook_1);
  m_whitePieces.push_back(&w_rook_2);

  //church
  m_whitePieces.push_back(&w_bishop_1);
  m_whitePieces.push_back(&w_bishop_2);

  //jumpy
  m_whitePieces.push_back(&w_knight_1);
  m_whitePieces.push_back(&w_knight_2);

  //slaves
  m_whitePieces.push_back(&w_pawn_1);
  m_whitePieces.push_back(&w_pawn_2);
  m_whitePieces.push_back(&w_pawn_3);
  m_whitePieces.push_back(&w_pawn_4);
  m_whitePieces.push_back(&w_pawn_5);
  m_whitePieces.push_back(&w_pawn_6);
  m_whitePieces.push_back(&w_pawn_7);
  m_whitePieces.push_back(&w_pawn_8);

}

void GameManager::drawCurrent(Renderer& rh, Renderer& circleRh)
{

  rh.drawBoard(BOARD_COLOR_1, BOARD_COLOR_2, BOARD_SIZE);

  for(auto piece : m_whitePieces)
  {
    rh.drawPiece(*piece);
  }

  for(auto piece : m_blackPieces)
  {
    rh.drawPiece(*piece);
  }

  for(auto cell : m_currentPossibleMoves)
  {
    circleRh.drawCircle(cell);
  }
  if(selected)
  {
    PieceInfo currentSelected{selected->getX(),selected->getY()};
    rh.highlightCell(currentSelected);
  }
  if(m_cellToHighlight.x != -1)
  {
    rh.highlightCell(m_cellToHighlight);
  }
  if(m_PawnTransform.x != -1)
  {
    rh.drawPawnTransform(m_PawnTransform);
  }
  setOccupiedPositions();
}

void GameManager::click_callback(int xpos, int ypos,int button,int action)
{

  ypos = static_cast<int>((SCREEN_HEIGHT - ypos)/SQUARE_HEIGHT);
  xpos = static_cast<int>(xpos/SQUARE_WIDTH);
  PieceInfo clicked;
  clicked.x = xpos;
  clicked.y = ypos;




  std::vector<PieceInfo> currentPossibleMoves;
  PieceInfo occupied;
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
    occupied = this->checkOccupiedPosition(clicked);
    if(m_PawnTransform.x != -1)
    {
      std::vector<PieceInfo> possibleChoices;
      PieceInfo move;

      for(int i = 0 ; i < 4; i++)
      {
        if(m_PawnTransform.y == 7)
        {
          move.x = m_PawnTransform.x == 7 ? m_PawnTransform.x - 1 : m_PawnTransform.x + 1;
          move.y = m_PawnTransform.y - i;
        }
        else
        {
          move.x = m_PawnTransform.x == 7 ? m_PawnTransform.x - 1 : m_PawnTransform.x + 1;
          move.y = m_PawnTransform.y + i;
        }
        m_currentPossibleMoves.push_back(move);
      }
      PieceInfo click(xpos,ypos);
      PieceType type = PAWN;
      auto isIn = std::find(begin(m_currentPossibleMoves),end(m_currentPossibleMoves),click);
      if(isIn != currentPossibleMoves.end())
      {
        if(m_PawnTransform.y == 7)
        {
          if(xpos == move.x)
          {
            switch(ypos)
            {
              case(7):
                {
                  type = BISHOP;
                  break;
                }
              case(6):
                {
                  type = KNIGHT;
                  break;
                }
              case(5):
                {
                  type = ROOK;
                  break;
                }
              case(4):
                {
                  type = QUEEN;
                  break;
                }
            }
          }
        }
        else if (m_PawnTransform.y == 0)
        {
          if(xpos == move.x)
          {
            switch(ypos)
            {
              case(0):
                {
                  type = BISHOP;
                  break;
                }
              case(1):
                {
                  type = KNIGHT;
                  break;
                }
              case(2):
                {
                  type = ROOK;
                  break;
                }
              case(3):
                {
                  type = QUEEN;
                  break;
                }
            }
          }
        }


        std::cout<< "allowed click, should transform" << std::endl;
        pawnTransform(getPieceByPosition(m_PawnTransform.x,m_PawnTransform.y),type);
        m_currentPossibleMoves.clear();
        m_PawnTransform.empty();
      }
    }
    else if(selected)
      {
        currentPossibleMoves = getAllowedMoves(*selected,true);
        PieceInfo move{xpos,ypos};
        auto isIn = std::find(begin(currentPossibleMoves),end(currentPossibleMoves),move);
        if(isIn != currentPossibleMoves.end())
        {

          if(occupied.x != -1)
          {
            if(occupied.color != selected->getColor())
            {
              Piece *captured = getPieceByPosition(xpos,ypos);
              PieceInfo cage{8,8};
              captured->moveTo(cage);
            }
          }

          selected->moveTo(move);
          dealWithCastle(selected);
          dealWithPawnTransform(selected);

          selected = nullptr;
          m_cellToHighlight.x = -1;

          turn = !turn;
          m_currentPossibleMoves.clear();
        }
        else
        {
          if(getPieceByPosition(xpos,ypos))
          {
            if(getPieceByPosition(xpos,ypos)->getColor() == selected->getColor())
            {
              selected = getPieceByPosition(xpos,ypos);
              m_currentPossibleMoves = getAllowedMoves(*selected,true);
            }
          }
          else
          {
            selected = nullptr;
            m_cellToHighlight.x = -1;
            m_currentPossibleMoves.clear();
          }
        }
      }
    else
        if(occupied.x != -1)// just to see if it is valid
        {
          if(!turn)
          {
            if(getPieceByPosition(xpos,ypos)->getColor() == PieceColor::WHITE)
            {
              selected = getPieceByPosition(xpos,ypos);
              m_currentPossibleMoves = getAllowedMoves(*selected,true);
            }
          }
          else
          {
            if(getPieceByPosition(xpos,ypos)->getColor() == PieceColor::BLACK)
            {
              selected = getPieceByPosition(xpos,ypos);
              m_currentPossibleMoves = getAllowedMoves(*selected,true);
            }
          }

        }

      m_whiteCheck = lookForWhiteCheck();
      m_blackCheck = lookForBlackCheck();
    }
}
void GameManager::pawnTransform(Piece* piece, PieceType type)
{
  PieceColor color = (PieceColor)piece->getColor();
  Piece* newPiece;
  int x = piece->getX();
  int y = piece->getY();
  piece->moveTo(8,8);
  switch(type)
  {
    case(BISHOP):
    {
      newPiece = new Bishop(x,y,color,(color == WHITE ? TEXTURE_BISHOP_W :
            TEXTURE_BISHOP_B));
      break;
    }
    case(KNIGHT):
    {
      newPiece = new Knight(x,y,color,(color == WHITE ? TEXTURE_KNIGHT_W :
            TEXTURE_KNIGHT_B));
      break;
    }
    case(ROOK):
    {
      newPiece = new Rook(x,y,color,(color == WHITE ? TEXTURE_ROOK_W :
            TEXTURE_ROOK_B));
      break;
    }
    case(QUEEN):
    {
      newPiece = new Queen(x,y,color,(color == WHITE ? TEXTURE_QUEEN_W :
            TEXTURE_QUEEN_B));
      break;
    }
  }
  if(color == WHITE)
    m_whitePieces.push_back(newPiece);
  else
    m_blackPieces.push_back(newPiece);
}


void GameManager::cursor_pos_callback(double xpos, double ypos)
{
  if(selected)
  {
    int horizontal = static_cast<int>(xpos/(SCREEN_WIDTH/BOARD_SIZE));
    int vertical = static_cast<int>((SCREEN_HEIGHT - ypos)/(SCREEN_WIDTH/BOARD_SIZE));

    PieceInfo underCursor(horizontal,vertical);

    auto isIn = std::find(begin(m_currentPossibleMoves),end(m_currentPossibleMoves),underCursor);
    if (isIn != m_currentPossibleMoves.end())
    {
      m_cellToHighlight.x = horizontal;
      m_cellToHighlight.y = vertical;
    }
    else
    {
      m_cellToHighlight.x = -1;
      m_cellToHighlight.y = -1;
    }
  }
}

void GameManager::dealWithPawnTransform(Piece* selected)
{
  if(selected->getType() == PieceType::PAWN)
  {
    if (static_cast<Pawn*>(selected)->canTransform())
    {
      //std::cout << "1.Knight \n 2.Bishop \n 3.Queen \n 4.Rook" << std::endl;
      m_PawnTransform.x = selected->getX();
      m_PawnTransform.y = selected->getY();
      /*
      std::cin >> choice;

      Piece* newPiece;

      switch(choice)
      {
        case(1):
          {
            newPiece = new Knight(selected->getX(),selected->getY(),(PieceColor)selected->getColor(),
              selected->getColor() == WHITE ? TEXTURE_KNIGHT_W : TEXTURE_KNIGHT_B);

            break;
          }
        case(2):
          {
            newPiece = new Bishop(selected->getX(),selected->getY(),(PieceColor)selected->getColor(),
                selected->getColor() == WHITE ? TEXTURE_BISHOP_W : TEXTURE_BISHOP_B);
            break;
          }
        case(3):
         {
           newPiece = new Queen(selected->getX(),selected->getY(),(PieceColor)selected->getColor(),
               selected->getColor() == WHITE ? TEXTURE_QUEEN_W : TEXTURE_QUEEN_B);
           break;
         }
        case(4):
         {
           newPiece = new Rook(selected->getX(),selected->getY(),(PieceColor)selected->getColor(),
               selected->getColor() == WHITE ? TEXTURE_ROOK_W : TEXTURE_ROOK_B);
             break;
         }
        default:
         {
           std::cout << "FAILED TO CREATE NEW PIECE" << std::endl;
         }
      }

      if(selected->getColor() == WHITE)
      {
        m_whitePieces.push_back(newPiece);
      }
      else
      {
        m_blackPieces.push_back(newPiece);
      }
      selected->moveTo(8,8);
      */
    }
  }
}

void GameManager::dealWithCastle(Piece* selected)
{
  if(m_Player == BLACK)
  {
    if(selected->getType() == PieceType::KING)
    {
      if(selected->leftCastled())
      {
        Piece* a_rook = getPieceByPosition(0,selected->getY());
        if(a_rook->firstMove())
        {
          PieceInfo rookMove{2,selected->getY()};
          a_rook->moveTo(rookMove);
        }
      }
      else if(selected->rightCastled())
      {
        Piece* b_rook = getPieceByPosition(7,selected->getY());
        if(b_rook->firstMove())
        {
          PieceInfo rookMove{4,selected->getY()};
          b_rook->moveTo(rookMove);
        }
      }
    }
  }
  else
  {
    if(selected->getType() == PieceType::KING)
    {
      if(selected->leftCastled())
      {
        Piece* a_rook = getPieceByPosition(0,selected->getY());
        if(a_rook->firstMove())
        {
          PieceInfo rookMove{3,selected->getY()};
          a_rook->moveTo(rookMove);
        }
      }
      else if(selected->rightCastled())
      {
        Piece* b_rook = getPieceByPosition(7,selected->getY());
        if(b_rook->firstMove())
        {
          PieceInfo rookMove{5,selected->getY()};
          b_rook->moveTo(rookMove);
        }
      }
    }
  }
}

Piece* GameManager::getPieceByPosition(int xpos, int ypos)
{

  for(auto piece: m_whitePieces)
  {
    if(piece->getX() == xpos && piece->getY() == ypos)
    {
      return piece;
    }
  }
  for(auto piece: m_blackPieces)
  {
    if(piece->getX() == xpos && piece->getY() == ypos)
    {
      return piece;
    }
  }
  return nullptr;
}



void GameManager::setOccupiedPositions()
{

  m_occupiedPositions.clear();
  for(auto piece : m_whitePieces)
  {
    PieceInfo position;
    position.x = piece->getX();
    position.y = piece->getY();
    position.color = piece->getColor();
    position.type = piece->getType();

    m_occupiedPositions.push_back(position);
  }
  for(auto piece : m_blackPieces)
  {
    PieceInfo position;
    position.x = piece->getX();
    position.y = piece->getY();
    position.color = piece->getColor();
    position.type = piece->getType();

    m_occupiedPositions.push_back(position);
  }
}



PieceInfo GameManager::checkOccupiedPosition(PieceInfo checked)
{
  const std::vector<PieceInfo>* currentOccupied = this->getOccupiedPositions();

  for (auto position : *currentOccupied)
  {
    if(position.x == checked.x && position.y==checked.y)
    {
      return {position.x , position.y, position.color, position.type};
    }
  }
  PieceInfo empty;
  return empty;
}

//flag is supposed to indicate if the function is being called by a player
//or by the system (for validating check and stuff)
std::vector<PieceInfo> GameManager::getAllowedMoves(Piece& piece,bool flag)
{
  std::vector<PieceInfo> allowedMoves;

  switch(piece.getType())
  {
    case(PieceType::KING):
      {
        allowedMoves = getPossibleKingMoves(piece,flag);
        break;
      }
    case(PieceType::QUEEN):
      {
        allowedMoves = getPossibleQueenMoves(piece);
        break;
      }
    case(PieceType::BISHOP):
      {
        allowedMoves = getPossibleBishopMoves(piece);
        break;
      }
    case(PieceType::KNIGHT):
      {
        allowedMoves = getPossibleKnightMoves(piece);
        break;
      }
    case(PieceType::ROOK):
      {
        allowedMoves = getPossibleRookMoves(piece);
        break;
      }
    case(PieceType::PAWN):
      {
        allowedMoves = getPossiblePawnMoves(piece,flag);
        break;
      }

  }
  if(flag)
  {
    if(!turn)
    {
      allowedMoves = filterAllowedMoves(allowedMoves,WHITE);
    }
    else
    {
      allowedMoves = filterAllowedMoves(allowedMoves,BLACK);
    }
    m_currentPossibleMoves = allowedMoves;
  }

  return allowedMoves;
}

std::vector<PieceInfo> GameManager::getPossiblePawnMoves(Piece& piece, bool flag)
{
  std::vector<PieceInfo> possibilities;

  if (piece.getColor() == m_Player)
  {
    //Move.
    if(flag)
    {
      for(int i = 1; (i < 3 || piece.getY() == 7) ; i ++)
      {
        PieceInfo move(piece.getX(),piece.getY() + i);
        auto occupied = std::find(begin(m_occupiedPositions),end(m_occupiedPositions),move);
        if (occupied != m_occupiedPositions.end()) break;

        possibilities.push_back(move);
        if(!piece.firstMove())
        {
          i++;
        }
      }
    }
    //Capture.
    if(piece.getY() != 7)
    {
      PieceInfo Capture{piece.getX(),piece.getY()+1,m_Player};
      int x = Capture.x;
      for(int i = -1 ; ( i < 2 ) ; i++)
      {
        if (i == 0 ) continue;
        Capture.x =  x + i;
        auto result = std::find(begin(m_occupiedPositions),end(m_occupiedPositions), Capture);
        if ( result != m_occupiedPositions.end() && result->color != piece.getColor()) //pawn capture condition.
        {
          possibilities.push_back(Capture);
        }
      }
    }
  }
  else//color white
  {
    if(flag)
    {
      for(int i = -1; (i > -3 ) ; i--)
      {
        if (piece.getY() == 0) continue;
        PieceInfo move(piece.getX(),piece.getY() + i);
        auto occupied = std::find(begin(m_occupiedPositions),end(m_occupiedPositions),move);
        if (occupied != m_occupiedPositions.end()) break;

        possibilities.push_back(move);
        if(!piece.firstMove())
        {
          i--;
        }
      }
    }

    if (piece.getY() != 0)
    {
      PieceInfo Capture{piece.getX(),piece.getY()-1,!m_Player};
      int x = Capture.x;
      for(int i = -1 ; ( i < 2 ) ; i++)
      {
        if (i == 0 ) continue;
        Capture.x = x + i;
        auto result = std::find(begin(m_occupiedPositions),end(m_occupiedPositions), Capture);
        if ( result != m_occupiedPositions.end() && result->color != piece.getColor()) //pawn capture condition.
        {
          possibilities.push_back(Capture);
        }
      }
    }
  }
  return possibilities;
}


std::vector<PieceInfo> GameManager::getPossibleRookMoves(Piece& piece)
{
  std::vector<PieceInfo> possibilities;
  PieceInfo move {piece.getX(), piece.getY()};
  //get Vertical Line
  int o_x = move.x;
  int o_y = move.y;

  //get right horizontal line
  for(int i = 1; i < 8 ; i++)
  {
    if (o_x + i < 8 && o_x + i > 0)
    {
      move.x = o_x + i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }
  //get left horizontal line
  for(int i = -1; i > -8 ; i--)
  {
    if (o_x + i < 8 && o_x + i >= 0)
    {
      move.x = o_x + i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }

  move.x = o_x;
  //get up vertical line
  for(int i = 1 ; i < 8; i++)
  {
    if (o_y + i < 8 && o_y + i >= 0)
    {
      move.y = o_y + i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }
  //get down vertical line
  for(int i = -1 ; i > -8; i--)
  {
    if (o_y + i < 8 && o_y + i >= 0)
    {
      move.y = o_y + i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }
  //coul`ve also just changed the +i to -i, instead of messing with the loops...
  return possibilities;
}
std::vector<PieceInfo> GameManager::getPossibleQueenMoves(Piece& piece)
{
  std::vector<PieceInfo> possibilities;
  for (auto a: getPossibleRookMoves(piece))
  {
    possibilities.push_back(a);
  }

  for (auto b: getPossibleBishopMoves(piece))
  {
    possibilities.push_back(b);
  }
  return possibilities;
}
std::vector<PieceInfo> GameManager::getPossibleKingMoves(Piece &piece,bool flag)
{
  std::vector<PieceInfo> possibilities;
  PieceInfo move{piece.getX(),piece.getY(),piece.getColor()};
  int o_x = move.x;
  int o_y = move.y;
  for(int i = -1; i < 2; i++)
  {
    for(int j = -1; j < 2; j++)
    {
      bool valid = false;
      if(i == 0 && j == 0)
        continue;

      if(o_x + i < 8 && o_x + i >=  0 && o_y + j < 8 && o_y+j >=0)
      {
        move.x = o_x + i;
        move.y = o_y + j;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        continue;
      }
      if(piece.getColor() == PieceColor::WHITE)
      {
        auto findCheck = std::find(begin(m_blackPossibleMoves),end(m_blackPossibleMoves),move);
        if(findCheck == m_blackPossibleMoves.end()) valid = true;
      }
      else
      {
        auto findCheck = std::find(begin(m_whitePossibleMoves),end(m_whitePossibleMoves),move);
        if(findCheck == m_whitePossibleMoves.end()) valid = true;
      }

      if (valid)
        possibilities.push_back(move);
      }

    }
  }
  //check for Castles
  if(piece.firstMove() && flag)
  {
    int row = piece.getY();
    int col = piece.getX();
    bool possibleLeft = true;
    bool possibleRight = true;
    //left
    int left_iter = -1;
    while(col + left_iter > 0)
    {
      PieceInfo way{col + left_iter,row};
      if(checkOccupiedPosition(way).x != -1)
      {
        possibleLeft = false;
      }
      left_iter--;
    }
    if(possibleLeft)
    {

      bool valid = false;
      if(getPieceByPosition(0,row)->firstMove())
      {
        PieceInfo move{piece.getX() - 2,piece.getY()};
        if(piece.getColor() == PieceColor::WHITE)
        {
          auto findCheck = std::find(begin(m_blackPossibleMoves),end(m_blackPossibleMoves),move);
          if(findCheck == m_blackPossibleMoves.end()) valid = true;
        }
        else
        {
          auto findCheck = std::find(begin(m_whitePossibleMoves),end(m_whitePossibleMoves),move);
          if(findCheck == m_whitePossibleMoves.end()) valid = true;
        }
        if(valid)
          possibilities.push_back(move);
      }
    }
    //right
    int right_iter = 1;
    while(col + right_iter < 7)
    {
      PieceInfo way{col + right_iter,row};
      if(checkOccupiedPosition(way).x != -1)
      {
        possibleRight = false;
      }
      right_iter++;
    }
    if(possibleRight)
    {

      bool valid = false;
      //this is a rook VVV  //supposed to check for castles
      if(getPieceByPosition(0,row)->firstMove())
      {
        PieceInfo move{piece.getX() + 2,piece.getY()};
        if(piece.getColor() == PieceColor::WHITE)
        {
          auto findCheck = std::find(begin(m_blackPossibleMoves),end(m_blackPossibleMoves),move);
          if(findCheck == m_blackPossibleMoves.end()) valid = true;
        }
        else
        {
          auto findCheck = std::find(begin(m_whitePossibleMoves),end(m_whitePossibleMoves),move);
          if(findCheck == m_whitePossibleMoves.end()) valid = true;
        }
        if(valid)
        {
          possibilities.push_back(move);
        }
      }
    }
  }

  return possibilities;


}

std::vector<PieceInfo> GameManager::getPossibleBishopMoves(Piece& piece)
{
  std::vector<PieceInfo> possibilities;
  PieceInfo move {piece.getX(),piece.getY(),piece.getColor()};
  int o_x = move.x;
  int o_y = move.y;

  //UP AND RIGHT
  for(int i = 1; i < 8; i++)
  {
    if(o_x + i < 8 && o_x + i >=0
    && o_y + i < 8 && o_y +i >= 0)
    {
      move.x = o_x + i;
      move.y = o_y + i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }

  //DOWN AND RIGHT
  for(int i = 1; i < 8; i++)
  {
   if(o_x + i < 8 && o_x + i >=0
    && o_y - i < 8 && o_y -i >= 0)
    {
      move.x = o_x + i;
      move.y = o_y - i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }
  //DOWN AND LEFT
  for(int i = 1; i < 8; i++)
  {
    if(o_x - i < 8 && o_x - i >=0
    && o_y - i < 8 && o_y -i >= 0)
    {
      move.x = o_x - i;
      move.y = o_y - i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }

  //UP AND LEFT
  for(int i = 1; i < 8; i++)
  {
    if(o_x - i < 8 && o_x - i >=0
    && o_y + i < 8 && o_y + i >= 0)
    {
      move.x = o_x - i;
      move.y = o_y + i;
      if(checkOccupiedPosition(move).x != -1)
      {
        if(checkOccupiedPosition(move).color != piece.getColor())
          possibilities.push_back(move);

        break;
      }
      possibilities.push_back(move);
    }
  }
  return possibilities;
}



std::vector<PieceInfo> GameManager::getPossibleKnightMoves(Piece& piece)
{
  std::vector<PieceInfo> possibilities;
  PieceInfo move{piece.getX(), piece.getY(),piece.getColor()};
  int o_x = move.x;
  int o_y = move.y;
  for(int i = -2 ; i < 3 ; i +=2)
  {
    for(int j = -1; j < 2; j++)
    {
      if(j == 0 || i == 0) continue;

      if(o_x + i < 8 && o_x + i >=  0 && o_y + j < 8 && o_y+j >=0)
      {
        move.x = o_x + i;
        move.y = o_y + j;
        if(checkOccupiedPosition(move).x != -1)
        {
          if(checkOccupiedPosition(move).color != piece.getColor())
            possibilities.push_back(move);

          continue;
        }
        possibilities.push_back(move);
      }

    }
  }
  for(int i = -2 ; i < 3 ; i +=2)
  {
    for(int j = -1; j < 2; j++)
    {
      if(j == 0 || i == 0) continue;

      if(o_y + i < 8 && o_y + i >=  0 && o_x + j < 8 && o_x+j >=0)
      {
        move.x = o_x + j;
        move.y = o_y + i;
        if(checkOccupiedPosition(move).x != -1)
        {
          if(checkOccupiedPosition(move).color != piece.getColor())
            possibilities.push_back(move);

          continue;
        }
        possibilities.push_back(move);
      }

    }

  }
  return possibilities;
}



bool GameManager::lookForBlackCheck(const PieceInfo& h_move)
{

  bool isChecked;
  PieceInfo current;
  bool flag = false;
  if(!h_move.isEmpty())
  {
    if(selected)
    {
      current.x = selected->getX();
      current.y = selected->getY();
      current.color = selected->getColor();
      current.type = selected->getType();
      flag = true;
    }
    selected->moveTo(h_move.x,h_move.y);
    setOccupiedPositions();
  }
  m_whitePossibleMoves.clear();
  for(auto piece : m_whitePieces)
  {
    if(piece->getX() == 8) continue;//pieces already captured

    for(auto move : getAllowedMoves(*piece,false))
    {
      m_whitePossibleMoves.push_back(move);
    }

    PieceInfo b_kingPosition(b_king.getX(),b_king.getY());
    auto kingCapturable = std::find(begin(m_whitePossibleMoves),end(m_whitePossibleMoves),b_kingPosition);
    if(kingCapturable != m_whitePossibleMoves.end())
    {
      isChecked = true;
      std::cout << "BLACK CHECKED" << std::endl;
    }
    else
    {
      isChecked = false;
    }
  }
  if(flag)
    selected->moveTo(current.x,current.y);

  return isChecked;
}
bool GameManager::lookForWhiteCheck(const PieceInfo& h_move)
{

  bool isChecked;
  PieceInfo current;
  bool flag = false;
  if(!h_move.isEmpty())
  {
    if(selected)
    {
      current.x = selected->getX();
      current.y = selected->getY();
      current.color = selected->getColor();
      current.type = selected->getType();
      flag = true;
    }
    selected->moveTo(h_move.x,h_move.y);
    setOccupiedPositions();
  }
  m_blackPossibleMoves.clear();
  for(auto piece : m_blackPieces)
  {
    if(piece->getX() == 8) continue;//pieces already captured

    for(auto move : getAllowedMoves(*piece,false))
    {
      m_blackPossibleMoves.push_back(move);
    }

    PieceInfo w_kingPosition(w_king.getX(),w_king.getY());
    auto kingCapturable = std::find(begin(m_blackPossibleMoves),end(m_blackPossibleMoves),w_kingPosition);
    if(kingCapturable != m_blackPossibleMoves.end())
    {
      isChecked = true;
      std::cout << "WHITE CHECKED" << std::endl;
    }
    else
    {
      isChecked = false;
    }
  }
  if(flag)
    selected->moveTo(current.x,current.y);
  return isChecked;
}

std::vector<PieceInfo> GameManager::filterAllowedMoves(std::vector<PieceInfo>& allowedMoves,PieceColor color)
{
  std::vector<PieceInfo> filteredMoves;
  for(auto move : allowedMoves)
  {
    if (color == WHITE)
    {
      if (!lookForWhiteCheck(move))
      {
        filteredMoves.push_back(move);
      }
    }
    else
    {
      if (!lookForBlackCheck(move))
        filteredMoves.push_back(move);
    }
  }
  return filteredMoves;
}

void GameManager::positionPieces(PieceColor color)
{
  if( color == BLACK)
  {
    //PIECEEEEEES
    w_pawn_1 = Pawn{0, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_2 = Pawn{1, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_3 = Pawn{2, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_4 = Pawn{3, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_5 = Pawn{4, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_6 = Pawn{5, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_7 = Pawn{6, 6, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_8 = Pawn{7, 6, PieceColor::WHITE, TEXTURE_PAWN_W};

    w_knight_1 = Knight{6,7 ,PieceColor::WHITE, TEXTURE_KNIGHT_W};
    w_knight_2 = Knight{1,7 ,PieceColor::WHITE, TEXTURE_KNIGHT_W};
    w_bishop_1 = Bishop{5,7, PieceColor::WHITE, TEXTURE_BISHOP_W};
    w_bishop_2 = Bishop{2,7, PieceColor::WHITE, TEXTURE_BISHOP_W};
    w_queen = Queen{4,7, PieceColor::WHITE, TEXTURE_QUEEN_W};
    w_king = King{3,7, PieceColor::WHITE, TEXTURE_KING_W};

    w_rook_1 = Rook{7,7,PieceColor::WHITE, TEXTURE_ROOK_W};
    w_rook_2 = Rook{0,7,PieceColor::WHITE, TEXTURE_ROOK_W};

    b_pawn_1 = Pawn{0, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_2 = Pawn{1, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_3 = Pawn{2, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_4 = Pawn{3, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_5 = Pawn{4, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_6 = Pawn{5, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_7 = Pawn{6, 1, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_8 = Pawn{7, 1, PieceColor::BLACK, TEXTURE_PAWN_B};

    b_rook_1 = Rook{0,0,PieceColor::BLACK, TEXTURE_ROOK_B};
    b_rook_2 = Rook{7,0,PieceColor::BLACK, TEXTURE_ROOK_B};

    b_bishop_2 = Bishop{2,0,PieceColor::BLACK, TEXTURE_BISHOP_B};
    b_bishop_1 = Bishop{5,0,PieceColor::BLACK, TEXTURE_BISHOP_B};
    b_knight_1 = Knight{1,0, PieceColor::BLACK, TEXTURE_KNIGHT_B};
    b_knight_2 = Knight{6,0, PieceColor::BLACK, TEXTURE_KNIGHT_B};

    b_queen = Queen{4,0,PieceColor::BLACK, TEXTURE_QUEEN_B};
    b_king = King{3,0,PieceColor::BLACK, TEXTURE_KING_B};
  }
  else
  {
    b_pawn_1 = Pawn{0, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_2 = Pawn{1, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_3 = Pawn{2, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_4 = Pawn{3, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_5 = Pawn{4, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_6 = Pawn{5, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_7 = Pawn{6, 6, PieceColor::BLACK, TEXTURE_PAWN_B};
    b_pawn_8 = Pawn{7, 6, PieceColor::BLACK, TEXTURE_PAWN_B};

    b_knight_1 = Knight{6,7 ,PieceColor::BLACK, TEXTURE_KNIGHT_B};
    b_knight_2 = Knight{1,7 ,PieceColor::BLACK, TEXTURE_KNIGHT_B};
    b_bishop_1 = Bishop{5,7, PieceColor::BLACK, TEXTURE_BISHOP_B};
    b_bishop_2 = Bishop{2,7, PieceColor::BLACK, TEXTURE_BISHOP_B};
    b_queen = Queen{3,7, PieceColor::BLACK, TEXTURE_QUEEN_B};
    b_king = King{4,7, PieceColor::BLACK, TEXTURE_KING_B};

    b_rook_1 = Rook{7,7,PieceColor::BLACK, TEXTURE_ROOK_B};
    b_rook_2 = Rook{0,7,PieceColor::BLACK, TEXTURE_ROOK_B};

    w_pawn_1 = Pawn{0, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_2 = Pawn{1, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_3 = Pawn{2, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_4 = Pawn{3, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_5 = Pawn{4, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_6 = Pawn{5, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_7 = Pawn{6, 1, PieceColor::WHITE, TEXTURE_PAWN_W};
    w_pawn_8 = Pawn{7, 1, PieceColor::WHITE, TEXTURE_PAWN_W};

    w_rook_1 = Rook{0,0,PieceColor::WHITE, TEXTURE_ROOK_W};
    w_rook_2 = Rook{7,0,PieceColor::WHITE, TEXTURE_ROOK_W};

    w_bishop_2 = Bishop{2,0,PieceColor::WHITE, TEXTURE_BISHOP_W};
    w_bishop_1 = Bishop{5,0,PieceColor::WHITE, TEXTURE_BISHOP_W};
    w_knight_1 = Knight{1,0, PieceColor::WHITE, TEXTURE_KNIGHT_W};
    w_knight_2 = Knight{6,0, PieceColor::WHITE, TEXTURE_KNIGHT_W};

    w_queen = Queen{3,0,PieceColor::WHITE, TEXTURE_QUEEN_W};
    w_king = King{4,0,PieceColor::WHITE, TEXTURE_KING_W};

  }
}



