#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char grid_coordinates[2];

/* Takes in two lists and their size. Compares the first <size> elements
 * Returns 1/0 for True/False
 */
char compare_lists(char a[], char b[], char size) {
    for (char i = 0; i < size; i++)
    {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
void compare_lists_test() {
    char x[] = {1,2,3};
    char y[] = {1,2,3};
    char z[] = {3,2,1};
    assert(compare_lists(x, y, 3));
    assert(!compare_lists(z, y, 3));
}


/* Takes in a position on the grid (global cell number) and
 * converts it into cartesian coordinates (both 0-indexed)
 * RETURNS: List[x, y]
 */
char* get_coordinates(char position) {
    grid_coordinates[0] = position % 9;
    grid_coordinates[1] = position / 9;
    return grid_coordinates;
}
void  get_cooridinates_test() {
    assert(get_coordinates(80)[0] == 8);
    assert(get_coordinates(80)[1] == 8);
    assert(get_coordinates(79)[0] == 7);
    assert(get_coordinates(79)[1] == 8);
}


/* Takes a list of allowed numbers and removes any new illegal numbers it finds
 * in the same row as <position>. Modifes list in-place
 */
void check_row(char allowed[], char sudoku[][9], char position) {
    char row = get_coordinates(position)[1];
    for (char i = 0; i < 9; i++)
    {
        if (sudoku[row][i])
        {
            allowed[sudoku[row][i]-1] = 0;
        }
    }
}
void check_row_test() {
    // Generate 1 row of sudoku
    char s[1][9];
    for (char i = 0; i < 9; i++)
    {
        s[0][i] = i+1;
    }
    // Set up allowed list
    char allowed[9] = {1,1,1,1,1,1,1,1,1};

    // Check if 1 is allowed
    s[0][0] = 0;
    char fasit1[9] = {1,0,0,0,0,0,0,0,0};
    check_row(allowed, s, 0);
    assert(compare_lists(allowed, fasit1, 9));

    // Check if none are allowed
    s[0][0] = 1;
    char fasit2[9] = {0,0,0,0,0,0,0,0,0};
    check_row(allowed, s, 0);
    assert(compare_lists(allowed, fasit2, 9));
}

/* Takes a list of allowed numbers and removes any new illegal numbers it finds
 * in the same column as <position>. Modifes list in-place
 */
void check_column(char allowed[], char sudoku[][9], char position) {
    char column = get_coordinates(position)[0];
    for (char i = 0; i < 9; i++)
    {
        if (sudoku[i][column])
        {
            allowed[sudoku[i][column]-1] = 0;
        }
    }
}
void check_column_test() {
    // Generate 1 row of sudoku
    char s[9][9];
    for (char i = 0; i < 9; i++)
    {
        s[i][0] = i+1;
    }
    // Set up allowed list
    char allowed[9] = {1,1,1,1,1,1,1,1,1};

    // Check if 1 is allowed
    s[0][0] = 0;
    char fasit1[9] = {1,0,0,0,0,0,0,0,0};
    check_column(allowed, s, 0);
    assert(compare_lists(allowed, fasit1, 9));

    // Check if none are allowed
    s[0][0] = 1;
    char fasit2[9] = {0,0,0,0,0,0,0,0,0};
    check_column(allowed, s, 0);
    assert(compare_lists(allowed, fasit2, 9));
}

/* Takes a list of allowed numbers and removes any new illegal numbers it finds
 * in the same square as <position>. Modifes list in-place
 */
void check_square(char allowed[], char sudoku[][9], char position) {
    char square_x = (get_coordinates(position)[0]/3)*3;
    char square_y = (get_coordinates(position)[1]/3)*3;

    for (char y_offset = 0; y_offset < 3; y_offset++)
    {
        for (char x_offset = 0; x_offset < 3; x_offset++)
        {
            if (sudoku[square_y + y_offset][square_x + x_offset])
            {
                allowed[sudoku[square_y + y_offset][square_x + x_offset]-1] = 0;
            }
        }
    }
}
void check_square_test() {
    char s[9][9] = {
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

    char t1[9] = {1,1,1,1,1,1,1,1,1};
    char s1[9] = {1,1,0,1,1,1,0,0,1};
    check_square(t1, s, 0);
    assert(compare_lists(t1, s1, 9));

    char t3[9] = {1,1,1,1,1,1,1,1,1};
    char s3[9] = {1,1,1,1,1,1,1,0,1};
    check_square(t3, s, 26);
    assert(compare_lists(t3, s3, 9));
}

/* Prints a standard 9x9 sudoku array
 * Purely for visualization
 */
void print_sudoku(char sudoku[][9]) {
    for (char y = 0; y < 9; y++)
    {
        for (char x = 0; x < 9; x++)
        {
            printf("%d ", sudoku[y][x]);
        }
        printf("\n");
    }
}


/* Recursively attempt to place a valid number in one
 * cell at a time, backtracking if we hit a dead end.
 * Solves the soduoku in-place
 */
char solve(char sudoku[][9], char position) {

    // If we hit position 81, then we managed to place
    // a number on every tile a.k.a. we completed it
    if (position == 81) {
        return 1;
    }

    // If not, then we have some work to do

    // Get current cartesian coordinates
    char x = get_coordinates(position)[0];
    char y = get_coordinates(position)[1];

    // If the current cell already has a value: skip
    if (sudoku[y][x]) {
        return solve(sudoku, position+1);
    }

    // Set up list to keep track of possible numbers
    char allowed[9] = {1,1,1,1,1,1,1,1,1};

    // Eliminate all dissalowed values
    check_row(allowed, sudoku, position);
    check_column(allowed, sudoku, position);
    check_square(allowed, sudoku, position);

    // Go through every number 1-9 and check if it was available
    for (char i = 0; i < 9; i++)
    {
        if (allowed[i]) {
            // If a number is available, we test it
            sudoku[y][x] = i+1;
            char result = solve(sudoku, position+1);
            // If we get back 1, then we know we completed it
            if (result) {
                return 1;
            }
        }
    }


    // If none of the available options worked,
    // then we reset this cell and go back
    sudoku[y][x] = 0;
    return 0;

}


int main(int argc, char const *argv[]) {

    // Pain and suffering

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

    // Double check that we solve it and it returns 1
    assert(solve(sudoku_base, 0));
    print_sudoku(sudoku_base);

    system("PAUSE");
}