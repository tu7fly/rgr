#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>

// ---------------- НАСТРОЙКИ ----------------

const int FISH_COUNT = 3;
const int BUBBLE_COUNT = 12;

// ---------------- ПАРАМЕТРЫ РЫБОК ----------------

float fishX[FISH_COUNT] = {-0.6f, 0.3f, 0.0f};
float fishY[FISH_COUNT] = {0.3f, -0.2f, 0.0f};
float fishSpeed[FISH_COUNT] = {0.008f, -0.006f, 0.01f};

float fishColor[FISH_COUNT][3] =
    {
        {1.0f, 0.5f, 0.0f},
        {0.2f, 0.8f, 0.3f},
        {0.8f, 0.3f, 0.9f}};

// 🔥 Счётчики ударов для каждой рыбы
int fishHits[FISH_COUNT] = {0, 0, 0};

// ---------------- ПАРАМЕТРЫ ПУЗЫРЬКОВ ----------------

float bubbleX[BUBBLE_COUNT];
float bubbleY[BUBBLE_COUNT];

// ---------------- РИСОВАНИЕ КРУГА ----------------

void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++)
    {
        float angle = 2.0f * 3.14159f * i / 30;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

// ---------------- РИСОВАНИЕ ТЕКСТА ----------------

void drawText(float x, float y, const char *text)
{
    glRasterPos2f(x, y);
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

// ---------------- РИСОВАНИЕ РЫБЫ ----------------

void drawFish(float x, float y, bool moveRight, int index)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    if (!moveRight)
        glScalef(-1, 1, 1);

    glColor3f(
        fishColor[index][0],
        fishColor[index][1],
        fishColor[index][2]);

    // Тело
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.0f, 0.06f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.0f, -0.06f);
    glEnd();

    // Хвост
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.2f, 0.07f);
    glVertex2f(-0.2f, -0.07f);
    glEnd();

    // Глаз
    glColor3f(0, 0, 0);
    drawCircle(0.05f, 0.02f, 0.01f);

    glPopMatrix();
}

// ---------------- ОТРИСОВКА ----------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Рамка аквариума
    glColor3f(0, 0.4f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.9f, -0.6f);
    glVertex2f(0.9f, -0.6f);
    glVertex2f(0.9f, 0.6f);
    glVertex2f(-0.9f, 0.6f);
    glEnd();

    // Рисуем рыб
    for (int i = 0; i < FISH_COUNT; i++)
    {
        drawFish(fishX[i], fishY[i], fishSpeed[i] > 0, i);
    }

    // Пузырьки
    glColor3f(0.8f, 0.9f, 1.0f);
    for (int i = 0; i < BUBBLE_COUNT; i++)
    {
        drawCircle(bubbleX[i], bubbleY[i], 0.02f);
    }

    // 🔥 Отображение счётчиков
    glColor3f(0, 0, 0);

    char buffer[50];

    for (int i = 0; i < FISH_COUNT; i++)
    {
        sprintf_s(buffer, "Fish %d hits: %d", i + 1, fishHits[i]);
        drawText(-0.85f, 0.7f - i * 0.08f, buffer);
    }

    glutSwapBuffers();
}

// ---------------- АНИМАЦИЯ ----------------

void timer(int)
{
    for (int i = 0; i < FISH_COUNT; i++)
    {
        fishX[i] += fishSpeed[i];

        // Если удар о стену
        if (fishX[i] > 0.85f || fishX[i] < -0.85f)
        {
            fishSpeed[i] = -fishSpeed[i];
            fishHits[i]++; // 🔥 увеличиваем счётчик конкретной рыбы
        }
    }

    // Движение пузырьков
    for (int i = 0; i < BUBBLE_COUNT; i++)
    {
        bubbleY[i] += 0.01f;

        if (bubbleY[i] > 0.6f)
            bubbleY[i] = -0.6f;
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// ---------------- MAIN ----------------

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Аквариум со счетчиками");

    glClearColor(0.6f, 0.85f, 1.0f, 1.0f);

    // Инициализация пузырьков
    for (int i = 0; i < BUBBLE_COUNT; i++)
    {
        bubbleX[i] = -0.9f + (rand() % 180) / 100.0f;
        bubbleY[i] = -0.6f + (rand() % 120) / 100.0f;
    }

    glutDisplayFunc(display);
    glutTimerFunc(30, timer, 0);
    glutMainLoop();

    return 0;
}
