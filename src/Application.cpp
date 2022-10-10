#include "Constants.h"
#include "pch.h"

#define GLEW_STATIC
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Window.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Constants.h"



int main() {

  Window window;

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  //TEXTUREEEEEEEEEEE
  TEXTURE_PAWN_W->make("../res/images/chessPieces/1024h/w_pawn_png_1024px.png");
  TEXTURE_PAWN_B->make("../res/images/chessPieces/1024h/b_pawn_png_1024px.png");

  TEXTURE_BISHOP_W->make("../res/images/chessPieces/1024h/w_bishop_png_1024px.png");
  TEXTURE_BISHOP_B->make("../res/images/chessPieces/1024h/b_bishop_png_1024px.png");

  TEXTURE_KNIGHT_W->make("../res/images/chessPieces/1024h/w_knight_png_1024px.png");
  TEXTURE_KNIGHT_B->make("../res/images/chessPieces/1024h/b_knight_png_1024px.png");

  TEXTURE_ROOK_W->make("../res/images/chessPieces/1024h/w_rook_png_1024px.png");
  TEXTURE_ROOK_B->make("../res/images/chessPieces/1024h/b_rook_png_1024px.png");

  TEXTURE_QUEEN_W->make("../res/images/chessPieces/1024h/w_queen_png_1024px.png");
  TEXTURE_QUEEN_B->make("../res/images/chessPieces/1024h/b_queen_png_1024px.png");

  TEXTURE_KING_W->make("../res/images/chessPieces/1024h/w_king_png_1024px.png");
  TEXTURE_KING_B->make("../res/images/chessPieces/1024h/b_king_png_1024px.png");

  float vertices[] = {
      // Position       Colors                Texcoords
      -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f, // top left
       0.5f,  0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f, // top right
       0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f, // bottom-right
      -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f, // bottom-left
  };
  float circleVertices[] = {
             0.5f,  0.5f, 0.0f,    1.0f,  1.0f, // top right
             0.5f, -0.5f, 0.0f,    1.0f, -1.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   -1.0f, -1.0f,// bottom left
            -0.5f,  0.5f, 0.0f,   -1.0f,  1.0f// top left
  };

  unsigned int elements[] = {0, 1, 2, 2, 3, 0};
  VertexArray vaCircle;
  VertexBuffer voCircle(circleVertices,3*2*4*sizeof(float));
  //unsigned int circleElements[] = {0,1,2,2,3,0};


  VertexBufferLayout circleLayout;
  circleLayout.Push<float>(3);
  circleLayout.Push<float>(2);

  vaCircle.AddBuffer(voCircle,circleLayout);

  IndexBuffer circleIB(&elements,6);

  // Create and bound VertexArray Object
  VertexArray va;
  // Crete and bound VertexBuffer object
  VertexBuffer vbo(vertices, 2 * 3 * 2 * 4 * sizeof(float));

  VertexBufferLayout layout;
  layout.Push<float>(2);
  layout.Push<float>(3);
  layout.Push<float>(2);

  va.AddBuffer(vbo, layout);

  IndexBuffer ib(&elements, 6);

  Shader boardShader("../res/shaders/Basic.shader");
  Shader selectShader("../res/shaders/select.shader");
  Shader pawnShader("../res/shaders/Pawn.shader");

  GameManager gameManager;
  window.setGameManager(gameManager);

  pawnShader.bind();
  pawnShader.SetUniform1i("u_Pawn", 0);

  selectShader.bind();
  selectShader.SetUniform4f("u_setColor",0.0f,0.6f,0.0f,0.5f);


  // still need to set uniforms, done in gameManager

  Renderer renderer(&va, &ib, &pawnShader,&boardShader,&selectShader);
  Renderer circleRenderer(&vaCircle, &circleIB, &pawnShader, &boardShader,&selectShader);
  window.waitEvent(renderer,circleRenderer,gameManager);

  glfwTerminate();
  return 0;
}


