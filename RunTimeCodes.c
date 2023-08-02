#include <stdio.h> /* Standard input and output library, used only for printf. */


int main() /* Main function, runs the comparison functions. */
{
	table(4 , (double)0.33);
	table(5 , (double)0.20);
	table(6 , (double)0.20);
	table(7 , (double)0.33);
	table(7 , (double)0.01);
	table(8 , (double)0.50);
	table(8 , (double)0.01);
	table(9 , (double)0.01);
	table(10 , (double)0.001);
	table(11 , (double)0.0001);
}

/*--------------------------------------------------------------*/

void table (int n , double a) /* Receives a and n, and then starts the comparison. */
{
	int A[n];
	int B[n];
	int i;
	int factorial = 1;
	int x;
	
	for (i = 1 ; i <= n ; i++)
	{
		factorial = factorial * i;	
	}
	double size = a*3*factorial;
	x = (int)size;
	int C[x];
	bestAndWorst(n , a , factorial , A , B , C , x , 1); /* 1 for regular quick sort. */
	bestAndWorst(n , a , factorial , A , B , C , x , 2); /* 2 for best pivot quick sort. */		
}

/*--------------------------------------------------------------*/

void bestAndWorst (int n , double a , int factorial , int A[] , int B[] , int C[] , int size , int which) /* Calculates number of comparisons and averages. */
{
	int i;
	int average = 0;
	int averageBest = 0;
	int averageWorst = 0;
	int temp;
	double aa = a*factorial;
	int xx = aa;
	int count1 = 1;
	
	for (i = 0 ; i < n ; i++)
	{
		A[i] = i+1;
		B[i] = i+1;
	}
	if (size < factorial)
	{
		for (i = 0 ; i < size ; i++)
		{
			if (which == 1)
			{
				temp = quickSortCounter1(B , n);	
			} 
			else if (which == 2)
			{
				temp = quickSortCounter2(B , n);
			}
			C[i] = temp;
			average += temp;
			equalizeArrays(A , B , n);
			generateNextPermutation(A , n);
			generateNextPermutation(B , n);
		}
		SELECT(C , 0 , size-1 , xx);
		SELECT(C , 0 , size-1 , size-xx+1);
		i = xx;
		while (count1 <= factorial-size)
		{
			if (i == size-xx)
			{
				SELECT(C , 0 , size-1 , xx);
				SELECT(C , 0 , size-1 , size-xx+1);
				i = xx;	
			}
			if (which == 1)
			{
				temp = quickSortCounter1(B , n);	
			} 
			else if (which == 2)
			{
				temp = quickSortCounter2(B , n);
			}
			C[i] = temp;
			average += temp;
			equalizeArrays(A , B , n);
			generateNextPermutation(A , n);
			generateNextPermutation(B , n);
			i++;
			count1++;
		}
		SELECT(C , 0 , size-1 , xx);
		SELECT(C , 0 , size-1 , size-xx+1);
		for (i = 0 ; i < xx ; i++)
		{
			averageBest += C[i];
		}
		for (i = size-xx ; i < size ; i++)
		{
			averageWorst += C[i];
		}
		double x = (double)averageBest/xx;
		double y = (double)averageWorst/xx;
		if (which == 1)
		{
			printf("Average comparisons for %f best permutations (quick sort) is: %f\n" , a , x);
			printf("Average comparisons of all permutations (quick sort) is: %f\n" , (double)average/(double)factorial);	
			printf("Average comparisons for %f worst permutations (quick sort) is: %f\n" , a , y);	
		}
		else if (which == 2)
		{
			printf("Average comparisons for %f best permutations (best pivot quick sort) is: %f\n" , a , x);
			printf("Average comparisons of all permutations (best pivot quick sort) is: %f\n" , (double)average/(double)factorial);	
			printf("Average comparisons for %f worst permutations (best pivot quick sort) is: %f\n" , a , y);
		}	
				
	}
	else
	{
		for (i = 0 ; i < factorial ; i++)
		{ 
			if (which == 1)
			{
				temp = quickSortCounter1(B , n);	
			} 
			else if (which == 2)
			{
				temp = quickSortCounter2(B , n);
			}
			C[i] = temp;
			average += temp;
			equalizeArrays(A , B , n);
			generateNextPermutation(A , n);
			generateNextPermutation(B , n);
		}
		SELECT(C , 0 , factorial-1 , xx);
		for (i = 0 ; i < xx ; i++)
		{
			averageBest += C[i];
		}
		SELECT(C , 0 , factorial-1 , factorial-xx+1);
		for (i = factorial-xx ; i < factorial ; i++)
		{
			averageWorst += C[i];
		}
		double x = (double)averageBest/xx;
		double y = (double)averageWorst/xx;
		if (which == 1)
		{
			printf("Average comparisons for %f best permutations (quick sort) is: %f\n" , a , x);
			printf("Average comparisons of all permutations (quick sort) is: %f\n" , (double)average/(double)factorial);	
			printf("Average comparisons for %f worst permutations (quick sort) is: %f\n" , a , y);	
		}
		else if (which == 2)
		{
			printf("Average comparisons for %f best permutations (best pivot quick sort) is: %f\n" , a , x);
			printf("Average comparisons of all permutations (best pivot quick sort) is: %f\n" , (double)average/(double)factorial);	
			printf("Average comparisons for %f worst permutations (best pivot quick sort) is: %f\n" , a , y);
		}	
	}		
}

/*--------------------------------------------------------------*/

int quickSortCounter1 (int A[] , int n) /* Receives a permutation, sorts it using quick sort and returns number of comparisons. */
{
	int count = 0;
	int *cnt = &count;
	int a = (quickSort(A , 0 , n-1 , cnt));
	
	return a;
}

/*--------------------------------------------------------------*/

int quickSortCounter2 (int A[] , int n) /* Receives a permutation, sorts it using best pivot quick sort and returns number of comparisons. */
{
	int count = 0;
	int *cnt = &count;
	int a = (bestPivotQS(A , 0 , n-1 , cnt));

	return a;
}


/*--------------------------------------------------------------*/

/* This is the quick-select algorithm with its own partition that we use for finding best and worst permutations. */

int selectPartition(int arr[], int l, int r)
{
	int j;
	int x = arr[r]; 
	int i = l;
	
	for (j = l; j <= r - 1; j++) {
		if (arr[j] <= x) {
			exchange(arr,i, j);
			i++;
		}
	}
	exchange(arr,i,r);
	return i;
}


int SELECT(int arr[], int l, int r, int k)
{
	int index;
	
	if (k > 0 && k <= r - l + 1) {

		
		index = selectPartition(arr, l, r);

		
		if (index - l == k - 1)
			{return arr[index];
			}
		
		if (index - l > k - 1)
			{return SELECT(arr, l, index - 1, k);
			}
		
		return SELECT(arr, index + 1, r, k - index + l - 1);
	}

	
	return -1;
}

/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

int quickSort(int A[] , int p , int r , int *cnt) /* Regular quick sort algorithm. */
{
	int q;

	if (p < r)
	{
		q = partition(A , p , r , cnt);
		quickSort(A , p , q-1 , cnt);
		quickSort(A , q+1 , r , cnt);
	}
	else
	{
		return *cnt;	
	}	
}

/*--------------------------------------------------------------*/

int partition(int A[] , int p , int r , int *cnt) /* Partition for the quick sort algorithms. */
{
	int x = A[r];
	int i = p - 1;
	int j;
	
	for (j = p ; j <= r-1 ; j++)
	{
		(*cnt) += 1;
		if (A[j] <= x)
		{
			i = i + 1;
			exchange(A,i,j);
		}
	}
	exchange(A,i+1,r);
	return i+1;	
}

/*--------------------------------------------------------------*/

int bestPivotQS(int A[] , int p , int r , int *cnt) /* Best pivot quick sort algorithm. */
{
	int q;
	int x;
	
	if (p < r)
	{
		x = bestPivotIndex(A , p , r , cnt);
		exchange(A , x , r);
		q = partition(A , p , r , cnt);
		bestPivotQS(A , p , q-1 , cnt);
		bestPivotQS(A , q+1 , r , cnt);
	}
	else
	{
		return *cnt;	
	}		
}

/*--------------------------------------------------------------*/

int bestPivotIndex(int A[] , int p , int r , int *cnt)
/* Function that finds the best pivot for quick-sort. */
{
	int i;
	int s;
	int b;
	int j;

	for (i = p ; i <= r ; i++)
	{
		s = 0; 
		b = 0;
		for (j = p ; j <= r ; j++)
		{
			(*cnt)+=2;
			if (A[j] > A[i])
			{
				b = b + 1;
			}
			else if (A[j] < A[i])
			{
				s = s + 1;	
			}	
		}
		if (abs(b-s) <= 1)
		{
			return i;
		}	
	}
}

/*--------------------------------------------------------------*/

void exchange (int A[] , int x , int y) /* Receives two indexes within an array and swaps their values. */
{
	int temp = A[x];
	
	A[x] = A[y];
	A[y] = temp;
}

/*--------------------------------------------------------------*/

void generateNextPermutation (int A[] , int n) /* Receives a permutation and generates the next one. */
{
	int i = n - 2;
	int j;
	int c;

	while (i >= 0 && A[i] > A[i+1])
	{
		i--;
	}
	if (i == -1)
	{
		return;
	}
	c = i+1;
	for (j = i+2 ; j <= n-1 ; j++)
	{
		if (A[i] < A[j] && A[j] < A[c])
		{
			c = j;
		}
	}
	exchange(A , i , c);
	reverse(A, i+1 ,n-1);
}

/*--------------------------------------------------------------*/

void reverse (int A[] , int a , int b) /* Receives an array and two indexes and reverses the values between the indexes. */
{
	int size = b-a+1;
	int i;
	int B[b-a+1];

	for (i = 0 ; i < size ; i++)
	{
		B[i] = A[b];
		b--;
	}
	for (i = 0 ; i < size ; i++)
	{
		A[a] = B[i];
		a++;
	}
}

/*--------------------------------------------------------------*/

void equalizeArrays(int A[] , int B[] , int n) /* Receives two similar sized arrays, A and B, and makes B same as A. */
{
	int i;
	
	for (i = 0 ; i < n ; i++)
	{
		B[i] = A[i];
	}	
}

/*--------------------------------------------------------------*/
