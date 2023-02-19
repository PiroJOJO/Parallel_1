#include <iostream>
#include <math.h>
#include <chrono>
#define PI 3.1415926535897932384
#define N_MAX 10000000
int main()
{
	auto begin = std::chrono::steady_clock::now();
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
	
	std::cout<<sum<<std::endl;
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
	std::cout<<"time: "<<elapsed_ms.count()<<"ms\n";
	free(arr);
	return 0;
}
