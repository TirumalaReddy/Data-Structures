/**
 * AGGRCOW - Aggressive cows
 
* Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The stalls are located along a straight line at positions x1,...,xN (0 <= xi <= 1,000,000,000).

* His C (2 <= C <= N) cows don't like this barn layout and become aggressive towards each other once put into a stall. To prevent the cows from hurting each other, FJ want to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?

* Assume stalls are inputted in sorted order. Else write sort logic.
 */
#include <stdio.h>
#include<stdlib.h>
int binary_search(int low, int high, int cows, int diff[], int N) {
	while (low < high) {
		int i,count = 1, mid, temp_diff = 0, pre_diff =0, result =diff[N-1];
		mid = low + (high - low)/2;
		for (i=1;i<N;i++) {
			temp_diff = diff[i] - pre_diff;
			if (temp_diff >= mid) {
				count ++;
				pre_diff = diff[i];
				if (temp_diff < result) {
					result = temp_diff;
				}
			}
		}
		if (count == cows) {
			return result;
		}
		if (count > cows) {
			low = mid + 1;
		} else {
			high = mid -1;
		}
	}
	return -1;
}

int main(void) {
	int i,N, *Stalls, result, cows, *diff;
	scanf("%d %d", &N, &cows);
	Stalls = malloc(N*sizeof(int));
	diff = malloc(N*sizeof(int));
	diff[0]=0;
	for (i=0; i<N; i++) {
		scanf("%d", &Stalls[i]);
		if (i!=0) {
			diff[i]=diff[i-1]+Stalls[i]-Stalls[i-1];
		}
	}
	result = binary_search(1, diff[N-1], cows, diff, N);
	printf("%d is max distance between 2 cows : ", result);
	return 0;
}
