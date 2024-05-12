#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(15.0f);
    while (!glfwWindowShouldClose(window)) {
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);


        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 0.5f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);
        glEnd();

    }

    glfwTerminate();
    return 0;
}

// compile  : g++ hello.cpp -o hello -lglfw -lGL