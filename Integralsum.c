#include<omp.h>
#include<stdio.h>
#define NUM_THREADS 8

static long num_steps=100000;
double step;

int main()
{
    int i,num_threads;
    double x,pi=0;
    double sum[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);
    
    step=1/(double)num_steps;

    double t1=omp_get_wtime(),t2;

    #pragma omp parallel
    {
        int id=omp_get_thread_num(),nthreads=omp_get_num_threads();
        if(id==0)
        {
            num_threads=nthreads;
        }
        for(i=id;i<num_steps;i+=nthreads)
        {
            x=(i+0.5)*step;
            sum[id]+=4/(1+x*x);
        }
    }
    for(i=0;i<num_threads;i++)
    {
        pi+=sum[i]*step;
    }
    t2=omp_get_wtime();
    printf("pi = %f, time = %f",pi,t2-t1);
}