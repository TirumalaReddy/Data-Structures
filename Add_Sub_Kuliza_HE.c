#include <stdio.h>
#include<stdlib.h>
void merge(int *a, int start, int mid, int end) {
	int temp[end-start+1], i, j, k=0;
	for (i=start, j=mid+1; i<=mid && j <=end;) {
		if (a[i] > a[j]) {
			temp[k++] = a[j];
			j++;
		} else {
			temp[k++] = a[i];
			i++;
		}
	}
	for (;i<=mid;i++) {
		temp[k++] = a[i];
	}
	for (;j<=end;j++) {
		temp[k++] = a[j];
	}
	k=0;
	for (i=start;i<=end;i++,k++) {
		a[i] = temp[k];
	}
}
void mergeSort(int *a, int start, int end) {
	if (start < end) {
		int mid = start + (end - start)/2;
		mergeSort(a, start, mid);
		mergeSort(a, mid+1, end);
		merge(a, start, mid, end);
	}
}
long int computeMin(int *al, int ls, int *ar, int rs, int k) {
	long int min1 = 1000000, min2=0;
	int i, r;
	// complete left sum
	for(i=0;i<ls;i++) {
		min2 +=al[i]; 
	}
	r = k-ls;
	// rem right sum for total K
	for(i=0;i<r;i++) {
		min2+=ar[i];
	}
	if (min1 > min2) {
		min1 = min2;
	}
	// remove left, move right
	for(i=r;i<rs;i++) {
		min2 -= al[ls-1-(i-r)];
		min2+= ar[i];
		if(min1 > min2) {
			min1 = min2;
		}
	}
	return min1;
}
int main(void) {
	int T,N,K, inc=3, dec=5;
	long int result2=1000, result1;
	scanf("%d", &T);
	while (T--) {
		int *a,i;
		int diff;
		scanf("%d %d", &N, &K);
		a = (int*) malloc(sizeof(int)*N);
		for(i=0;i<N;i++) {
			scanf("%d", &a[i]);
		}
		mergeSort(a, 0, N-1);
		diff = 0;
		result2 = 1000000;
		K=K-1;
		for (i=0;i<N;i++) {
			int j=0,m=0,l,r, result1=0, al[K], ar[K];
			l=(i < K) ? i : K; // l elements on left side
			r= (i+K > N-1) ? N-i-1 : K ; // r elements on right side
			while(l) {
				al[j] = (a[i]-a[i-j-1])*inc;
				j++;
				l--;
			}
			while(r) {
				ar[m] = (a[i+m+1]-a[i])*dec;
				m++;
				r--;
			}
			result1 = computeMin(al, j, ar, m, K);
			if (result2 > result1) {
				result2 = result1;
			}
		}
		
		printf("%ld\n",result2);
	}
	return 0;
}
