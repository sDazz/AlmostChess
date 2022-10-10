#pragma once

#include "pch.h"
#include "Renderer.h"
#include "Pieces/Bishop.h"
#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"
#include "Pieces/Queen.h"
#include "Pieces/Knight.h"
#include "Pieces/King.h"
#include "Pieces/Piece.h"
#include "Constants.h"
#include <GLFW/glfw3.h>




class GameManager
{
  private:
    Piece* selected = nullptr;
    PieceInfo m_cellToHighlight = PieceInfo(-1,-1);
    std::vector<Piece*> m_blackPieces;
    std::vector<Piece*> m_whitePieces;
    std::vector<PieceInfo> m_occupiedPositions;

    std::vector<PieceInfo> m_currentPossibleMoves;

    bool turn = false;  //white
    PieceInfo m_PawnTransform = PieceInfo(-1,-1);
    std::vector<PieceInfo> m_whitePossibleMoves;
    std::vector<PieceInfo> m_blackPossibleMoves;


    bool m_whiteCheck = false;
    bool m_blackCheck = false;


    PieceColor m_Player = WHITE; //white

  public:

    GameManager()
    {
      positionPieces(m_Player);
      genFullBoard();
    }
    ~GameManager();


    void select(Piece& piece);

    PieceInfo checkOccupiedPosition(PieceInfo checked);

    inline const std::vector<PieceInfo>* getOccupiedPositions() {return &m_occupiedPositions;}
    void setOccupiedPositions();
    Piece* getPieceByPosition(int xpos, int ypos);

    void drawCurrent(Renderer& rh,Renderer& circleRh);
    void drawCircles(Renderer& rh);

    void cursor_pos_callback(double xpos,double ypos);

    void genFullBoard();

    void click_callback(int xpos, int ypos,int button,int action);

    std::vector<PieceInfo> getAllowedMoves(Piece& piece, bool flag);
    std::vector<PieceInfo> getPossiblePawnMoves(Piece& piece, bool flag);
    std::vector<PieceInfo> getPossibleRookMoves(Piece& piece);
    std::vector<PieceInfo> getPawnCapture(Piece& piece);
    std::vector<PieceInfo> getPossibleBishopMoves(Piece& piece);
    std::vector<PieceInfo> getPossibleKingMoves(Piece& piece, bool flag);
    std::vector<PieceInfo> getPossibleQueenMoves(Piece& piece);
    std::vector<PieceInfo> getPossibleKnightMoves(Piece& piece);






    void resetBoard();
    void lookForCheck(PieceColor color);
    bool lookForWhiteCheck(const PieceInfo& h_move = PieceInfo());
    bool lookForBlackCheck(const PieceInfo& h_move = PieceInfo());
    std::vector<PieceInfo> filterAllowedMoves(std::vector<PieceInfo>& allowedMoves,PieceColor color);

    void dealWithCastle(Piece* selected);
    void dealWithPawnTransform(Piece* selected);
    void pawnTransform(Piece* piece, PieceType type);

    void positionPieces(PieceColor color);

  public:
    //&TEXTURES


    //PIECEEEEEES
    Pawn w_pawn_1;
    Pawn w_pawn_2;
    Pawn w_pawn_3;
    Pawn w_pawn_4;
    Pawn w_pawn_5;
    Pawn w_pawn_6;
    Pawn w_pawn_7;
    Pawn w_pawn_8;

    Knight w_knight_1;
    Knight w_knight_2;
    Bishop w_bishop_1;
    Bishop w_bishop_2;
    Queen w_queen;
    King w_king;

    Rook w_rook_1;
    Rook w_rook_2;

    Pawn b_pawn_1;
    Pawn b_pawn_2;
    Pawn b_pawn_3;
    Pawn b_pawn_4;
    Pawn b_pawn_5;
    Pawn b_pawn_6;
    Pawn b_pawn_7;
    Pawn b_pawn_8;

    Rook b_rook_1;
    Rook b_rook_2;

    Bishop b_bishop_2;
    Bishop b_bishop_1;
    Knight b_knight_1;
    Knight b_knight_2;

    Queen b_queen;
    King b_king;

};

