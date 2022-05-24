/*
 * CSE 351 Lab 4 (Caches and Cache-Friendly Code)
 * Part 2 - Optimizing Matrix Transpose
 *
 * Name(s): Erik Nielsen 
 * NetID(s): erikn8
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 * and compute B = A^T.
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */

#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);


/*
 * transpose_submit - This is the transpose function that you will be graded
 *     on. Do not change the description string "Transpose submission", as the
 *     driver searches for that string to identify the transpose function to be
 *     graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {
    int rows, cols;
    int i , j;
    int temp = 0, diagonal  = 0;
    int s0, s1, s2, s3, s4;

    if(N == 32){

        for(cols = 0 ; cols < N ; cols += 8){
            for(rows = 0 ; rows < N ; rows += 8){
                for(i = rows ; i < rows + 8 ; i ++){
                    for(j = cols; j < cols + 8 ; j++){
                        if(i != j){
                            B[j][i] = A[i][j];

                        }else{
                            temp = A[i][j];
                            diagonal = i;
                        }
                    }
                    if (rows == cols)	
					{
						B[diagonal][diagonal] = temp;
					}

                }
            }
        }
    }

	if (N == 64)
	{	
		for(rows = 0; rows < N; rows += 4)
		{
			for(cols = 0; cols < M; cols += 4)
			{
				s0 = A[rows][cols];
				s1 = A[rows+1][cols];
				s2 = A[rows+2][cols];
			 s3 = A[rows+2][cols+1];
				s4 = A[rows+2][cols+2]; 
				B[cols+3][rows] = A[rows][cols+3];
				B[cols+3][rows+1] = A[rows+1][cols+3];
				B[cols+3][rows+2] = A[rows+2][cols+3];
				B[cols+2][rows] = A[rows][cols+2];
				B[cols+2][rows+1] = A[rows+1][cols+2];
				B[cols+2][rows+2] =  s4;
				s4 = A[rows+1][cols+1];
				B[cols+1][rows] = A[rows][cols+1];
				B[cols+1][rows+1] =  s4;
				B[cols+1][rows+2] = s3;
				B[cols][rows] = s0;
				B[cols][rows+1] = s1;
				B[cols][rows+2] = s2;
				B[cols][rows+3] = A[rows+3][cols];
				B[cols+1][rows+3] = A[rows+3][cols+1];
				B[cols+2][rows+3] = A[rows+3][cols+2];
				s0 = A[rows+3][cols+3];
				B[cols+3][rows+3] = s0;
			}
		}
	}
}



// You can define additional transpose functions below. We've defined a simple
// one below to help you get started.

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple rows-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}


/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}