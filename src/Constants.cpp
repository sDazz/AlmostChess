#include "Constants.h"

glm::vec4 BOARD_COLOR_1 = glm::vec4(237.0f,205.0f,168.0f,255.0f) * 1.0f/255.0f;
glm::vec4 BOARD_COLOR_2 = glm::vec4(128.0f,98.0f,65.0f, 255.0f) * 1.0f/255.0f;

constexpr float SQUARE_HEIGHT = SCREEN_HEIGHT/BOARD_SIZE;
constexpr float SQUARE_WIDTH = SCREEN_WIDTH/BOARD_SIZE;

//TEXTUREEEEEEEEEEE
Texture* TEXTURE_PAWN_W = new Texture();
Texture* TEXTURE_PAWN_B = new Texture();

Texture* TEXTURE_BISHOP_W = new Texture();
Texture* TEXTURE_BISHOP_B = new Texture();

Texture* TEXTURE_KNIGHT_W = new Texture();
Texture* TEXTURE_KNIGHT_B = new Texture();

Texture* TEXTURE_ROOK_W = new Texture();
Texture* TEXTURE_ROOK_B = new Texture();

Texture* TEXTURE_QUEEN_W = new Texture();
Texture* TEXTURE_QUEEN_B = new Texture();

Texture* TEXTURE_KING_W = new Texture();
Texture* TEXTURE_KING_B = new Texture();









