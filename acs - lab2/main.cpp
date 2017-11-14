#include <omp.h> 
#include <stdio.h> 

int main(int argc, char *argv[])
{
	int NumOfThreads;
#pragma omp parallel 
	{
		int ThreadId;
		ThreadId = omp_get_thread_num();
		NumOfThreads = omp_get_num_threads();
		printf("Hello, I am thread number %d from %d\n",
			ThreadId, NumOfThreads);
	}
	return 0;
}