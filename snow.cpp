#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h> 
#include <stdio.h>  // для sprintf
#include <string.h> // для работы со строками (если нужно)
#define WIDTH 80
#define HEIGHT 60
#define CELL 10      // ðàçìåð êëåòêè
#define TIMER 250    // çàäåðæêà àíèìàöèè (ìñ)

int field[HEIGHT][WIDTH];

/* Èíèöèàëèçàöèÿ ïîëÿ */
void initField() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            field[i][j] = 0;
}

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}


int count = 0;
/* Îäèí øàã ñíåãîïàäà */
void snowfall() {

    // движение вниз
    for (int i = HEIGHT - 2; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 1 && field[i + 1][j] == 0) {
                field[i][j] = 0;
                field[i + 1][j] = 1;
            }
        }
    }

    // проверка нижней строки (снежинка упала)
    for (int j = 0; j < WIDTH; j++) {
        if (field[HEIGHT - 1][j] == 1) {
            count++;
            field[HEIGHT - 1][j] = 0;
        }
    }

    // генерация новых снежинок сверху
    for (int j = 0; j < WIDTH; j++) {
        if (rand() % 8 == 0) {
            if (field[0][j] == 0) {
                field[0][j] = 1;
            }
        }
    }
}

/* Îòðèñîâêà ïîëÿ */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // áåëûé ñíåã
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 1) {
                int x = j * CELL;
                int y = (HEIGHT - i) * CELL;

                glBegin(GL_QUADS);
                glVertex2i(x, y);
                glVertex2i(x + CELL, y);
                glVertex2i(x + CELL, y - CELL);
                glVertex2i(x, y - CELL);
                glEnd();
            }
        }
    }

    char buffer[50];
    sprintf(buffer, "Snow count: %d", count);
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(10.0f, HEIGHT * CELL - 40.0f, buffer);

    glutSwapBuffers();
}

/* Òàéìåð àíèìàöèè */
void timer(int value) {
    snowfall();
    glutPostRedisplay();
    glutTimerFunc(TIMER, timer, 0);
}

/* Íàñòðîéêà OpenGL */
void initGL() {
    glClearColor(0.0, 0.0, 0.2, 1.0); // ò¸ìíî-ñèíèé ôîí
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH * CELL, 0, HEIGHT * CELL);
}

/* Ãëàâíàÿ ôóíêöèÿ */
int main(int argc, char** argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH * CELL, HEIGHT * CELL);
    glutCreateWindow("Snowfall - GLUT");

    initField();
    initGL();

    glutDisplayFunc(display);
    glutTimerFunc(TIMER, timer, 0);

    glutMainLoop();
    return 0;
}
