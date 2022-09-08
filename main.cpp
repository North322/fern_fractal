#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

#define ITERATAIONS_COUNT 50000
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

void resize(int width, int height) {}

double randDouble(double min, double max) {
  return min + (rand() / (RAND_MAX / (max - min)));
}

void drawPoint(double x, double y) {
  glBegin(GL_POINTS);
  glColor3d(0, 1, 0);
  glVertex2d(x, y);
  glEnd();
}

void drawString(std::string str, double xPos, double yPos) {
  int i = 0;
  glColor3d(1, 1, 1);
  while (str[i] != '\0') {
    glRasterPos2d(xPos, yPos);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
    xPos += 10;
    i++;
  }
}
void display() {
  double t, p, midX = WINDOW_WIDTH / 2, midY = WINDOW_HEIGHT / 2;
  int radius = (int)midY * 0.1;
  double x = 1.0, y = 0.0;

  for (int i = 0; i < ITERATAIONS_COUNT; i++) {
    p = randDouble(0.0, 1.0);
    t = x;

    if (p <= 0.85) {
      x = 0.84 * x - 0.045 * y;
      y = 0.045 * t + 0.86 * y + 1.6;
    } else if (p <= 0.92) {
      x = 0.25 * x - 0.26 * y;
      y = 0.23 * t + 0.25 * y + 1.6;
    } else if (p <= 0.99) {
      x = -0.135 * x + 0.28 * y;
      y = 0.26 * t + 0.245 * y + 0.44;
    } else {
      x = 0;
      y = 0.16 * y;
    }
    drawPoint(midX + round(radius * x), midY - round(radius * y) + 35);
  }

  std::string title = "RGZ Gorshkov Danil ABT-113";
  drawString(title, 300, 600);
  glutSwapBuffers();
}

void init() {
  std::srand(std::time(nullptr));
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Fern Leaf");
  glutReshapeFunc(resize);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
