#include <stdio.h>
#define mod(x) (x%1000000007)
#define MAX 128
int main(void) {
	unsigned long long int N, sum1[MAX], sum2[MAX];
	unsigned long long int result=0;
	int i=0, max=0, num;
	scanf("%llu", &N);
	for(i=0;i<MAX;i++) {
		sum1[i] = 0;
		sum2[i] = 0;
	}
	while (N--) {
		int exor, temp=max;
		scanf("%d", &num);
		for(i=0;i<=max;i++) {
			if (sum1[i] > 0) {
				exor = i^num;
				sum2[exor]+=sum1[i];
				if(temp < exor) {
					temp = exor;
				}
			}
		}
		for(i=0;i<MAX;i++) {
			sum2[i]=mod(sum2[i]);
			sum1[i] = sum2[i];
		}
		max = temp;
		if (max < num) max=num;
		sum1[num]++;
		sum2[num]++;
	}
	for(i=0;i<=max;i++) {
		unsigned long long int count;
		if(sum2[i] > 0) {
			count = sum2[i];
			result += count*(count-1)/2;
			result = mod(result);
		}
	}
	printf("%llu", result);
	return 0;
}
