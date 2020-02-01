#ifndef SHELL_SORT_CPP
#define SHELL_SORT_CPP

#include "project1.h"

void shell_sort(std::vector<int> & nums, const std::vector<int> & gaps)
{
	for (int g = 0; g < gaps.size(); g++)
	{
		for (int i = g; i < nums.size(); i++)
		{
			int temp = nums[i];
			int n = i;
			while (n >= g && temp < nums[n-g])
			{
				nums[n] = nums[n-g];
				n -= g;
			}
			nums[n] = temp;
		}
	}
	return;
}

#endif
