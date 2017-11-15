#include <omp.h> 
#include <stdio.h> 
#include <locale.h>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Rus");

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
	
	// task 1 ////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 1 ==========================================================\n");
	double f1, f2;
	printf("Enter A:");
	scanf("%f", &f1);
	printf("Enter B:");
	scanf("%f", &f2);

#define NNN 100000000 // Число итераций - общее...
#define NT 2 // Чичло потоков
	
	start = omp_get_wtime();
#pragma omp parallel num_threads(NT) 
	{
#pragma omp for 
		for (int i = 0; i < (NNN / NT); i++)
			f1*f2;
	}
	end = omp_get_wtime();
	printf("Parallel task(%d): running time = %f\n", NT, end - start);

	double start2 = omp_get_wtime();
#pragma omp parallel num_threads(1) 
	{
#pragma omp for 
		for (int i = 0; i < (NNN/NT); i ++)
			f1*f2;
	}
	double end2 = omp_get_wtime();
	printf("Single task: running time = %f\n", end2 - start2);

	//////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 2 ==========================================================\n");
	printf("Empty parallel org region time = %f ms\n", (end - start)*NT * 1000 - (end2 - start2)*1000);

	//////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 4 ==========================================================\n");
	start = omp_get_wtime();
#pragma omp parallel num_threads(3) 
	{
		int ThreadId = omp_get_thread_num();
		printf("Начало... Thread(%d)\n", ThreadId);
#pragma omp master 
		{ 
			printf("Главный поток!... Thread(%d)\n", ThreadId);
		}
		printf("Середина... Thread(%d)\n", ThreadId);
#pragma omp master 
		{ 
		printf("Главный поток!... Thread(%d)\n", ThreadId);
		}
		printf("Конец... Thread(%d)\n", ThreadId);
	}
	end = omp_get_wtime();

	//////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 5 ==========================================================\n");
	int n = 10;
	printf("Последовательный регион. n=%d\n", n);
#pragma omp parallel num_threads(2) private(n) 
	{
		int ThreadId = omp_get_thread_num();
		n = ThreadId;		
		printf("  Параллельная область(%d). n=%d\n", ThreadId, n);
	}
	printf("Последовательный регион. n=%d\n", n);
	
	//////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 6 ==========================================================\n");
	int m[5] = {};
	printf("Массив m до обработки:\n", n);
	for (int i = 0; i < 5; i++)
		printf("%d ", m[i]);
	printf("\n", n);
#pragma omp parallel num_threads(2) shared(m) 
	{
		int ThreadId = omp_get_thread_num();
		for (int i = 0; i < 5; i++)
			if (i == ThreadId)
				m[i] = 1;
	}
	printf("Массив m после обработки:\n", n);
	for (int i = 0; i < 5; i++)
		printf("%d ", m[i]);
	printf("\n", n);

	//////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 7 ==========================================================\n");
	int tc = 0;
#pragma omp parallel reduction(+: tc) 
	{
		tc = 1;
	}
	printf("Количество потоков (счет при помощи редукции):%d\n", tc);

	//////////////////////////////////////////////////////////////////////////////
	printf("\n>>>Task 8 ==========================================================\n");
	tc = 0;
#pragma omp parallel num_threads(4) reduction(+: tc) 
	{
		int ThreadId = omp_get_thread_num();
		tc = ThreadId;
		printf("  Thread id %d\n", ThreadId);
	}
	printf("Сумма номеров потоков:%d\n", tc);
	
	//////////////////////////////////////////////////////////////////////////////
		printf("==========================================================\n");
	printf("Press Enter to exit...");
	getchar();
	getchar();
}