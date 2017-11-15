#include <omp.h> 
#include <stdio.h> 

int main(int argc, char *argv[])
{
	int NumOfThreads;
	double start = omp_get_wtime();
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Hello, I am thread number %d from %d\n", ThreadId, NumOfThreads);
#pragma omp master
		{
			printf("I am master thread, number %d\n", ThreadId);
		}
	}
	double end = omp_get_wtime();
	printf("Running time = %f\n", end - start);
	
	//////////////////////////////////////////////////////////////////////////////

	double f1, f2;
	printf("Enter A:");
	scanf("%f", &f1);
	printf("Enter B:");
	scanf("%f", &f2);

	start = omp_get_wtime();
#pragma omp parallel omp_num_task(2)
	{
	}
	end = omp_get_wtime();


	//////////////////////////////////////////////////////////////////////////////

	printf("Press Enter to exit...");
	getchar();
}