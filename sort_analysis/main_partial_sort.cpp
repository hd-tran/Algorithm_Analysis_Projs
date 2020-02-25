#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <utility>
#include <algorithm>

#include "sort_heads.h"
#include "bubble_sort.cpp"
#include "insertion_sort.cpp"
#include "spin_the_bottle_sort.cpp"
#include "shell_sort.cpp"
#include "annealing_sort.cpp"
#include "randomGen.cpp"

void printVector(std::vector<int> & v)
{
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << ",";
	}
	std::cout << "\n";
}

std::vector<int> genArray(int n)
{
        std::vector<int> result;

        for (int i = 0; i < n; i++)
        {
                result.push_back(i+1);
        }

        return result;
}

void partialSortShuffle(std::vector<int> & v)
{
        std::vector< std::pair<int,int> > repeats = {};
        double n = v.size();
        // independently choose 2*log(n) pairs of values to swap
        double pairs = 2 * log2(n);
        pairs = floor(pairs);
        int r = (int)pairs;

        std::mt19937 generator = getMTGenWithCurrentTimeSeed();
        std::uniform_int_distribution<int> distribution( 0, v.size()-1 );

        for (int x = 0; x < r; x++)
        {
                // randomly choose 2 values (i,j) to swap now
                int i = distribution( generator );
		//std::cout << "i to Swap: " << i << std::endl;

                int j = distribution( generator );
		//std::cout << "j to Swap: " << j << std::endl;

		std::pair<int,int> swapPair(i,j);

                std::vector< std::pair<int,int> >::iterator it = std::find(repeats.begin(), repeats.end(), swapPair);
		
                while ( j == i ||  it != repeats.end() )
                {
			//std::cout << "Old i to Swap: " << i << std::endl;
                        int j = distribution( generator );
			//std::cout << "New j to Swap: " << j << std::endl;
	  	        swapPair = std::pair<int,int>(i,j);
                        it = std::find(repeats.begin(),repeats.end(), swapPair);
			if (j != i && it == repeats.end())
			{
				break;
			}
		}

		repeats.push_back(swapPair);

                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
        }
	/*
	std::cout << "Swapped Pairs: ";
        for (int y = 0; y < repeats.size(); y++)
        {
                std::cout << "(" << repeats[y].first << "," <<repeats[y].second << ")" << " ; ";
        }
	std::cout << std::endl;
	*/
        return;
}

void randomShuffle(std::vector<int> & v)
{
        std::mt19937 generator = getMTGenWithCurrentTimeSeed();

        // Fisher Yates Shuffle
        for (int i = 0; i < v.size() - 2; i++)
        {
                std::uniform_int_distribution<int> distribution( i, v.size()-1 );
                int j = distribution( generator );
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
        }

        return;
}

int main()
{
	std::cout << "Basic Sort Testing\n";

        int smallSize     = 10;
        int mediumSize    = 100;
        int largeSize     = 1000;
        int veryLargeSize = 10000;

       	std::ofstream annealingTimings1;
        annealingTimings1.open("data/partialannealing1.csv");

        std::ofstream annealingTimings2;
        annealingTimings2.open("data/partialannealing2.csv");

        std::ofstream bubbleTimings;
        bubbleTimings.open("data/partialbubble.csv");

        std::ofstream insertionTimings;
        insertionTimings.open("data/partialinsertion.csv");

        std::ofstream shellTimings1;
        shellTimings1.open("data/partialshell1.csv");

        std::ofstream shellTimings2;
        shellTimings2.open("data/partialshell2.csv");

        std::ofstream spinTimings;
        spinTimings.open("data/partialspin.csv");

        std::vector<int> temps1({1000, 100, 10, 0});
        std::vector<int> temps2({0});
        std::vector<int> reps1({1000, 100, 10, 0});
        std::vector<int> reps2({0});
        //std::vector<int> gaps1({701, 301, 132, 57, 23, 10, 4, 1});
        std::vector<int> gaps1({});
        std::vector<int> gaps2({});


        std::cout << "======== Partially Sorted ========\n";
        std::cout << "==== Small Arrays ====\n";

        for (int i = 0; i < 5; i++)
        {
		temps1 = {};
		reps1 = {};

		temps2 = {};
		reps2 = {};

                gaps1 = {};
                gaps2 = {};

                std::vector<int> array1 = genArray(smallSize);
                partialSortShuffle(array1);
		
		std::cout << "Unsorted Vector: ";	
		printVector(array1);

                std::vector<int> array2 = array1;
                std::vector<int> array3 = array1;
                std::vector<int> array4 = array1;
                std::vector<int> array5 = array1;

                std::vector<int> array6 = array1;
                std::vector<int> array7 = array1;

		int tVal1 = 1;
                for (int k = 1; tVal1 < array1.size() * 3 / 4 ; k++)
                {
                        tVal1 =  pow(3, k) / 2;
                        temps1.push_back(tVal1);
                }
                std::reverse(temps1.begin(), temps1.end());

                int rVal1 = 1;
                for (int k = 0; k < temps1.size(); k++)
                {
                        rVal1 = log2(temps1[0]);
                        reps1.push_back(rVal1);
                }

                clock_t annealTime = clock();
                annealing_sort(array1, temps1, reps1);
                annealTime = clock() - annealTime;
                float annealTimeSec = ( (float)annealTime ) / CLOCKS_PER_SEC;

                int tVal2 = 1;
                for (int k = 0; tVal2 > 0; k++)
                {
                        tVal2 = array6.size() / pow(2,k);
                        temps2.push_back(tVal2);
                }
                int rVal2 = 1;
                for (int k = 0; k < temps2.size(); k++)
                {
                        rVal2 = temps2.size() / 2;
                        reps2.push_back(rVal2);
                }

                clock_t annealTime2 = clock();
                annealing_sort(array6, temps2, reps2);
                annealTime2 = clock() - annealTime2;
                float annealTimeSec2 = ( (float)annealTime2 ) / CLOCKS_PER_SEC;

                clock_t bubbleTime = clock();
                bubble_sort(array2);
                bubbleTime = clock() - bubbleTime;
                float bubbleTimeSec = ( (float)bubbleTime ) / CLOCKS_PER_SEC;

                clock_t insertionTime = clock();
                insertion_sort(array3);
                insertionTime = clock() - insertionTime;
                float insertionTimeSec = ( (float)insertionTime ) / CLOCKS_PER_SEC;

                int val1 = 1;
                for (int k = 1; val1 > 0 ; k++)
                {
                        val1 = pow(2,k) * array4.size() / pow(3,k);
                        gaps1.push_back(val1);
                }
                gaps1.erase(gaps1.end()-1);

                clock_t shellTime = clock();
                shell_sort(array4, gaps1);
                shellTime = clock() - shellTime;
                float shellTimeSec = ( (float)shellTime ) / CLOCKS_PER_SEC;

                int val2 = 1;
                for (int k = 1; val2 > 0; k++)
                {
                        //gaps2.push_back(val2);
                        val2 = k* array7.size() / pow(3,k);
                        gaps2.push_back(val2);
                }
                gaps2.erase(gaps2.end()-1);


                clock_t shellTime2 = clock();
                shell_sort(array7, gaps2);
                shellTime2 = clock() - shellTime2;
                float shellTimeSec2 = ( (float)shellTime2 ) / CLOCKS_PER_SEC;

                clock_t spinTime = clock();
                spin_the_bottle_sort(array5);
                spinTime = clock() - spinTime;
                float spinTimeSec = ( (float)spinTime ) / CLOCKS_PER_SEC;

                std::cout << "Sort Timings\n";
                std::cout << "Test Number: " << i+1 << std::endl;
                std::cout << "Annealing Sort: " << annealTimeSec << " seconds" << std::endl;
                std::cout << "Annealing Sort2: " << annealTimeSec2 << " seconds" << std::endl;
                std::cout << "Bubble Sort: " << bubbleTimeSec << " seconds" << std::endl;
                std::cout << "Insertion Sort: " << insertionTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort: " << shellTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort2: " << shellTimeSec2 << " seconds" << std::endl;
                std::cout << "Spin The Bottle Sort: " << spinTimeSec << " seconds" << std::endl;

		annealingTimings1 << smallSize << "," << annealTimeSec << "\n";
                annealingTimings2 << smallSize << "," << annealTimeSec2 << "\n";
                bubbleTimings << smallSize << "," << bubbleTimeSec << "\n";
                insertionTimings << smallSize << "," << insertionTimeSec << "\n";
                shellTimings1 << smallSize << "," << shellTimeSec << "\n";
                shellTimings2 << smallSize << "," << shellTimeSec2 << "\n";
                spinTimings << smallSize << "," << spinTimeSec << "\n";

		/*
                std::cout << "Partial,Small Arrays Done...\n";
		std::cout << "Post-Sort Arrays: " << std::endl;
		std::cout << "----Annealing Sort: ";
		printVector(array1);
		std::cout << "----Annealing Sort2: ";
		printVector(array6);
		std::cout << "----Bubble Sort: ";
		printVector(array2);
		std::cout << "----Insertion Sort: ";
		printVector(array3);
		std::cout << "----Shell Sort: ";
		printVector(array4);
		std::cout << "----Shell Sort2: ";
		printVector(array7);
		std::cout << "----Spin The Bottle Sort: ";
		printVector(array5);
*/
	}

        std::cout << "Starting Partial,Medium Arrays...\n";
        std::cout << "==== Medium Arrays ====\n";
        for (int i = 0; i < 5; i++)
        {
		temps1 = {};
		reps1 = {};

		temps2 = {};
		reps2 = {};

                gaps1 = {};
                gaps2 = {};

                std::vector<int> array1 = genArray(mediumSize);
                partialSortShuffle(array1);

                std::vector<int> array2 = array1;
                std::vector<int> array3 = array1;
                std::vector<int> array4 = array1;
                std::vector<int> array5 = array1;

                std::vector<int> array6 = array1;
                std::vector<int> array7 = array1;

		int tVal1 = 1;
                for (int k = 1; tVal1 < array1.size() * 3 / 4 ; k++)
                {
                        tVal1 =  pow(3, k) / 2;
                        temps1.push_back(tVal1);
                }
                std::reverse(temps1.begin(), temps1.end());

                int rVal1 = 1;
                for (int k = 0; k < temps1.size(); k++)
                {
                        rVal1 = log2(temps1[0]);
                        reps1.push_back(rVal1);
                }

                clock_t annealTime = clock();
                annealing_sort(array1, temps1, reps1);
                annealTime = clock() - annealTime;
                float annealTimeSec = ( (float)annealTime ) / CLOCKS_PER_SEC;

                int tVal2 = 1;
                for (int k = 0; tVal2 > 0; k++)
                {
                        tVal2 = array6.size() / pow(2,k);
                        temps2.push_back(tVal2);
                }
                int rVal2 = 1;
                for (int k = 0; k < temps2.size(); k++)
                {
                        rVal2 = temps2.size() / 2;
                        reps2.push_back(rVal2);
                }

                clock_t annealTime2 = clock();
                annealing_sort(array6, temps2, reps2);
                annealTime2 = clock() - annealTime2;
                float annealTimeSec2 = ( (float)annealTime2 ) / CLOCKS_PER_SEC;

                clock_t bubbleTime = clock();
                bubble_sort(array2);
                bubbleTime = clock() - bubbleTime;
                float bubbleTimeSec = ( (float)bubbleTime ) / CLOCKS_PER_SEC;

                clock_t insertionTime = clock();
                insertion_sort(array3);
                insertionTime = clock() - insertionTime;
                float insertionTimeSec = ( (float)insertionTime ) / CLOCKS_PER_SEC;

                int val1 = 1;
                for (int k = 1; val1 > 0 ; k++)
                {
                        val1 = pow(2,k) * array4.size() / pow(3,k);
                        gaps1.push_back(val1);
                }
                gaps1.erase(gaps1.end()-1);

                clock_t shellTime = clock();
                shell_sort(array4, gaps1);
                shellTime = clock() - shellTime;
                float shellTimeSec = ( (float)shellTime ) / CLOCKS_PER_SEC;

                int val2 = 1;
                for (int k = 1; val2 > 0; k++)
                {
                        //gaps2.push_back(val2);
                        val2 = k* array7.size() / pow(3,k);
                        gaps2.push_back(val2);
                }
                gaps2.erase(gaps2.end()-1);


                clock_t shellTime2 = clock();
                shell_sort(array7, gaps2);
                shellTime2 = clock() - shellTime;
                float shellTimeSec2 = ( (float)shellTime2 ) / CLOCKS_PER_SEC;

                clock_t spinTime = clock();
                spin_the_bottle_sort(array5);
                spinTime = clock() - spinTime;
                float spinTimeSec = ( (float)spinTime ) / CLOCKS_PER_SEC;

                std::cout << "Sort Timings\n";
                std::cout << "Test Number: " << i+1 << std::endl;
                std::cout << "Annealing Sort: " << annealTimeSec << " seconds" << std::endl;
                std::cout << "Annealing Sort2: " << annealTimeSec2 << " seconds" << std::endl;

                std::cout << "Bubble Sort: " << bubbleTimeSec << " seconds" << std::endl;
                std::cout << "Insertion Sort: " << insertionTimeSec << " seconds" << std::endl;

                std::cout << "Shell Sort: " << shellTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort2: " << shellTimeSec2 << " seconds" << std::endl;

                std::cout << "Spin The Bottle Sort: " << spinTimeSec << " seconds" << std::endl;

		annealingTimings1 << mediumSize << "," << annealTimeSec << "\n";
                annealingTimings2 << mediumSize << "," << annealTimeSec2 << "\n";
                bubbleTimings << mediumSize << "," << bubbleTimeSec << "\n";
                insertionTimings << mediumSize << "," << insertionTimeSec << "\n";
                shellTimings1 << mediumSize << "," << shellTimeSec << "\n";
                shellTimings2 << mediumSize << "," << shellTimeSec2 << "\n";
                spinTimings << mediumSize << "," << spinTimeSec << "\n";

	}

        std::cout << "==== Large Arrays ====\n";
        for (int i = 0; i < 5; i++)
        {
		temps1 = {};
		reps1 = {};

		temps2 = {};
		reps2 = {};

                gaps1 = {};
                gaps2 = {};

                std::vector<int> array1 = genArray(largeSize);
                partialSortShuffle(array1);

                std::vector<int> array2 = array1;
                std::vector<int> array3 = array1;
                std::vector<int> array4 = array1;
                std::vector<int> array5 = array1;

                std::vector<int> array6 = array1;
                std::vector<int> array7 = array1;

		int tVal1 = 1;
                for (int k = 1; tVal1 < array1.size() * 3 / 4 ; k++)
                {
                        tVal1 =  pow(3, k) / 2;
                        temps1.push_back(tVal1);
                }
                std::reverse(temps1.begin(), temps1.end());

                int rVal1 = 1;
                for (int k = 0; k < temps1.size(); k++)
                {
                        rVal1 = log2(temps1[0]);
                        reps1.push_back(rVal1);
                }

                clock_t annealTime = clock();
                annealing_sort(array1, temps1, reps1);
                annealTime = clock() - annealTime;
                float annealTimeSec = ( (float)annealTime ) / CLOCKS_PER_SEC;

                int tVal2 = 1;
                for (int k = 0; tVal2 > 0; k++)
                {
                        tVal2 = array6.size() / pow(2,k);
                        temps2.push_back(tVal2);
                }
                int rVal2 = 1;
                for (int k = 0; k < temps2.size(); k++)
                {
                        rVal2 = temps2.size() / 2;
                        reps2.push_back(rVal2);
                }

                clock_t annealTime2 = clock();
                annealing_sort(array6, temps2, reps2);
                annealTime2 = clock() - annealTime2;
                float annealTimeSec2 = ( (float)annealTime2 ) / CLOCKS_PER_SEC;

                clock_t bubbleTime = clock();
                bubble_sort(array2);
                bubbleTime = clock() - bubbleTime;
                float bubbleTimeSec = ( (float)bubbleTime ) / CLOCKS_PER_SEC;

                clock_t insertionTime = clock();
                insertion_sort(array3);
                insertionTime = clock() - insertionTime;
                float insertionTimeSec = ( (float)insertionTime ) / CLOCKS_PER_SEC;

                int val1 = 1;
                for (int k = 1; val1 > 0 ; k++)
                {
                        val1 = pow(2,k) * array4.size() / pow(3,k);
                        gaps1.push_back(val1);
                }
                gaps1.erase(gaps1.end()-1);

                clock_t shellTime = clock();
                shell_sort(array4, gaps1);
                shellTime = clock() - shellTime;
                float shellTimeSec = ( (float)shellTime ) / CLOCKS_PER_SEC;

                int val2 = 1;
                for (int k = 1; val2 > 0; k++)
                {
                        //gaps2.push_back(val2);
                        val2 = k* array7.size() / pow(3,k);
                        gaps2.push_back(val2);
                }
                gaps2.erase(gaps2.end()-1);


                clock_t shellTime2 = clock();
                shell_sort(array7, gaps2);
                shellTime2 = clock() - shellTime2;
                float shellTimeSec2 = ( (float)shellTime2 ) / CLOCKS_PER_SEC;

                clock_t spinTime = clock();
                spin_the_bottle_sort(array5);
                spinTime = clock() - spinTime;
                float spinTimeSec = ( (float)spinTime ) / CLOCKS_PER_SEC;

                std::cout << "Sort Timings\n";
                std::cout << "Test Number: " << i+1 << std::endl;
                std::cout << "Annealing Sort: " << annealTimeSec << " seconds" << std::endl;
                std::cout << "Annealing Sort2: " << annealTimeSec2 << " seconds" << std::endl;

                std::cout << "Bubble Sort: " << bubbleTimeSec << " seconds" << std::endl;
                std::cout << "Insertion Sort: " << insertionTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort: " << shellTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort2: " << shellTimeSec2 << " seconds" << std::endl;

                std::cout << "Spin The Bottle Sort: " << spinTimeSec << " seconds" << std::endl;
        
		annealingTimings1 << largeSize << "," << annealTimeSec << "\n";
                annealingTimings2 << largeSize << "," << annealTimeSec2 << "\n";
                bubbleTimings << largeSize << "," << bubbleTimeSec << "\n";
                insertionTimings << largeSize << "," << insertionTimeSec << "\n";
                shellTimings1 << largeSize << "," << shellTimeSec << "\n";
                shellTimings2 << largeSize << "," << shellTimeSec2 << "\n";
                spinTimings << largeSize << "," << spinTimeSec << "\n";

	}

        std::cout << "==== Very Large Arrays ====\n";
        for (int i = 0; i < 5; i++)
        {
		temps1 = {};
		reps1 = {};

		temps2 = {};
		reps2 = {};

                gaps1 = {};
                gaps2 = {};
                
		std::vector<int> array1 = genArray(veryLargeSize);
                partialSortShuffle(array1);

                std::vector<int> array2 = array1;
                std::vector<int> array3 = array1;
                std::vector<int> array4 = array1;
                std::vector<int> array5 = array1;

                std::vector<int> array6 = array1;
                std::vector<int> array7 = array1;

		int tVal1 = 1;
                for (int k = 1; tVal1 < array1.size() * 3 / 4 ; k++)
                {
                        tVal1 =  pow(3, k) / 2;
                        temps1.push_back(tVal1);
                }
                std::reverse(temps1.begin(), temps1.end());

                int rVal1 = 1;
                for (int k = 0; k < temps1.size(); k++)
                {
                        rVal1 = log2(temps1[0]);
                        reps1.push_back(rVal1);
                }

                clock_t annealTime = clock();
                annealing_sort(array1, temps1, reps1);
                annealTime = clock() - annealTime;
                float annealTimeSec = ( (float)annealTime ) / CLOCKS_PER_SEC;

                int tVal2 = 1;
                for (int k = 0; tVal2 > 0; k++)
                {
                        tVal2 = array6.size() / pow(2,k);
                        temps2.push_back(tVal2);
                }
                int rVal2 = 1;
                for (int k = 0; k < temps2.size(); k++)
                {
                        rVal2 = temps2.size() / 2;
                        reps2.push_back(rVal2);
                }

                clock_t annealTime2 = clock();
                annealing_sort(array6, temps2, reps2);
                annealTime2 = clock() - annealTime2;
                float annealTimeSec2 = ( (float)annealTime2 ) / CLOCKS_PER_SEC;

                clock_t bubbleTime = clock();
                bubble_sort(array2);
                bubbleTime = clock() - bubbleTime;
                float bubbleTimeSec = ( (float)bubbleTime ) / CLOCKS_PER_SEC;

                clock_t insertionTime = clock();
                insertion_sort(array3);
                insertionTime = clock() - insertionTime;
                float insertionTimeSec = ( (float)insertionTime ) / CLOCKS_PER_SEC;

                int val1 = 1;
                for (int k = 1; val1 > 0 ; k++)
                {
                        val1 = pow(2,k) * array4.size() / pow(3,k);
                        gaps1.push_back(val1);
                }
                gaps1.erase(gaps1.end()-1);

                clock_t shellTime = clock();
                shell_sort(array4, gaps1);
                shellTime = clock() - shellTime;
                float shellTimeSec = ( (float)shellTime ) / CLOCKS_PER_SEC;

                int val2 = 1;
                for (int k = 1; val2 > 0; k++)
                {
                        //gaps2.push_back(val2);
                        val2 = k* array7.size() / pow(3,k);
                        gaps2.push_back(val2);
                }
                gaps2.erase(gaps2.end()-1);

                clock_t shellTime2 = clock();
                shell_sort(array7, gaps2);
                shellTime2 = clock() - shellTime2;
                float shellTimeSec2 = ( (float)shellTime2 ) / CLOCKS_PER_SEC;

                clock_t spinTime = clock();
                spin_the_bottle_sort(array5);
                spinTime = clock() - spinTime;
                float spinTimeSec = ( (float)spinTime ) / CLOCKS_PER_SEC;

                std::cout << "Sort Timings\n";
                std::cout << "Test Number: " << i+1 << std::endl;
                std::cout << "Annealing Sort: " << annealTimeSec << " seconds" << std::endl;
                std::cout << "Annealing Sort2: " << annealTimeSec2 << " seconds" << std::endl;

                std::cout << "Bubble Sort: " << bubbleTimeSec << " seconds" << std::endl;
                std::cout << "Insertion Sort: " << insertionTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort: " << shellTimeSec << " seconds" << std::endl;
                std::cout << "Shell Sort2: " << shellTimeSec2 << " seconds" << std::endl;

                std::cout << "Spin The Bottle Sort: " << spinTimeSec << " seconds" << std::endl;

		annealingTimings1 << veryLargeSize << "," << annealTimeSec << "\n";
                annealingTimings2 << veryLargeSize << "," << annealTimeSec2 << "\n";
                bubbleTimings << veryLargeSize << "," << bubbleTimeSec << "\n";
                insertionTimings << veryLargeSize << "," << insertionTimeSec << "\n";
                shellTimings1 << veryLargeSize << "," << shellTimeSec << "\n";
                shellTimings2 <<veryLargeSize << "," << shellTimeSec2 << "\n";
                spinTimings << veryLargeSize << "," << spinTimeSec << "\n";

	}

	annealingTimings1.close();
        annealingTimings2.close();
        bubbleTimings.close();
        insertionTimings.close();
        shellTimings1.close();
        shellTimings2.close();
        spinTimings.close();

        return 0;

}
