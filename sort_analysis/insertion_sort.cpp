#ifndef INSERTION_SORT_CPP
#define INSERTION_SORT_CPP

#include "sort_heads.h"

void insertion_sort(std::vector<int> & nums)
{
	for (int i = 1; i < nums.size(); i++)
	{
		int temp = nums[i];
		int n = i;
		while (n > 0 && nums[n-1] > temp)
		{
			nums[n] = nums[n-1];
			n--;
		}
		nums[n] = temp;
	}
	return;
}

#endif
