#include <GLFW/glfw3.h>
#include <iostream>

void redimensiona(int w, int h)
{
  glViewport(0, 0, w, h);
  float aspect = (float)w / (float)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w >= h)
    glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, 1.0, -1.0);
  else
    glOrtho(-10.0, 10.0, -10.0 / aspect, 10.0 / aspect, 1.0, -1.0);
}

int main()
{
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(640, 480, "ViewPort", NULL, NULL);
  if (!window)
  {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(2.0f);

  while (!glfwWindowShouldClose(window))
  {
    int largura, altura;
    glfwGetFramebufferSize(window, &largura, &altura);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
      
    redimensiona(largura, altura);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-2.5f, -2.5f, 0.0f);
    glVertex3f(2.5f, -2.5f, 0.0f);
    glVertex3f(2.5f, 2.5f, 0.0f);
    glVertex3f(-2.5f, 2.5f, 0.0f);
    glEnd();
  }

  glfwTerminate();
  return 0;
}

// compile  : g++ hello.cpp -o hello -lglfw -lGL