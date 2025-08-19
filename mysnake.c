#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define cols 25
#define rows 25

char board[rows][cols];
int isgameover=0;
int eaten=1;
int snake_len=1;

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
int a[256][2];

void snake()
{
    char snake='@';
    a[0][0]=posx;
    a[0][1]=posy;
    
    for(int i=snake_len;i>0;i--)
    {
        a[i][0]=a[i-1][0];
        a[i][1]=a[i-1][1];
    }
    for(int k=snake_len;k>0;k--)
    {
        board[a[k][0]][a[k][1]]=snake;
    }
    

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
    case 'w':
        transform(-1,0);
        break;
    case 's':
        transform(1,0);break;
    case 'a':
        transform(0,-1);break;
    case 'd':
        transform(0,1);break;

    }
}

void collison()
{
    if(posx==rows-1||posx==0||posy==0||posy==cols-1)
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
        x=(rand()%(max-min+1))+min;
        y=(rand()%(max-min+1))+min;
    }
    if(x==posx&&y==posy){x=2,y=4;}
    board[x][y]='#';
}
void Eaten()
{
    if(posx==x&&posy==y)
    {
        eaten=1;
        snake_len+=1;
        
    }
    else
    {
        eaten=0;
    }
}

int main()
{   
    srand(time(NULL));
    
    while(!isgameover)
    {
        clear_screen();
        draw_board();
        snake();
        food();
        print_board();
        input();
        Eaten(); 
        collison();
        
        
        
        

    }
    printf("Game Over");
    

}