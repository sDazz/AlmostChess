#pragma once
#include "glm/glm.hpp"
#include "Texture.h"


#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 800.0f
#define BOARD_SIZE 8
#define PIECE_HORIZONTAL_SCALE 0.7f
#define PIECE_VERTICAL_SCALE 0.7f
#define CIRCLE_SCALE 0.3f
#define PAWN_HORIZONTAL_SCALE 0.55f

extern glm::vec4 BOARD_COLOR_1;
extern glm::vec4 BOARD_COLOR_2;

extern const float SQUARE_HEIGHT;
extern const float SQUARE_WIDTH;



enum PieceType
{
  PAWN = 0, BISHOP = 1, KNIGHT = 2, ROOK = 3, QUEEN = 4, KING = 5
};

enum PieceColor
{
  BLACK = 0, WHITE = 1
};


extern Texture* TEXTURE_PAWN_W;
extern Texture* TEXTURE_PAWN_B;

extern Texture* TEXTURE_BISHOP_W;
extern Texture* TEXTURE_BISHOP_B;

extern Texture* TEXTURE_KNIGHT_W;
extern Texture* TEXTURE_KNIGHT_B;

extern Texture* TEXTURE_ROOK_W;
extern Texture* TEXTURE_ROOK_B;

extern Texture* TEXTURE_QUEEN_W;
extern Texture* TEXTURE_QUEEN_B;

extern Texture* TEXTURE_KING_W;
extern Texture* TEXTURE_KING_B;

