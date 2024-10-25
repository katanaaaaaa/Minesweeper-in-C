#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // Required for bool, true, false
#include <time.h>

/*
(i-1, j-1)   (i-1, j)   (i-1, j+1)
(i,   j-1)   (i,   j)   (i,   j+1)
(i+1, j-1)   (i+1, j)   (i+1, j+1)
*/

int count_adjacent_bombs(int **matrix, int i, int j, int rows, int cols) {
    int bomb_count = 0, x, y;
    for (x = i - 1; x <= i + 1; x++) {
        for (y = j - 1; y <= j + 1; y++) {
            if (x >= 0 && x < rows && y >= 0 && y < cols && (x != i || y != j)) {
                if (matrix[x][y] == 0) {  
                    bomb_count++;
                }
            }
        }
    }
    return bomb_count;
}

int main() {
    int i, j, **matrix,  row, col, bomb, b;
    char **display;
    bool game_over = false;
    int check_row , check_col;

    printf("Enter the number of lines and rows: ");
    scanf("%d%d", &i, &j);
    printf("Enter the number of bombs: ");
    scanf("%d", &bomb);

    // Allocate memory for the rows (array of pointers to rows)
    matrix = (int**)malloc(i * sizeof(int*)); 

    // Allocate memory for each row (for the columns of each row)
    for (row = 0; row < i; row++) {
        matrix[row] = (int*)malloc(j * sizeof(int)); 
    }

    // Wherever there is no bomb, put 2
    for (row = 0; row < i; row++) {
        for (col = 0; col < j; col++) {
            matrix[row][col] = 2;
        }
    }

    // Locate bombs in a random way
    srand(time(0));
    for (b = 0; b < bomb; b++) {
        row = rand() % i;
        col = rand() % j;
        if (matrix[row][col] != 0) {
            matrix[row][col] = 0;
            printf("Bomb placed at: (%d, %d)\n", row, col); 
        } else {
            b--;  // Retry if a bomb is already there
        }
    }

    // Example - Display the matrix values
    printf("\nMatrix values:\n");
    for (row = 0; row < i; row++) {
        for (col = 0; col < j; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
    
    // Allocate memory for display dynamically
        printf("\nDiplay values:\n");
        display = (char**)malloc(i * sizeof(char*));
        for (row = 0; row < i; row++) {
            display[row] = (char*)malloc(j * sizeof(char));
            for (col = 0; col < j; col++) {
                display[row][col] = '-';  // Initialize to '-'
                printf("%c ", display[row][col]);

           }  
	       printf("\n");
     
        }

    // The user interaction
    while (!game_over) {
        printf("\nEnter the cordinates(row,column): ");
        scanf("%d%d", &row, &col);

        // Check if the coordinates are valid before accessing the matrix
        if (row >= 0 && row < i && col >= 0 && col < j) {
            // Print the current value at the selected coordinates for debugging
            printf("Current value at matrix[%d][%d]: %d\n", row, col, matrix[row][col]);

            // Check if the user hit a bomb
            if (matrix[row][col] == 0) {
                printf("The game is OVER! You have stepped on a BOMB!\n");
                display[row][col]='B';
                printf("\nDiplay values:\n");
                for (row = 0; row < i; row++) {
                    for (col = 0; col < j; col++){
                        printf("%c ", display[row][col]);
                        }  
	                printf("\n");
	            }
                break;
            }
            // Check if the box is visited for the first time
            else if (matrix[row][col] == 2) {
                matrix[row][col] = 3;
                display[row][col] = 'A';
                printf("This box is now visited for the first time.\n");
                int bombs_nearby = count_adjacent_bombs(matrix, row, col, i, j);
                display[row][col] = '0' + bombs_nearby;  // Convert count to char for display
                printf("Safe! %d bombs nearby.\n", bombs_nearby);
            }
            // Check if the box is already visited
            else if (matrix[row][col] == 3) {
                printf("\nThis box is already visited.\n");
            }

            // Check if the game should be over (all non-bomb boxes visited)
            game_over = true;  // Assume the game is over
            for (check_row = 0; check_row < i; check_row++) {
                for (check_col = 0; check_col < j; check_col++) {
                    if (matrix[check_row][check_col] == 2) {
                        game_over = false;  // Found a non-visited box
                    }
                }
            }
                /*printf("\nMatrix values:\n");
                for (row = 0; row < i; row++) {
                    for (col = 0; col < j; col++) {
                        printf("%d ", matrix[row][col]);
                   }
                   printf("\n");
                }
                */
                printf("\nDiplay values:\n");
                for (row = 0; row < i; row++) {
                    for (col = 0; col < j; col++){
                        printf("%c ", display[row][col]);
                        }  
	                printf("\n");
	            }
     
        } else {
            printf("Invalid coordinates. Please try again.\n");
        }
        
    }
       
    if(game_over){
        printf("You are the WINNER!!!!!");
    }

    // Free the memory for each row
    for (row = 0; row < i; row++) {
        free(matrix[row]);
        free(display[row]);

    }
    // Free the memory for the array of pointers (the rows)
    free(matrix);
    free(display);
    return 0;
}

