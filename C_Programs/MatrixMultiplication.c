#include <stdio.h>
#include <pthread.h>

#define SIZE 3

int matA[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int matB[SIZE][SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int matC[SIZE][SIZE];

#define NUM_THREADS 4

void *multiply(void *arg) {
    int thread_id = *(int *)arg;
    int block_size = SIZE / NUM_THREADS;
    int start_row = thread_id * block_size;
    int end_row = start_row + block_size;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < SIZE; k++) {
                sum += matA[i][k] * matB[k][j];
            }
            matC[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix C:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", matC[i][j]);
        }
        printf("\n");
    }

    return 0;
}
