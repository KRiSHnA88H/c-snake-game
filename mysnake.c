#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define cols 25
#define rows 25

char board[rows][cols];
int isgameover=0;
int eaten=1;

//drew the board
void draw_board()
{
    for(int i=0;i<cols;i++)
    {
        for(int j=0;j<rows;j++)
        {
            if(i==0||j==0||i==cols-1||j==rows-1)
            {
                board[i][j]='*';
            }
            else
            {
                board[i][j]=' ';
            }    
        }
    }
}
void clear_screen()
{
    system("cls");
}

//put the snake head in center
int posx= 12;
int posy= 12;
void snake()
{
    char snake='@';
    board[posx][posy]=snake;
}

//print changes in board[][]
void print_board()
{
    for(int i=0;i<cols;i++)
    {
        for(int j=0;j<rows;j++)
        {
           printf("%c",board[i][j]);
        }
        printf("\n");
    } 
    
}

//changes pos of snake head
void transform(int x,int y)
{
    posx+=x;
    posy+=y;
}

//takes input
void input()
{
    char m=getch();
    switch (m)
    {
    case 'W'|'w':
        transform(-1,0);
        break;
    case 'S'|'s':
        transform(1,0);break;
    case 'a'|'A':
        transform(0,-1);break;
    case 'd'|'D':
        transform(0,1);break;

    }
}

void collison()
{
    if(posx==rows-1|posx==0|posy==0|posy==cols-1)
    {
        isgameover=1;
    }

}
 int x,y;
void food()
{
   
    if(eaten)
    {
        int max=23,min=1;
        srand(time(NULL));
        x=(rand()%(max-min+1))+min;
        srand(time(NULL));
        y=(rand()%(max-min+1))+min;
    }
    
    board[x][y]='#';
}
void Eaten()
{
    if(posx==x&&posy==y)
    {
        eaten=1;
    }
    else
    {
        eaten=0;
    }
}

int main()
{   
    
    while(!isgameover)
    {
        
        draw_board();
        snake();
        food();
        print_board();
        input();
        Eaten();
        collison();
        clear_screen();
        
        
        

    }
    printf("Game Over");
    

}