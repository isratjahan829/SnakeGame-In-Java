#include <graphics.h>
#include <conio.h>
#include <string>

const int width = 26;
const int height = 26;
const int tileSize = 32;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

int difficulty = 0; // 0: Easy, 1: Medium, 2: Hard

void DrawIntro()
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    setcolor(YELLOW);
    outtextxy(220, 200, "Snake Game");

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(290, 300, "Press Enter to Play");

    while (1)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 13)  // Enter key
                break;
        }
    }
}

void DrawMenu()
{
    cleardevice();

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    outtextxy(250, 200, "***Game Menu***");

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);

    // Highlight the selected difficulty option
    if (difficulty == 0)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(320, 250, "1. Easy");

    if (difficulty == 1)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(315, 280, "2. Medium");

    if (difficulty == 2)
        setcolor(YELLOW);
    else
        setcolor(WHITE);
    outtextxy(320, 310, "3. Hard");
}

void SetDifficulty()
{
    cleardevice();
    DrawMenu();

    while (1)
    {
        if (kbhit())
        {
            char key = getch();
            switch (key)
            {
                case 'w':
                    difficulty = (difficulty - 1 + 3) % 3; // Wrap around options
                    DrawMenu();
                    break;
                case 's':
                    difficulty = (difficulty + 1) % 3;
                    DrawMenu();
                    break;
                case 13:  // Enter key
                    return;
            }
        }
    }
}

void DrawScore()
{
    std::string scoreStr = "Score: " + std::to_string(score);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    char scoreText[50]; // Create a char array with sufficient size
    strcpy(scoreText, scoreStr.c_str()); // Copy the string into the char array
    outtextxy(10, 5, scoreText);
}

void Setup()
{
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw()
{
    cleardevice();

    // Draw the snake's head
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x * tileSize + tileSize / 2, y * tileSize + tileSize / 2, tileSize / 2, tileSize / 2);

    // Draw the snake's tail
    for (int i = 0; i < nTail; i++)
    {
        setfillstyle(SOLID_FILL, GREEN);
        fillellipse(tailX[i] * tileSize + tileSize / 2, tailY[i] * tileSize + tileSize / 2, tileSize / 2, tileSize / 2);
    }

    // Draw the fruit
    setfillstyle(SOLID_FILL, RED);
    fillellipse(fruitX * tileSize + tileSize / 2, fruitY * tileSize + tileSize / 2, tileSize / 2, tileSize / 2);

    DrawScore();

    switch (difficulty)
    {
        case 0: // Easy
            delay(150);
            break;
        case 1: // Medium
            delay(50);
            break;
        case 2: // Hard
            delay(70);
            break;
    }
}


void Input()
{
    if (kbhit())
    {
        char key = getch();
        switch (key)
        {
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
                exit(0);
                break;
        }
    }
}

void DrawGameOver()
{
    cleardevice();

    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setcolor(RED);
    outtextxy(250, 200, "Game Over");

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(270, 300, "Press Enter to Restart");

    while (1)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 13)  // Enter key
            {
                SetDifficulty(); // Show the difficulty menu
                Setup(); // Reset the game state
                break;
            }
        }
    }
}

void DrawLoadingScreen()
{
    cleardevice();

    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    setcolor(YELLOW);
    outtextxy(250, 200, "Loading...");

    delay(1000); // Delay for the loading screen

    cleardevice();
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;


    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case LEFT:
            x = (x - 1 + width) % width;
            break;
        case RIGHT:
            x = (x + 1) % width;
            break;
        case UP:
            y = (y - 1 + height) % height;
            break;
        case DOWN:
            y = (y + 1) % height;
            break;
        default:
            break;
    }

    // Check if the snake hit itself
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            // Snake collided with its tail, game over
            delay(500); // Delay to show the collision
            DrawGameOver();
            Setup();
            return;
        }
    }

    // Check if the snake hit the wall in hard mode
    if (difficulty == 2 && (x == 0 || x == width - 1 || y == 0 || y == height - 1))
    {
        // Snake hit the wall, game over
        delay(500); // Delay to show the collision
        DrawGameOver();
        Setup();
        return;
    }

    if (x == fruitX && y == fruitY)
    {
        // Snake ate the fruit, increase the score and spawn a new fruit
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    initwindow(width * tileSize, height * tileSize);

    DrawIntro();

    SetDifficulty();

    DrawLoadingScreen();

    Setup();

    while (1)
    {
        Input();
        Logic();
        Draw();
    }

    closegraph();

    return 0;
}
