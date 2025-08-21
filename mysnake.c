#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define ROWS 25
#define COLS 25
#define MAX_LEN 256

char board[ROWS][COLS];
int isgameover = 0;
int eaten = 1;
int snake_len = 1;
int dx = 1, dy = 0;

// snake head position
int posx = ROWS / 2;
int posy = COLS / 2;

// snake body coords
int a[MAX_LEN][2];

// food position
int foodx, foody;

// timing
clock_t last = 0;
int delay = 150; // ms

// draw empty board
void draw_board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1) {
                board[i][j] = '*';
            } else {
                board[i][j] = ' ';
            }
        }
    }
}

// snake drawing
void snake() {
    // update body coords
    for (int i = snake_len; i > 0; i--) {
        a[i][0] = a[i - 1][0];
        a[i][1] = a[i - 1][1];
    }
    a[0][0] = posx;
    a[0][1] = posy;

    for (int k = 0; k < snake_len; k++) {
        if (k == 0)
            board[a[k][0]][a[k][1]] = '@'; // head
        else
            board[a[k][0]][a[k][1]] = 'O'; // body
    }
}

// print board (buffered)
void print_board() {
    fflush(stdout);
    printf("\033[H"); // move cursor to top-left instead of clearing
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1)
            printf("\033[35m%c\033[0m",board[i][j]);
            else if(i==foodx && j==foody) printf("\033[31m%c\033[0m",board[i][j]);
            else
            printf("\033[32m%c\033[0m",board[i][j]);
            
            
        }
       

        printf("%c",'\n');
    }
}

// move snake
void transform(int x, int y) {
    posx += x;
    posy += y;
}

// input
void input() {
    if (_kbhit()) {
        int m = _getch();

        // check if it's an arrow key (two-byte sequence)
        if (m == 0 || m == 224) {
            int arrow = _getch(); // read the actual code
            switch (arrow) {
            case 72: // Up
                if (dx != 1 || snake_len == 1) {
                    dx = -1;
                    dy = 0;
                }
                break;
            case 80: // Down
                if (dx != -1 || snake_len == 1) {
                    dx = 1;
                    dy = 0;
                }
                break;
            case 75: // Left
                if (dy != 1 || snake_len == 1) {
                    dx = 0;
                    dy = -1;
                }
                break;
            case 77: // Right
                if (dy != -1 || snake_len == 1) {
                    dx = 0;
                    dy = 1;
                }
                break;
            }
        } else {
            // WASD controls
            switch (m) {
            case 'w':
                if (dx != 1 || snake_len == 1) {
                    dx = -1;
                    dy = 0;
                }
                break;
            case 's':
                if (dx != -1 || snake_len == 1) {
                    dx = 1;
                    dy = 0;
                }
                break;
            case 'a':
                if (dy != 1 || snake_len == 1) {
                    dx = 0;
                    dy = -1;
                }
                break;
            case 'd':
                if (dy != -1 || snake_len == 1) {
                    dx = 0;
                    dy = 1;
                }
                break;
            case 'q': // quit
                isgameover = 1;
                break;
            }
        }
    }
}


// check collision
void collision() {
    if (posx == ROWS - 1 || posx == 0 || posy == 0 || posy == COLS - 1) {
        isgameover = 1;
    }

    // check self collision
    for (int i = 1; i < snake_len; i++) {
        if (posx == a[i][0] && posy == a[i][1]) {
            isgameover = 1;
        }
    }
}

// food
void food() {
    if (eaten) {
        int max = ROWS - 2, min = 1;
        foodx = (rand() % (max - min + 1)) + min;
        foody = (rand() % (max - min + 1)) + min;
        eaten = 0;
    }
    board[foodx][foody] = '#';
}

// check eaten
void Eaten() {
    if (posx == foodx && posy == foody) {
        eaten = 1;
        snake_len++;
        if (snake_len >= MAX_LEN) {
            printf("You won!\n");
            exit(0);
        }
    }
}

int main() {
    int difficulty = 0;
    srand(time(NULL));
    printf("========== Snake Game ==========\n");
    printf("Controls:\n");
    printf("  Use ARROW KEYS to move the snake\n");
    printf("     Arrow UP or w : Move Up\n");
    printf("     Arrow Down or s : Move Down\n");
    printf("     Arrow Left or a : Move Left\n");
    printf("     Arrow Right  or d: Move Right\n");

    printf("Choose Difficulty (1 = Easy, 2 = Medium, 3 = Hard): ");
    if (scanf("%d", &difficulty) != 1) {
        printf("Invalid input! Defaulting to Medium.\n");
        difficulty = 2;
    }

    switch (difficulty) {
    case 1: delay = 125; break; // Easy
    case 2: delay = 100; break; // Medium
    case 3: delay = 50; break;  // Hard
    default:
        printf("Invalid choice! Defaulting to Medium.\n");
        delay = 100;
        break;
    }
    system("cls");

    // hide cursor for clean rendering
   printf("\033[?25l");

    last = clock();

    // Move cursor to top-left initially
    printf("\033[H");

    while (!isgameover) {
        input();
         

        clock_t now = clock();
        if ((now - last) * 1000 / CLOCKS_PER_SEC >= delay) {
            transform(dx, dy);
            Eaten();
            collision();
            last = now;
            

            draw_board();
            snake();
            food();
            print_board();
        }
    }

    // restore cursor
    printf("\033[?25h");

    printf("Game Over!\n");
    return 0;
}
