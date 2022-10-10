#include "Renderer.h"



void Renderer::genMat4()
{
  m_proj = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f,-1.0f, 1.0f);
  m_view = glm::mat4(1.0f);
}

void Renderer::ClearBlack()const
{
  GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(Shader* sh)
{
  m_va->Bind();
  m_ib->Bind();
  sh->bind();
  GLCall(glDrawElements(GL_TRIANGLES, m_ib->getCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::drawBoard(
    const glm::vec4& color1, const glm::vec4& color2, int cells)
{
    m_boardShader->bind();
    bool flag = true;
    for(int j = 0; j < cells; j++)
    {
      int vertical = j* 800/8 + 800/16;
      for(int i = 0; i < cells ; i++)
      {
        glm::vec4 color;
        if (flag)
        {
          if (i%2) color = color1;
          else color = color2;
        }
        else
        {
          if (!(i%2)) color = color1;
          else color = color2;
        }

        int horizontal =i* 800/8 + 50;
        //translate, then scale.
        glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(horizontal, vertical,0));
        model = glm::scale(model, glm::vec3(800/8,800/8,0));
        glm::mat4 mvp =  m_proj * m_view * model;
        //need to fix these shader stuff

        m_boardShader->SetUniformMat4f("u_MVP",mvp);
        m_boardShader->SetUniformVec4("my_color",color);
        draw(m_boardShader);
      }
      flag = !flag;
    }
}
void Renderer::highlightCell(const PieceInfo& position)
{

  m_boardShader->bind();
  int horizontal = position.x * SCREEN_WIDTH/BOARD_SIZE + 50;
  int vertical = position.y * SCREEN_HEIGHT/BOARD_SIZE + SCREEN_HEIGHT/16;

  glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(horizontal, vertical,0));
  model = glm::scale(model, glm::vec3(800/8,800/8,0));
  glm::mat4 mvp =  m_proj * m_view * model;

  glm::vec4 color(0.0,0.3,0.0,0.3);

  m_boardShader->SetUniformMat4f("u_MVP",mvp);
  m_boardShader->SetUniformVec4("my_color",color);
  draw(m_boardShader);
}



void Renderer::drawPiece(const Piece& piece)//just pawn for now
{

  m_pieceShader->bind();
  piece.getTexture()->bind();
  glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(
        piece.getX()*SQUARE_WIDTH + SQUARE_WIDTH/2,
        piece.getY()*SQUARE_HEIGHT + SQUARE_HEIGHT/2,
        0));
  if(piece.getType() == PAWN)
  {
    model = glm::scale(model, glm::vec3(PAWN_HORIZONTAL_SCALE * SQUARE_WIDTH,PIECE_VERTICAL_SCALE * SQUARE_HEIGHT,0));
  }
  else
  {
    model = glm::scale(model, glm::vec3((PIECE_HORIZONTAL_SCALE) * SQUARE_WIDTH,PIECE_VERTICAL_SCALE * SQUARE_HEIGHT,0));
  }


  glm::mat4 mvp;

  mvp = m_proj * m_view * model;
  m_pieceShader->SetUniformMat4f("u_MVP",mvp);
  draw(m_pieceShader);

}


void Renderer::drawCircle(PieceInfo& position)
{

  m_selectShader->bind();
  glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(
        position.x*SQUARE_WIDTH + SQUARE_WIDTH/2,
        position.y*SQUARE_HEIGHT + SQUARE_HEIGHT/2,
        0));


  model = glm::scale(model, glm::vec3(CIRCLE_SCALE * SQUARE_WIDTH,CIRCLE_SCALE * SQUARE_HEIGHT,0));
  //glm::mat4 model = glm::mat4(1.0);

  glm::mat4 mvp;

  mvp = m_proj * m_view * model;
  m_selectShader->SetUniformMat4f("u_MVP",mvp);

  draw(m_selectShader);
}


void Renderer::drawPawnTransform(const PieceInfo& position)
{
  int horizontal;
  int vertical = position.y ;
  if(position.x == 7)
  {
    horizontal = (position.x - 1);
  }
  else
  {
    horizontal = (position.x + 1);
  }
  switch(position.y)
  {
    case(7):
      {
        //from 1 to 4 'cause that correspond to the PieceType enum for bishop to queen.
        for(int i = 1 ; i < 5; i++)
        {
          m_boardShader->bind();
          int current_vertical = vertical - i + 1;

          horizontal = (horizontal == 0 ? 1 : horizontal);
          glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(
                horizontal  * SCREEN_WIDTH/BOARD_SIZE + 50,
                current_vertical * SCREEN_HEIGHT/BOARD_SIZE + SCREEN_HEIGHT/16,
                0));
          model = glm::scale(model, glm::vec3(800/8 + 10,800/8 + 10,0));
          glm::mat4 mvp =  m_proj * m_view * model;

          glm::vec4 color(0.0,0.0,0.0,0.3);

          m_boardShader->SetUniformMat4f("u_MVP",mvp);
          m_boardShader->SetUniformVec4("my_color",color);
          draw(m_boardShader);
          switch(i)
          {
            case(PieceType::BISHOP):
              {
                Bishop bishop(horizontal,current_vertical,BLACK,TEXTURE_BISHOP_B);
                drawPiece(bishop);
                break;
              }
              case(PieceType::KNIGHT):
              {
                Knight knight(horizontal,current_vertical,BLACK,TEXTURE_KNIGHT_B);
                drawPiece(knight);
                break;
              }
              case(PieceType::ROOK):
              {
                 Rook rook(horizontal,current_vertical,BLACK,TEXTURE_ROOK_B);
                 drawPiece(rook);
                 break;
              }
              case(PieceType::QUEEN):
              {
                 Queen queen(horizontal,current_vertical,BLACK,TEXTURE_QUEEN_B);
                 drawPiece(queen);
                 break;
              }
          }
        }
        break;
      }
    case(0):
      {
        for(int i = 1; i < 5 ; i++)
        {
          m_boardShader->bind();
          int current_vertical = vertical + i - 1;

          horizontal = (horizontal == 0 ? 1 : horizontal);
          glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(
                horizontal  * SCREEN_WIDTH/BOARD_SIZE + 50,
                current_vertical * SCREEN_HEIGHT/BOARD_SIZE + SCREEN_HEIGHT/16,
                0));


          model = glm::scale(model, glm::vec3(800/8 + 10,800/8 + 10,0));
          glm::mat4 mvp =  m_proj * m_view * model;

          glm::vec4 color(0.0,0.0,0.0,0.3);

          m_boardShader->SetUniformMat4f("u_MVP",mvp);
          m_boardShader->SetUniformVec4("my_color",color);
          draw(m_boardShader);
          switch(i)
          {
            case(PieceType::BISHOP):
              {
                Bishop bishop(horizontal,current_vertical,BLACK,TEXTURE_BISHOP_W);
                drawPiece(bishop);
                break;
              }
              case(PieceType::KNIGHT):
              {
                Knight knight(horizontal,current_vertical,WHITE,TEXTURE_KNIGHT_W);
                drawPiece(knight);
                break;
              }
              case(PieceType::ROOK):
              {
                 Rook rook(horizontal,current_vertical,WHITE,TEXTURE_ROOK_W);
                 drawPiece(rook);
                 break;
              }
              case(PieceType::QUEEN):
              {
                 Queen queen(horizontal,current_vertical,WHITE,TEXTURE_QUEEN_W);
                 drawPiece(queen);
                 break;
              }
          }
        }
        break;
      }
  }
}








