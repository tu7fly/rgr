#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAX_BUBBLES = 50;
const int WIDTH = 800;
const int HEIGHT = 600;

const int POT_LEFT = 100;
const int POT_RIGHT = WIDTH - 100;
const int POT_BOTTOM = 60;
const int POT_TOP = HEIGHT;

int bubbleCounter = 0;
char counterText[50];

struct Bubble {
    float x, y;
    float size;
    bool active;
};

Bubble bubbles[MAX_BUBBLES];

void init() {
    srand(time(0));

    for (int i = 0; i < MAX_BUBBLES; i++) {
        bubbles[i].active = false;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawBubble(float x, float y, float radius) {
    glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5f, 0.5f, 0.5f);
    glRectf(POT_LEFT, POT_BOTTOM, POT_RIGHT, 0);
    glRectf(POT_LEFT - 20, POT_TOP, POT_LEFT, 0);
    glRectf(POT_RIGHT, POT_TOP, POT_RIGHT + 20, 0);

    glColor3f(0.0f, 0.3f, 0.8f);
    glRectf(POT_LEFT, POT_TOP, POT_RIGHT, POT_BOTTOM);

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < MAX_BUBBLES; i++) {
        if (bubbles[i].active) {
            drawBubble(bubbles[i].x, bubbles[i].y, bubbles[i].size);
        }
    }

    glColor3f(1.0f, 1.0f, 0.0f);
    sprintf(counterText, "Bubbles: %d", bubbleCounter);
    drawText(20, HEIGHT - 30, counterText);

    glutSwapBuffers();
}

void update(int value) {
    if (rand() % 100 < 5) {
        for (int i = 0; i < MAX_BUBBLES; i++) {
            if (!bubbles[i].active) {
                bubbles[i].x = POT_LEFT + 10 + rand() % (POT_RIGHT - POT_LEFT - 20);
                bubbles[i].y = POT_BOTTOM + 5;
                bubbles[i].size = 3.0f;
                bubbles[i].active = true;
                bubbleCounter++;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_BUBBLES; i++) {
        if (bubbles[i].active) {
            bubbles[i].y += 2.0f;
            bubbles[i].size += 0.15f;


            if (bubbles[i].y + bubbles[i].size >= POT_TOP - 5) {
                bubbles[i].active = false;
                bubbleCounter--;
            }
            else if (bubbles[i].size > 25.0f) {
                bubbles[i].active = false;
                bubbleCounter--;
            }
            else if (bubbles[i].x - bubbles[i].size < POT_LEFT ||
                     bubbles[i].x + bubbles[i].size > POT_RIGHT) {
                bubbles[i].active = false;
                bubbleCounter--;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bubbles");

    init();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}