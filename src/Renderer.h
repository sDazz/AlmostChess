#pragma once
#include "pch.h"
#include "Constants.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Pieces/Piece.h"
#include <math.h>
#include "Pieces/Pawn.h"
#include "external/glm/ext/matrix_clip_space.hpp"
#include "external/glm/ext/matrix_transform.hpp"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"


class Renderer
{
  private:
    VertexArray *m_va;
    IndexBuffer *m_ib;
    glm::mat4 m_proj;
    glm::mat4 m_view;

    //shaders of interest
    Shader* m_pieceShader;
    Shader* m_boardShader;
    Shader* m_selectShader;


  public:
    Renderer(VertexArray* va,IndexBuffer*  ib, Shader* pieceShader, Shader* boardShader,Shader* selectShader)
      :m_va(va), m_ib(ib), m_pieceShader(pieceShader),m_boardShader(boardShader),
      m_selectShader(selectShader)
    {
      genMat4();
    }


    void genMat4();

    void ClearBlack () const;
    void draw(Shader* sh);
    void drawBoard(
                   const glm::vec4& color1, const glm::vec4& color2,
                   int cells);


    void highlightCell(const PieceInfo& position);
    void drawPiece(const Piece& piece);
    Shader* getSelectShader() { return m_selectShader;};
    void drawPawnTransform(const PieceInfo& position);

    void drawCircle(PieceInfo& position);
};





