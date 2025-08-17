#include <stdio.h>
#include <stdlib.h>
#define cols 25
#define rows 25
char board[rows][cols];
int isgameover=0;


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


int main()
{   
    draw_board();
    print_board();

}