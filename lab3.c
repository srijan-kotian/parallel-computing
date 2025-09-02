// #include<stdio.h>
// #include<omp.h>

// int f(int n){
//     int i,j;
//     if(n<2){
//         return n;
//     }
    
//     else{
//         #pragma omp task shared(i) firstprivate(n)
//         i=f(n-1);
//         #pragma omp task shared(j) firstprivate(n)
//         j=f(n-2);
//          #pragma omp taskwait 

//         return i+j;
//     }
// }


// int main(){
//     int n;
//     printf("\n enter the number to calculate fibonacci=");
//     scanf("%d",&n);
//     omp_set_dynamic(0);
//     omp_set_num_threads(4);
//     double t0,t1;
//     #pragma omp parallel shared(n)
//     {
//         #pragma omp single
//          t0=omp_get_wtime();
//         int result=f(n);
//          t1=omp_get_wtime(); 

//         printf("fib(%d)=%d\n",n,f(n));
//         printf("time=%f sec \n",t1-t0);
//     }
//     return 0;
// }
#include <stdio.h>
#include <omp.h>

int f(int n) {
    int i, j;
    if (n < 2) {
        return n;
    } else {
        #pragma omp task shared(i)
        i = f(n - 1);

        #pragma omp task shared(j)
        j = f(n - 2);

        #pragma omp taskwait
        return i + j;
    }
}

int main() {
    int n;
    printf("Enter the number to calculate Fibonacci: ");
    scanf("%d", &n);

    omp_set_dynamic(0);
    omp_set_num_threads(4);

    int result;
    double t0, t1;

    #pragma omp parallel
    {
        #pragma omp single
        {
            t0 = omp_get_wtime();
            result = f(n);
            t1 = omp_get_wtime();
        }
    }

    printf("fib(%d) = %d\n", n, result);
    printf("Time = %f sec\n", t1 - t0);

    return 0;
}
