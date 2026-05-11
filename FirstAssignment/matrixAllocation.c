#include <stdio.h>
#include <stdlib.h>

//declaration of special_sum function
int special_sum(int *mat, int rows, int cols);

int main() {
    // size of matrix
    int N;
    // The pointer that holds the matrix
    int *mat;

    // Asking the user to enter the size of matrix
    printf("Please enter the size of the matrix: ");
    scanf("%d", &N);

    // allocation of memory by using malloc
    mat = (int *)malloc(N*N*sizeof(int));

    //checking if memory allocation has failed
    if(mat == NULL) {
        printf("Memory allocation has failed");
        return 1;
    }   

    //loop to read elements from the user input
    printf("enter matrix elements: ");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            //here we calculate the exact place inside the matrix and scan there
            scanf("%d", mat + i*N + j);
        }
        
    }

    //calling the function
    int sum = special_sum(mat, N, N);

    //printing the sum
    printf("Sum: %d \n", sum);

    //freeing the memory
    free(mat);

    return 0;
}

// definiton of special_sum
int special_sum(int *mat, int rows, int cols) {
    int sum = 0;

    //creating the loop with given rows and cols variables
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //checking if we are on the main diagonal e: (1,1)
            if(i == j) {
                //we get the value of the specific matrix element we are currently at and add it to the sum
                sum += *(mat + i *cols + j);
            }
            // checking if we are on the secondary diagonal e: (0,2)
            else if(i + j == cols - 1) {
                //we get the value of the specific matrix element we are currently at and add it to the sum
                sum += *(mat+i*cols+j);
            }
        }
        
    }

    return sum;
}