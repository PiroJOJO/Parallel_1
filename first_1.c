#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.1415926535897932384
#define N_MAX 10000000
int main()
{
	clock_t begin = clock();
	float* arr = (float*)malloc(sizeof(float)*N_MAX);
	float sum = 0;
#pragma acc data create (arr[0:N_MAX])
	{
#pragma acc kernels
		for(size_t i = 0; i < N_MAX; i++)
		{
			arr[i] = sin (2 * M_PI/ N_MAX * i);
		}
#pragma acc data copy (sum)
		{
#pragma acc kernels
			for ( size_t i = 0; i < N_MAX; i++)
			{
				sum += arr[i];
			}
		}
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;
	printf("%0.17f\n",sum);
	printf("%f\n",time_spent);
	free(arr);
	return 0;
}
