#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <string>

float playerX = 0.0f, playerY = -0.6f;
float playerSize = 0.025f;
int playerLives = 4;
float caminhoSize = 0.04;
float offsetX;
float offsetY;

float initialPlayerX = playerX;
float initialPlayerY = playerY;


int labirinto[30][30] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}
};


float jogadorCorR = 0.0f, jogadorCorG = 1.0f, jogadorCorB = 0.0f;
float labirintoCorR = 1.0f, labirintoCorG = 1.0f, labirintoCorB = 1.0f;

enum GameState { PLAYING, GAME_OVER, VICTORY };
GameState gameState = PLAYING;

void desenhaJogador() {
    glColor3f(jogadorCorR, jogadorCorG, jogadorCorB);
    glRectf(playerX, playerY, playerX + playerSize, playerY + playerSize);
}

void desenhaLabirinto() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    float labirintoWidth = 30 * caminhoSize;
    float labirintoHeight = 30 * caminhoSize;

    offsetX = -(15 * caminhoSize);
    offsetY = (15 * caminhoSize);

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            if (labirinto[i][j] == 1) {
                glColor3f(labirintoCorR, labirintoCorG, labirintoCorB);
                glRectf(offsetX + j * caminhoSize, offsetY - i * caminhoSize, offsetX + (j + 1) * caminhoSize, offsetY - (i + 1) * caminhoSize);
            }
        }
    }

    desenhaJogador();

    if (gameState == GAME_OVER) {
        glColor3f(1.0, 0.0, 0.0); // Cor vermelha
        glRasterPos2f(-0.5f, 0.0f);
        std::string gameOverMessage = "Derrota! Pressione Enter para recomeçar.";
        for (const char& character : gameOverMessage) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
        }
    }
    else if (gameState == VICTORY) {
        glColor3f(0.0, 1.0, 0.0); // Cor verde
        glRasterPos2f(-0.5f, 0.0f);
        std::string victoryMessage = "Vitória! Pressione Enter para recomeçar.";
        for (const char& character : victoryMessage) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
        }
    }
    else {
        glColor3f(1.0, 0.0, 0.0);
        glRectf(-1.0, 0.9, -1.0 + (playerLives * 0.1), 1.0);
    }

    glutSwapBuffers();
}

void moveJogador(int key, int x, int y) {
    if (gameState != PLAYING) {
        if (key == 13) { // 13 é o código ASCII da tecla "Enter"
            // Recomeça o jogo ao pressionar Enter
            gameState = PLAYING;
            playerLives = 4;
            playerX = initialPlayerX;
            playerY = initialPlayerY;
            jogadorCorR = 0.0f;
            jogadorCorG = 1.0f;
            jogadorCorB = 0.0f;
            labirintoCorR = 1.0f;
            labirintoCorG = 1.0f;
            labirintoCorB = 1.0f;
        }
        return;
    }

    float speed = 0.025f;

    float nextX = playerX;
    float nextY = playerY;

    switch (key) {
    case GLUT_KEY_UP:
        nextY += speed;
        break;
    case GLUT_KEY_DOWN:
        nextY -= speed;
        break;
    case GLUT_KEY_LEFT:
        nextX -= speed;
        break;
    case GLUT_KEY_RIGHT:
        nextX += speed;
        break;
    }

    int playerCellX = (int)((-offsetX + playerX + playerSize / 2) / caminhoSize);
    int playerCellY = (int)((offsetY - playerY - playerSize / 2) / caminhoSize);

    int nextCellX = (int)((-offsetX + nextX + playerSize / 2) / caminhoSize);
    int nextCellY = (int)((offsetY - nextY - playerSize / 2) / caminhoSize);

    if (labirinto[nextCellY][nextCellX] == 0) {
        playerX = nextX;
        playerY = nextY;
    }
    else {
        playerLives--;
        if (playerLives == 0) {
            gameState = GAME_OVER;
        }
    }

    if (playerY >= offsetY - caminhoSize) {
        gameState = VICTORY;
    }

    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
    if (gameState != PLAYING && key == 13) { // 13 é o código ASCII da tecla "Enter"
        gameState = PLAYING;
        playerLives = 4;
        playerX = initialPlayerX;
        playerY = initialPlayerY;
        jogadorCorR = 0.0f;
        jogadorCorG = 1.0f;
        jogadorCorB = 0.0f;
        labirintoCorR = 1.0f;
        labirintoCorG = 1.0f;
        labirintoCorB = 1.0f;
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        jogadorCorR = rand() / static_cast<float>(RAND_MAX);
        jogadorCorG = rand() / static_cast<float>(RAND_MAX);
        jogadorCorB = rand() / static_cast<float>(RAND_MAX);
        labirintoCorR = rand() / static_cast<float>(RAND_MAX);
        labirintoCorG = rand() / static_cast<float>(RAND_MAX);
        labirintoCorB = rand() / static_cast<float>(RAND_MAX);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Jogo de Labirinto");
    glutDisplayFunc(desenhaLabirinto);
    glutSpecialFunc(moveJogador);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouseClick);
    initialPlayerX = playerX;
    initialPlayerY = playerY;
    glutMainLoop();
    return 0;
}
