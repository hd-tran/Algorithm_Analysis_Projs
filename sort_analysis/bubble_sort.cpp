#ifndef BUBBLE_SORT_CPP
#define BUBBLE_SORT_CPP

#include "project1.h"

void bubble_sort(std::vector<int> & nums)
{
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = 1; j < nums.size(); j++)
		{
			int temp;
			if (nums[j-1] > nums[j])
			{
				temp = nums[j-1];
				nums[j-1] = nums[j];
				nums[j] = temp;
			}
		}
	}
	return;
}

#endif
