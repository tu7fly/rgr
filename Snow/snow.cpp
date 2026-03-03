#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#define WIDTH 80
#define HEIGHT 60
#define CELL 10      // размер клетки
#define TIMER 50     // задержка анимации (мс)

int field[HEIGHT][WIDTH];

/* Инициализация поля */
void initField() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            field[i][j] = 0;
}

/* Один шаг снегопада */
void snowfall() {
    // движение снега вниз (снизу вверх!)
    for (int i = HEIGHT - 2; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 1 && field[i + 1][j] == 0) {
                field[i][j] = 0;
                field[i + 1][j] = 1;
            }
        }
    }

    // генерация новых снежинок сверху
    for (int j = 0; j < WIDTH; j++) {
        if (rand() % 8 == 0) {
            if (field[0][j] == 0)
                field[0][j] = 1;
        }
    }
}

/* Отрисовка поля */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0); // белый снег

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

    glutSwapBuffers();
}

/* Таймер анимации */
void timer(int value) {
    snowfall();
    glutPostRedisplay();
    glutTimerFunc(TIMER, timer, 0);
}

/* Настройка OpenGL */
void initGL() {
    glClearColor(0.0, 0.0, 0.2, 1.0); // тёмно-синий фон
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH * CELL, 0, HEIGHT * CELL);
}

/* Главная функция */
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