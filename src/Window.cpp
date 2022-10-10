#include "Window.h"
#include "Constants.h"


Window::Window()
{
  /* Initialize the library */
  if (!glfwInit()) {
    std::cout << "glfwInit() failed" << std::endl;
  }

  /* Create a windowed mode window and its OpenGL context */
  m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "HeYo", NULL, NULL);
  if (!m_window) {
    std::cout << "failed to create window - glfw" << std::endl;
    glfwTerminate();
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(m_window);

  // Initialize GLEW
  GLCall(glewExperimental = GL_TRUE);
  GLCall(glewInit());
  glfwSetWindowUserPointer(m_window, this);
}

void Window::waitEvent(Renderer& renderer,Renderer& circleRenderer,GameManager& GameManager)
{
  while (!glfwWindowShouldClose(m_window)) {
    /* Render here */
    renderer.ClearBlack();
    GameManager.drawCurrent(renderer,circleRenderer);
    //GameManager.drawCircles(circleRenderer);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwWaitEvents();
    //rename it
    glfwSetMouseButtonCallback(m_window, onKey);
    glfwSetCursorPosCallback(m_window, moveCursor);
  }
}

