 g++  -Iexternal -IPieces -I.\
  -g Constants.cpp Pieces/Pawn.cpp GameManager.cpp Window.cpp Pieces/Piece.cpp\
  Application.cpp Shader.cpp VertexArray.cpp VertexBuffer.cpp Texture.cpp\
  Renderer.cpp IndexBuffer.cpp\
 external/stb_image/stb_image.cpp\
 -std=c++20\
 -lsfml-graphics -lsfml-window -lsfml-system\
 -lglfw -lglut -lGLEW -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl  -o executable &&
./executable
