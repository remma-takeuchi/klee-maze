#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <klee/klee.h>

#define H 7
#define W 11
#define ITERS 28
#define INTERVAL 500000

char maze[H][W] = {"+-+---+---+",
                   "| |     |#|",
                   "| | --+ | |",
                   "| |   | | |",
                   "| +-- | | |",
                   "|     |   |",
                   "+-----+---+"};

void draw()
{
    int i, j;
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int x, y;   //Player position
    int ox, oy; //Old player position
    int i = 0;  //Iteration number
    char program[ITERS];
    x = 1;
    y = 1;
    maze[y][x] = 'X';

    draw();
    printf("\nw:up, s:down, a:right, d:left\n");
    printf("Enter your command: \n");

#ifdef KLEE_ANALYSIS
    klee_make_symbolic(program, ITERS, "program");
#else
    scanf("%s", program);
#endif

    while (i < ITERS)
    {
        ox = x; //Save old player position
        oy = y;

        switch (program[i])
        {
        case 'w':
            y--;
            break;
        case 's':
            y++;
            break;
        case 'a':
            x--;
            break;
        case 'd':
            x++;
            break;
        default:
            printf("Wrong command!(only w,s,a,d accepted!)\n");
            printf("You lose!\n");
            exit(-1);
            break;
        }

        if (maze[y][x] == '#')
        {
            printf("You win!\n");
            printf("Your solution: \n%s\n", program);
#ifdef KLEE_ASSERT
            klee_assert(0);
#endif
            exit(1);
        }

        if (maze[y][x] != ' ' && !((y == 2 && maze[y][x] == '|' && x > 0 && x < W)))
        //if (maze[y][x] != ' ')
        {
            x = ox;
            y = oy;
        }

        if (ox == x && oy == y)
        {
            printf("You lose\n");
            exit(-2);
        }

        maze[y][x] = 'X';
        draw();

        i++;

#ifndef KLEE_ANALYSIS
        usleep(INTERVAL); //me wait to human
#endif
    }

    printf("You lose\n");
}
