//worst case O(num of digits)  complexity

#include <stdio.h>
long long int ans = 0, L;
int digits = 0;

int count = 0;

int calcDigits(long long int N) {
	int digits = 0;
	long long int div = 1;
	while (N/div) {
		digits++;
		div *=10;
	}
	L = div/10;
	return digits;
}

int eval(long long int N, int flag) {
	long long int R;
	int i, lD, rD;
	//printf("evaluating %lld\n", N);
	R = 10;
	for(i=0; i<= (digits)/2;i++) {
		count++;
		lD = (N/L) % 10;
		rD = (N % R) / (R/10);
		
		if (i == digits/2) {
			if (digits & 1) {
				ans = ans *10 + lD;
				//printf("digits odd\n");
			}
			return ans;
		}

		if (lD <= rD || flag) {
			ans = ans * 10 + lD;
			flag = 0;
		} else {
			N = N/R;
			N = N % (L/ (R/10));
			N = N-1;
			if (rD == 0) rD = 9;
			N = N*10 + rD;
			digits = calcDigits(N);
			return eval(N, 1);
		}
		L = L/10;
		R = R*10;
	}
	return ans;
}

int main(void) {
	int T, div = 1, i, j, L , R, lD, rD;
	long long int N;
	scanf("%d", &T);
	while(T--) {
		count = 0;
		ans = 0;
		scanf("%lld", &N);
		digits = calcDigits(N);
		eval(N, 0);
		//printf("ans is %d\n", ans);
		printf("previous palindrome of %lld is \t", N);
		printf("%lld", ans);
		if (digits &1) {
			ans = ans/10;
		}
		while(ans >0) {
			printf("%lld", ans%10);
			ans = ans/10;
		}
		printf("\t complexity O(%d)\n", count);
	}
	return 0;
}
