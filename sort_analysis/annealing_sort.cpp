#ifndef ANNEALING_SORT_CPP
#define ANNEALING_SORT_CPP

#include "sort_heads.h"
#include "randomGen.cpp"

int findMin(int first, int second)
{
	if (first <= second)
	{
		return first;
	}
	else
	{
		return second;
	}
}

int findMax(int first, int second)
{
	if (first >= second)
	{
		return first;
	}
	else
	{
		return second;
	}
}

void annealing_sort(std::vector<int> & nums, const std::vector<int> & temps, const std::vector<int> & reps)
{
	std::mt19937 generator = getMTGenWithCurrentTimeSeed();
	for (int j = 0; j < temps.size(); j++)
	{
		if (temps[j] == 0)
		{
			break;
		}
		for (int i = 0; i < nums.size()-1; i++)
		{
			std::uniform_int_distribution<int> distribution( i+1, findMin(nums.size()-1, i+temps[j]) );
			for (int k = 0; k <= reps[j]; k++)
			{
				int s = distribution(generator);
				if (nums[i] > nums[s])
				{
					int temp = nums[i];
					nums[i] = nums[s];
					nums[s] = temp;
				}
			}
		}
		for (int i = nums.size()-1; i >= 1; i--)
		{
			std::uniform_int_distribution<int> distribution( findMax(0,i-temps[j]), i-1);
			for (int k = 0; k <= reps[j]; k++)
			{
				int s = distribution(generator);
				if (nums[s] > nums[i])
				{
					int temp = nums[s];
					nums[s] = nums[i];
					nums[i] = temp;
				}
			}
		}
	}
	return;
}
#endif
