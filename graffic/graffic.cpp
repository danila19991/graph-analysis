//
// Created by danila on 28.04.19.
//

#include "graffic.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <random>
#include <algorithm>

constexpr double need_d = 20;

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

void show_graph(draw_graph &g, const std::string& name) {
    if (!glfwInit())
    {
        std::cout<<"window creation error\n";
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, name.c_str(), NULL, NULL);

    glfwMakeContextCurrent(window);

    glClearColor( 1.0f, 1.0f, 1.0f, 0.f );

    glShadeModel( GL_FLAT );

    int counter = 0;

    while (!glfwWindowShouldClose(window))
    {
        ++counter;
        if(counter > 50){
            iterate_draw_graph(g, 1e-2);
            counter = 0;
        }

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glLoadIdentity();

        glClearDepth(1.0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        width = 100;
        height = 100;

        glOrtho(0.0, g.maxx, 0.0, g.maxy, -1.0, 1.0);

        glColor3f(0.5,0.5,0.5);
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
                show_node(g.x[i], g.y[i], 2);
            }
        }
        else{
            for (size_t i = 0; i < g.x.size(); ++i) {
                glColor3f(g.node_colors[i],0,1-g.node_colors[i]);
                show_node(g.x[i], g.y[i], std::max(2., g.node_colors[i]*10));
            }
        }

        glFlush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();


}

draw_graph generate_start_positions(const graph &g) {
    draw_graph res;

    std::vector<double> x(g.edges.size()), y(g.edges.size());

    res.g = g;

    std::vector<std::pair<double, double>> p(g.edges.size());

    for(int i=0;i<g.edges.size();++i){
        p[i].first = (i%18)*50 + 50;
        p[i].second = (i/18)*50 + 50;
        //x[i] = (i%18)*50 + 50;
        //y[i] = (i/18)*50 + 50;
    }

    std::random_shuffle(p.begin(), p.end());

    for(int i=0;i<g.edges.size();++i){
        x[i] = p[i].first;
        y[i] = p[i].second;
    }

    res.maxy = 1000;
    res.maxx = 1000;
    res.x = x;
    res.y = y;

    return res;
}

std::mt19937 rnd;

void iterate_draw_graph(draw_graph &dg, double k) {
    std::vector<double> dx(dg.g.edges.size()), dy(dg.g.edges.size());

    for(size_t i=0;i<dg.g.edges.size();++i){
        dy[i] = dx[i] = 0;

        auto it = dg.g.edges[i].begin();

        for(size_t j=0; j<dg.g.edges.size();++j){
            if(i==j)
                continue;
            if(it != dg.g.edges[i].end() && *it == j){
                ++it;
                double v = std::sqrt((dg.x[i] - dg.x[j])*(dg.x[i] - dg.x[j]) +
                        (dg.y[i] - dg.y[j])*(dg.y[i] - dg.y[j]));

                if(abs(v) < 1){
                    continue;
                }

                if(v > need_d){
                    dx[i] += need_d/v*(dg.x[j] - dg.x[i]);
                    dy[i] += need_d/v*(dg.y[j] - dg.y[i]);
                }
                else{
                    dx[i] -= (dg.x[j] - dg.x[i])*(11-v)*10;
                    dy[i] -= (dg.y[j] - dg.y[i])*(11-v)*10;
                }
            }
            else{
                double v = std::sqrt((dg.x[i] - dg.x[j])*(dg.x[i] - dg.x[j]) +
                                     (dg.y[i] - dg.y[j])*(dg.y[i] - dg.y[j]));

                if(abs(v) < 1){
                    continue;
                }

                dx[i] -= (dg.x[j] - dg.x[i])/v/std::log(v);
                dy[i] -= (dg.y[j] - dg.y[i])/v/std::log(v);
            }
        }
    }

    for(size_t i=0;i<dg.g.edges.size();++i) {
        int t = rnd() % 100;
        if(t == 1){
            dg.x[i] += 2;
        }
        if(t == 3){
            dg.x[i] -= 2;
        }
        if(t == 7){
            dg.y[i] += 2;
        }
        if(t == 9){
            dg.y[i] -= 2;
        }

        dg.x[i] = std::min(std::max(1.0,dg.x[i] + dx[i]*k),dg.maxx-1);
        dg.y[i] = std::min(std::max(1.0,dg.y[i] + dy[i]*k),dg.maxy-1);


        std::cout<<dg.x[i]<<' '<<dg.y[i]<<' ';
        std::cout<<dx[i]<<' '<<dy[i]<<'\n';
    }

}
