#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int height = 30, width = 40;
char *SCORE = "Score: ";


void draw() ;

int main(void)
{
    char scoreString[10];
    char *gameOver = "GAME OVER";
    WINDOW *win = initscr();
    keypad(win, true);
    nodelay(win, true);

    int score = 0;
    int gameover = 0;

    int posX = width / 2;
    int posY = height / 2;
    
    int dirX = 1;
    int dirY = 0;

    int foodX;
    int foodY;
    label1:
        foodX = rand() % width;
        if (foodX == 0)
        {
            goto label1;
        }
    label2:
        foodY = rand() % height;
        if (foodY == 0)
        {
            goto label2;
        }


    while (!gameover)
    {
        draw();
        int pressed  = wgetch(win);
        if (pressed == KEY_LEFT)
        {
            dirX = -1;
            dirY = 0 ; 
        }
        if (pressed == KEY_RIGHT)
        {
            dirX = 1;
            dirY = 0;
        }
        if (pressed == KEY_UP)
        {
            dirX = 0;
            dirY = -1;
        }
        if (pressed == KEY_DOWN)
        {
            dirX = 0;
            dirY = 1; 
        }
        posX += dirX;
        posY += dirY;
        erase();

        mvaddstr(posY, posX, "0");
        mvaddstr(foodY, foodX, "*");
        mvaddstr(0, 0, SCORE);
        mvaddstr(0, strlen(SCORE) , scoreString);

        if (posX == foodX && posY == foodY)
        {
            score += 10;
            snprintf(scoreString, sizeof(scoreString), "%i\n" , score);
            label3:
                foodX = rand() % width;
                if (foodX == 0 || foodX == width)
                {
                    goto label3;
                }
                
            label4:
                foodY = rand() % height;
                if (foodY == 0 || foodY == height || foodY == 1)//added the 1 cause there is score in line 1 
                {
                    goto label4;
                }
        }
        if (posX <= 0 || posX >= width || posY <= 1 || posY >= height )
        {
            gameover = 1;
            
        }

        usleep(100000);
    }
    
    erase();
    mvaddstr(height / 2, width / 2 - strlen(gameOver), gameOver);
    mvaddstr(height / 2 + 1, width / 2 - strlen(scoreString), scoreString);
    refresh();
    usleep(3000000);
    
    
    endwin();
}

void draw() 
{ 
    //this loop starts at i = 1 cause in line 1 there is score.
    for (int i = 1; i < height; i++) 
    { 
        for (int j = 0; j < width; j++) 
        { 
            if (i == 1 || i == height - 1 || j == 0 || j == width - 1) 
            { 
                mvaddstr(i, j, "#"); 
            } 
            
        }  
    } 
} 