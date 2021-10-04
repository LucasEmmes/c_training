#include <stdio.h>
#include <assert.h>

char total, r, nx, ny, x, y, max;
char c[2];

void coord(char pos) {
    c[0] = pos % 9;
    c[1] = pos / 9;
}

void print_array(char arr[][9]) {
    for (char i = 0; i < 9; i++)
    {
        for (char j = 0; j < 9; j++)
        {
            printf("%d ", arr[i][j]);
        }
        
        printf("\n");
    }
    
}

void check_row(char sudoku[][9], char row, char allowed[]) {
    for (char i = 0; i < 9; i++)
    {
        if (sudoku[row][i]) {
            allowed[sudoku[row][i]-1] = 0;
        }
    }
}

void check_col(char sudoku[][9], char col, char allowed[]) {
    for (char i = 0; i < 9; i++)
    {
        if (sudoku[i][col]) {
            allowed[sudoku[i][col]-1] = 0;
        }
    }
}

void check_square(char sudoku[][9], char pos, char allowed[]) {
    coord(pos);
    char dx = (c[0]/3)*3;
    char dy = (c[1]/3)*3;
    for (char i = 0; i < 3; i++)
    {
        for (char j = 0; j < 3; j++)
        {
            if (sudoku[dy+i][dx+j]) {
                allowed[sudoku[dy+i][dx+j]-1] = 0;
            }
        }
    }
}

char compare(char l1[], char l2[], char size) {
    for (char i = 0; i < size; i++)
    {
        if (l1[i] != l2[i])
        {
            return 0;
        }
        
    }
    return 1;
}

char valid(char sudoku[][9]) {
    // Check rows
    for (char i = 0; i < 9; i++)
    {
        char taken[] = {0,0,0,0,0,0,0,0,0};
        for (char j = 0; j < 9; j++)
        {
            if (sudoku[i][j]) {
                if (taken[sudoku[i][j]-1]) {
                    return 0;
                } else {
                    taken[sudoku[i][j]-1]++;
                }
            }
        }
    }

    // Check cols
    for (char i = 0; i < 9; i++)
    {
        char taken[] = {0,0,0,0,0,0,0,0,0};
        for (char j = 0; j < 9; j++)
        {
            if (sudoku[j][i]) {
                if (taken[sudoku[j][i]-1]) {
                    return 0;
                } else {
                    taken[sudoku[j][i]-1]++;
                }
            }
        }
    }

    // Check squares
    for (char x = 0; x < 9; x++)
    {
        char taken[] = {0,0,0,0,0,0,0,0,0};
        char tx = (x%3)*3;
        char ty = (x/3)*3;
        for (char i = 0; i < 3; i++)
        {
            for (char j = 0; j < 3; j++)
            {
                if (sudoku[ty+i][tx+j]) {
                    if (taken[sudoku[ty+i][tx+j]]) {
                        return 0;
                    } else {
                        taken[sudoku[ty+i][tx+j]-1]++;
                    }
                }
            }
        }
    }
    
    return 1;
}

char solve(char sudoku[][9], char pos) {
    // CHECKS
    // assert(valid(sudoku));
    if (!valid(sudoku)) {
        printf("a");
    }
    if (pos == 4) {
        printf("b");
    }
    
    
    
    
    if (pos > max) {
        max = pos;
    }
    coord(pos);
    x = c[0];
    y = c[1];
 
    // If we have solved the sudoku, return 1 downwards
    if (pos == 81) {
        return 1;
    }

    // If the current spot is taken, we just pass along
    if (sudoku[y][x]) {
        return solve(sudoku, pos+1);
    }

    // List of possible values to check
    char allowed[9] = {1,1,1,1,1,1,1,1,1};

    // check row
    check_row(sudoku, y, allowed);
    // check col
    check_col(sudoku, y, allowed);
    // check block
    check_square(sudoku, pos, allowed);
    
    // So that we may return 0 if there are not valid options
    char empty = 1;

    // Iterate over options and test if available
    for (char i = 0; i < 9; i++)
    {
        if (allowed[i]) {
            empty = 0;
            // Modify sudoku
            sudoku[y][x] = i+1;

            // Recursively call
            r = solve(sudoku, pos+1);
            // If we solved it, return downwards
            if (r) {
                return r;
            }
        }
    }
    
    // If we end up here, then either
    // a: there were no options available, or
    // b: no option helped solve the sudoku
    sudoku[y][x] = 0;
    return 0;
    
}



int main(int argc, char const *argv[])
{

    char sudoku_base[9][9] = {
        {0,7,8,5,0,0,0,0,0},
        {0,0,3,0,0,7,8,0,0},
        {0,0,0,1,9,0,0,0,0},
        {0,0,7,0,0,0,2,9,0},
        {0,9,0,0,6,1,0,4,0},
        {0,0,0,0,0,4,0,0,0},
        {3,0,6,0,0,2,0,0,0},
        {0,1,0,0,0,0,0,0,4},
        {0,0,0,0,0,0,5,0,0}
        };

    // Correct result
    // 1 7 8 | 7 8 5 | 8 5 2
    // 2 5 9 | 5 9 4 | 9 4 7
    // 4 6 3 | 6 3 1 | 3 1 9
    // - - - - - - - - - - -
    // 5 4 1 | 4 1 3 | 1 3 8
    // 8 9 7 | 9 7 6 | 7 6 4
    // 3 2 6 | 2 6 9 | 6 9 1
    // - - - - - - - - - - -
    // 6 3 4 | 3 4 8 | 4 8 5
    // 7 1 5 | 1 5 2 | 5 2 3
    // 9 8 2 | 8 2 7 | 2 7 6


    // assert(valid(sudoku_base));

    char a[] = {1, 1, 0, 1, 1, 1, 0, 0, 1};
    char b[] = {0, 1, 1, 1, 0, 1, 0, 1, 0};
    char c[] = {1, 1, 1, 1, 1, 1, 1, 0, 1};
    char d[] = {1, 1, 1, 1, 1, 1, 0, 1, 0};
    char e[] = {0, 1, 1, 0, 1, 0, 1, 1, 1};
    char f[] = {1, 0, 1, 0, 1, 1, 1, 1, 0};
    char g[] = {0, 1, 0, 1, 1, 0, 1, 1, 1};
    char h[] = {1, 0, 1, 1, 1, 1, 1, 1, 1};
    char i[] = {1, 1, 1, 0, 0, 1, 1, 1, 1};

    // assert(solve(sudoku_base, 0) == 1);
    solve(sudoku_base, 0);
    print_array(sudoku_base);

    
}
