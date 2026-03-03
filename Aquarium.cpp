// Подключаем библиотеку OpenGL через freeglut
#include <GL/glut.h>

// Для генерации случайных чисел
#include <cstdlib>

// Для функций sin() и cos()
#include <cmath>

// ---------------- НАСТРОЙКИ ----------------

// Количество рыбок
const int FISH_COUNT = 3;

// Количество пузырьков
const int BUBBLE_COUNT = 12;

// ---------------- ПАРАМЕТРЫ РЫБОК ----------------

// Координаты по X
float fishX[FISH_COUNT] = { -0.6f, 0.3f, 0.0f };

// Координаты по Y
float fishY[FISH_COUNT] = { 0.3f, -0.2f, 0.0f };

// Скорости движения
float fishSpeed[FISH_COUNT] = { 0.008f, -0.006f, 0.01f };

// Цвет каждой рыбки (R, G, B)
float fishColor[FISH_COUNT][3] =
{
    {1.0f, 0.5f, 0.0f},  // оранжевая
    {0.2f, 0.8f, 0.3f},  // зелёная
    {0.8f, 0.3f, 0.9f}   // фиолетовая
};

// ---------------- ПАРАМЕТРЫ ПУЗЫРЬКОВ ----------------

float bubbleX[BUBBLE_COUNT];
float bubbleY[BUBBLE_COUNT];

// ---------------- ФУНКЦИЯ РИСОВАНИЯ КРУГА ----------------
void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 30; i++)
    {
        float angle = 2.0f * 3.14159f * i / 30;

        glVertex2f(
            x + r * cos(angle),
            y + r * sin(angle)
        );
    }

    glEnd();
}

// ---------------- ФУНКЦИЯ РИСОВАНИЯ РЫБКИ ----------------
void drawFish(float x, float y, bool moveRight, int index)
{
    glPushMatrix();             // сохраняем текущее состояние
    glTranslatef(x, y, 0);      // перемещаем рыбку

    if (!moveRight)
        glScalef(-1, 1, 1);     // отражение при движении влево

    // Цвет рыбки
    glColor3f(
        fishColor[index][0],
        fishColor[index][1],
        fishColor[index][2]
    );

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

    glPopMatrix();              // возвращаем состояние
}

// ---------------- ФУНКЦИЯ ОТРИСОВКИ ----------------
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

    // Рисуем рыбок
    for (int i = 0; i < FISH_COUNT; i++)
    {
        drawFish(
            fishX[i],
            fishY[i],
            fishSpeed[i] > 0,
            i
        );
    }

    // Рисуем пузырьки
    glColor3f(0.8f, 0.9f, 1.0f);
    for (int i = 0; i < BUBBLE_COUNT; i++)
    {
        drawCircle(bubbleX[i], bubbleY[i], 0.02f);
    }

    glutSwapBuffers();
}

// ---------------- ФУНКЦИЯ АНИМАЦИИ ----------------
void timer(int)
{
    // Движение рыб
    for (int i = 0; i < FISH_COUNT; i++)
    {
        fishX[i] += fishSpeed[i];

        // Отскок от стен
        if (fishX[i] > 0.85f || fishX[i] < -0.85f)
            fishSpeed[i] = -fishSpeed[i];
    }

    // Движение пузырьков вверх
    for (int i = 0; i < BUBBLE_COUNT; i++)
    {
        bubbleY[i] += 0.01f;

        if (bubbleY[i] > 0.6f)
            bubbleY[i] = -0.6f;
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// ---------------- ГЛАВНАЯ ФУНКЦИЯ ----------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);

    glutCreateWindow("Аквариум с рыбками");

    // Цвет воды
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