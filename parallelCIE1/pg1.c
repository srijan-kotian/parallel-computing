#include <stdio.h>
#include <omp.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n, i, serial_count = 0, parallel_count = 0;
    double start, end;

    printf("Enter n: ");
    scanf("%d", &n);

    start = omp_get_wtime();
    for (i = 1; i <= n; i++) {
        if (isPrime(i))
            serial_count++;
    }
    end = omp_get_wtime();
    double serial_time = end - start;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:parallel_count) schedule(dynamic)
    for (i = 1; i <= n; i++) {
        if (isPrime(i))
            parallel_count++;
    }

    end = omp_get_wtime();
    double parallel_time = end - start;

    printf("\nSerial Count of primes = %d", serial_count);
    printf("\nParallel Count of primes = %d", parallel_count);
    printf("\nExecution time (serial): %f seconds", serial_time);
    printf("\nExecution time (parallel): %f seconds\n", parallel_time);

    return 0;
}
