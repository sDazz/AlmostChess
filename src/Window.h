#pragma once
#include "Constants.h"
#include <GLFW/glfw3.h>
#include "GameManager.h"
#include "Renderer.h"


class Window
{
  //DO NOT PUT MORE MEMBERS INTO THIS SHI
  //Actually..........
  private:
    GLFWwindow* m_window;
    GameManager* m_GamePointer;

    static void onKey(GLFWwindow* window,int button,int action,int mods)
    {
      Window* obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
      //be AWARE OF THIS SHIT ^^^^

      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);
      obj->onKey(xpos,ypos,button,action,mods);
    }
    static void moveCursor(GLFWwindow* window,double xpos, double ypos)
    {
      Window* obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
      obj->moveCursor(xpos,ypos);
    }

  public:
    Window();
    ~Window()
    {
      glfwDestroyWindow(m_window);
    }

    void setGameManager(GameManager& gamePointer){ m_GamePointer = &gamePointer;}

    GameManager* getGameManager(){return m_GamePointer;}

    void onKey(int xpos, int ypos, int button,int action,int mods)
    {
      m_GamePointer->click_callback(xpos,ypos,button,action);
    }

    void moveCursor(double xpos, double ypos)
    {
      m_GamePointer->cursor_pos_callback(xpos,ypos);
    }


    //bool isOkay() const {return m_status;}
    void waitEvent( Renderer& renderer,Renderer& circleRenderer,  GameManager& GameManager);//event driven

};
