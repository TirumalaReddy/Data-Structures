#include <stdio.h>
#include<stdlib.h>
#define MAX 16

void computeCent(int cent,int* pal,char* str, int size) {
	int i,j,count=0;
	for (i=cent-1,j=cent+1;i>=0&&j<size;i--,j++) {
		if (str[i] == str[j]) {
			count++;
		} else {
			break;
		}
	}
	pal[cent] = count;
}
int main(void) {
	char *org,*str,c;
	int *pal,i=0,i_mirror,size=MAX, cent=1, length;
	org = (char*) malloc(sizeof(char)*MAX);
	scanf("%c", &c);
	while (c!= '\n' && c!= ' ') {
		org[i++] = c;
		if (i==size) {
			org = realloc(org, sizeof(char)* (size+=MAX));
		}
		scanf("%c", &c);
	}
	size = 2*i+1;
	str = (char*) malloc(sizeof(char)*(size));
	for (i=0;i<size;i+=2) {
		str[i] = '#';
		str[i+1] = org[i/2];
	}
	pal = (int*) malloc(sizeof(int)*size);
	pal[0]=0;
	cent=0;
	length = 0;
	i_mirror=0;
	for (i=1;i<size;i++) {
		// length = 0  new center
		// i-cent == pal[cent]  at the corner of the boundary new center
		// pal[2*cent-i] >= length - (i-cent) , mirrors value crossing boundary make it new center
		if ( length ==0 || i-cent == pal[cent] || pal[2*cent-i] >= length - (i-cent)) {
			cent = i;
			//printf("center %d\n", cent);
			computeCent(cent, pal, str, size);
			length = pal[cent];
		} else {
			pal[i] = pal[2*cent -i];
		}
	}
	for (i=0;i<size;i++) {
		printf("%c ",str[i]);
	}
	printf("\n");
	for(i=0;i<size;i++) {
		printf("%d ", pal[i]);
	}
	return 0;
}
