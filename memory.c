// IT18033960
// E.K.J Premathilaka
// Weekend

#include <stdio.h>
#include <stdbool.h>

#define M 11
#define N 51
#define K 11

int m, n, turnAroundTime;
int minTval[K][K] , partitionSizes[M];
int startTime[M], endTime[M], Ptime[N]; //to store the start times and end times of regions and 'Ptime' to calculate turnaround time of each program
int partNo[M], programNo[N]; // partition number and program number
int tradeoffSize[N], tradeoffTime[N]; // temporary arrays to sort time values and sizes of each program
bool progState[N];

void userInputs()
{
	for (int i = 1; i <= m; i++) //storing the sizes of the regions
		scanf("%d", &partitionSizes[i]);

	int s, t, k;
	for (int i = 1; i <= n; i++) //per program
	{
		int minTval = 1000;
		int sizeS;

		scanf("%d", &k);
		for (int i = 1; i <= k; i++)
		{
			int count = 0;
			scanf("%d %d", &s, &t);
			for (int j = 1; j <= m; j++) //checking all the 's' values to get the minimun 't' values of the program
			{
				if (s <= partitionSizes[j] && count == 0) //checking the required size
				{
					if (t < minTval)
					{
						//getting the set with the minimum 't' value
						minTval = t;
						sizeS = s;
						count++;
					}
				}
			}
		}

		// assigning the minimum values to an array
		tradeoffSize[i] = sizeS;
		tradeoffTime[i] = minTval;
	}
}


//swapping function
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// this function is called in the main to sort 's' , 't' and program number arrays
void sort()
{
	int smallest;

	//selection sort algo to sort 't' values in ascending order
	for (int i = 1; i <= n - 1; i++)
	{
		smallest = i;
		for (int j = i + 1; j <= n; j++)
		{
			if (tradeoffTime[j] < tradeoffTime[smallest])
				smallest = j;
		}
		swap(&tradeoffTime[i], &tradeoffTime[smallest]);
		swap(&tradeoffSize[i], &tradeoffSize[smallest]); // according to the time values, sizes should be sorted
		swap(&programNo[i], &programNo[smallest]); // keeps the program number array updated
	}
}


void calculation()
{
	// selection sort algo to sort executed time(startTime) of partitions in ascending order
	for (int i = 1; i <= n; i++) // n = number of programs
	{
		int min;
		for (int i = 1; i <= m - 1; i++)
		{
			min = i;
			for (int j = i + 1; j <= m; j++)
			{
				if (startTime[j] < startTime[min])
					min = j;
			}
			swap(&startTime[i], &startTime[min]);
			swap(&partNo[i], &partNo[min]);
			swap(&partitionSizes[i], &partitionSizes[min]);
		}

		for (int j = 1; j <= m; j++) // m = number of partitions
		{
			if (progState[i] == false && tradeoffSize[i] <= partitionSizes[j]) //checks if the programs fits in the partition
			{
				progState[i] = true; //program 'i' is running
				int start = startTime[j];
				startTime[j] = endTime[j] = tradeoffTime[i] + startTime[j]; // endTime of the current program is gonna be the starttime of the next program
				Ptime[i] = endTime[j]; //gets the time it took for a program to complete

				printf("Program %d runs in region %d from %d to %d\n", programNo[i], partNo[j], start, endTime[j]);
			}
		}
		turnAroundTime += Ptime[i]; // calculating TT
	}
}


int main()
{
	int caseNo = 1;

	printf("\nInputs\n");
	while(scanf("%d %d", &m, &n) == 2 && m > 0 && n > 0) //Partitions and Programs
	{
		turnAroundTime = 0;

		//initializing program number
		for (int i = 1; i <= n; i++)
			programNo[i] = i;

		// setting startTimes to 0
		for (int i = 1; i <= m; i++)
		{
			startTime[i] = 0;
			partNo[i] = i;
		}

		// initializing program states which means no program is completed yet
		for (int i = 1; i <= n; ++i)
			progState[i] = false;
		
		userInputs();
		sort();

		printf("\nCase %d\n\n", caseNo);
		calculation();

		printf("\nAverage turnaround time = %.2f\n", (float)turnAroundTime / n);
		printf("\nInputs\n");
		caseNo++;
	}
	return 0;
}

/*
TEST CASES
2 4
40 60
1 35 4
1 20 3
1 40 10
1 60 7

3 5
10 20 30
2 10 50 12 30
2 10 100 20 25
1 25 19
1 19 41
2 10 18 30 42

4 7
20 30 40 50
1 10 5
3 50 10 25 15 35 20
2 10 50 12 30
2 10 100 20 25
1 25 19
1 19 41
2 10 18 30 42
*/
