#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct trie node;
struct trie {
	char value;
	int prefix_count;
	int word_count;
	struct trie *edges[26];
};

struct trie* createNode(char val) {
	int i;
	struct trie* vertex = (struct trie*) malloc(sizeof(struct trie));
	vertex->value = val;
	vertex->prefix_count = 0;
	vertex->word_count = 0;
	for(i=0;i<26;i++) {
		vertex->edges[i] = NULL;
	}
	return vertex;
}

struct trie* insert(struct trie* vertex, char val) {
 if (vertex->edges[val-97] == NULL) {
 	vertex->edges[val-97] = createNode(val);
 }
 vertex->edges[val-97]->prefix_count++;
 return vertex->edges[val-97];
}

void getPrefixesOneLevel(struct trie* node) {
	int i;
	for (i=0;i<26; i++) {
		if (node->edges[i] != NULL) {
			printf("\n%c", node->edges[i]->value);
		}
	}
}

int main(void) {
	int choice, count;
	char str;
	struct trie *root, *vertex;
	root = createNode(' ');
	scanf("%d\n", &choice);
	while (choice!=0) {
		vertex = root;
		switch (choice) {
			case 1:
			str = getchar_unlocked();
			while (str != '\n') {
				vertex = insert(vertex, str);
				str = getchar_unlocked();
			}
			vertex->word_count++;
			break;
			case 2:
			str = getchar_unlocked();
			while (str != '\n') {
				if (vertex != NULL) 
				{
					vertex = vertex->edges[str-97];
				}
				str = getchar_unlocked();
			}
			if (vertex != NULL) {
				printf("prefix count : %d", vertex->prefix_count);
			} else {
				printf("prefix count : 0");
			}
			break;
			case 3:
			str = getchar_unlocked();
			while (str != '\n') {
				if (vertex != NULL) 
				{
					vertex = vertex->edges[str-97];
				}
				str = getchar_unlocked();
			}
			if (vertex != NULL) {
				printf("word count : %d", vertex->word_count);
			} else {
				printf("word count : 0");
			}
			break;
			case 4:
			str = getchar_unlocked();
			while (str != '\n') {
				if (vertex != NULL) 
				{
					vertex = vertex->edges[str-97];
				}
				printf("%c",str);
				str = getchar_unlocked();
			}
			printf("\nnext character options");
			getPrefixesOneLevel(vertex);
			default :
			break;
		}
		scanf("%d\n", &choice);
	}
	return 0;
}
