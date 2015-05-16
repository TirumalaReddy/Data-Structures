#include <stdio.h>

int main(void) {
	char c[1000], read, pass = '1';
	int count = 0, subL = 0, size = 0, i=0, LPS[1000];
	read = getchar_unlocked();
	while (read != ' ' && read != '\n') {
		printf("%c", read);
		c[size ++] = read ;
		read = getchar_unlocked();
	}
	for (i=1; i<size;) {
		if (c[i] == c[count]) {
			count ++;
			LPS[i] = count;
			i++;
		} else if (count > 0){
			count = LPS[count-1];
		} else {
			LPS[i] = count;
			i++;
		}
	}
	printf("\n LPS array \n");
	for (i=0;i<size;i++) {
		printf("%d ",LPS[i]);
	}
	subL = size - LPS[size-1];
	printf("\n substring length %d \n", subL);
	for (i =2 ; i*subL-1 < size ; i++) {
		if (LPS[i*subL-1] != (i-1)*subL) {
			pass = '0';
		}
	}
	if (pass == '1') {
		printf("substring is  \"");
		for (i=0; i< subL; i++) {
			printf("%c", c[i]);
		}
		printf("\"  iterate \"%d\" times\n", size/subL);
	} else {
		printf("\n can not get String from any substring\n");
	}
}
