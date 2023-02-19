#include <iostream>
#include <math.h>
#include <chrono>
#define PI 3.1415926535897932384
#define N_MAX 10000000
int main()
{
	double* arr = (double*)malloc(sizeof(double)*N_MAX);
	double sum = 0;
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
	
	std::cout<<sum<<std::endl;
	free(arr);
	return 0;
}
