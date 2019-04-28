//
// Created by danila on 28.04.19.
//

#include "graffic.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

std::vector<std::vector<double>>
normalise(const std::vector<std::vector<double>> &mat){
    double mx = mat[0][0];
    for(auto& line: mat){
        for(auto& it: line){
            mx = std::max(mx,it);
        }
    }

    std::vector<std::vector<double>> res(mat);

    if(mx > 1e-6){
        for(auto& line: res){
            for(auto& it: line){
                it /= mx;
            }
        }
        return res;
    }
    return mat;
}

void show_matrix(const std::vector<std::vector<double>> &mat,
        const std::string& name) {
    auto nmat = normalise(mat);

    if (!glfwInit())
    {
        std::cout<<"window creation error\n";
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, name.c_str(), NULL, NULL);

    glfwMakeContextCurrent(window);

    glClearColor( 1.0f, 1.0f, 1.0f, 0.f );

    glShadeModel( GL_FLAT );

    while (!glfwWindowShouldClose(window))
    {

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glLoadIdentity();

        glClearDepth(1.0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        width = 100;
        height = 100;

        glOrtho(0.0, nmat.size(), 0.0, nmat[0].size(), -1.0, 1.0);

        glBegin(GL_QUADS);
        for(size_t i=0;i<nmat.size(); ++i){
            for(size_t j=0;j<nmat[i].size();++j){
                glColor3f(nmat[i][j],0.0F,1-nmat[i][j]);
                glVertex3f(i, j, 0.0);
                glVertex3f(i, j+1, 0.0);
                glVertex3f(i+1, j+1, 0.0);
                glVertex3f(i+1, j, 0.0);
            }
        }
        glEnd();

        glFlush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

}

void show_node(double x, double y, double r){
    glBegin(GL_TRIANGLES);
    //glVertex2f(x,y);

    double rs = r*std::sqrt(2)/2;

    glVertex2f(x+r,y);
    glVertex2f(x+rs,y-rs);
    glVertex2f(x,y-r);

    glVertex2f(x+r,y);
    glVertex2f(x,y-r);
    glVertex2f(x-rs,y-rs);

    glVertex2f(x+r,y);
    glVertex2f(x-rs,y-rs);
    glVertex2f(x-r,y);

    glVertex2f(x+r,y);
    glVertex2f(x-r,y);
    glVertex2f(x-rs,y+rs);

    glVertex2f(x+r,y);
    glVertex2f(x-rs,y+rs);
    glVertex2f(x,y+r);

    glVertex2f(x+r,y);
    glVertex2f(x,y+r);
    glVertex2f(x+rs,y+rs);

    glEnd();
}

void show_graph(const draw_graph &g, const std::string& name) {
    if (!glfwInit())
    {
        std::cout<<"window creation error\n";
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, name.c_str(), NULL, NULL);

    glfwMakeContextCurrent(window);

    glClearColor( 1.0f, 1.0f, 1.0f, 0.f );

    glShadeModel( GL_FLAT );

    while (!glfwWindowShouldClose(window))
    {

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glLoadIdentity();

        glClearDepth(1.0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        width = 100;
        height = 100;

        glOrtho(0.0, g.maxx, 0.0, g.maxy, -1.0, 1.0);

        glColor3f(0,0,0);
        for(size_t i=0;i<g.g.edges.size(); ++i){
            for(size_t j=0;j<g.g.edges[i].size(); ++j){
                glBegin(GL_LINES);

                glVertex2f(g.x[i], g.y[i]);
                glVertex2f(g.x[g.g.edges[i][j]], g.y[g.g.edges[i][j]]);

                glEnd();
            }
        }

        if(g.node_colors.size() != g.x.size()) {
            glColor3f(0,0,0);
            for (size_t i = 0; i < g.x.size(); ++i) {
                show_node(g.x[i], g.y[i], 3);
            }
        }
        else{
            for (size_t i = 0; i < g.x.size(); ++i) {
                glColor3f(g.node_colors[i],0,1-g.node_colors[i]);
                show_node(g.x[i], g.y[i], std::max(3., g.node_colors[i]*10));
            }
        }

        glFlush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();


}
