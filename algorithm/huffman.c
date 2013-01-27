#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#define NUM 256

typedef struct{
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;

/******* Choose two smallest from 0 to n in T *************/
void Select(HuffmanTree T, int len, int *s1, int *s2)
{
	int i = 0;
	while (T[i++].parent != -1);
	*s1 = i-1;
	while (T[i++].parent != -1);
	*s2 = i-1;
	if (T[*s1].weight>T[*s2].weight) {
		i = *s1;
		*s1 = *s2;
		*s2 = i;
	}
	for (i=0; i<=len; i++) {
		if(T[i].parent == -1) {
			if (T[*s1].weight > T[i].weight) {
				*s2 = *s1;
				*s1 = i;
			}
			else if (T[*s2].weight >T[i].weight && i != *s1)
				*s2 = i;
		}
	}
	return;
}

void show_binary(char ch)
{
	char i;

	for (i = 0; i < 8; i++) { 
		if (ch&0x80)
			printf("1");
		else printf("0");
		if (i == 3)
			printf(",");
		ch <<= 1;
	}
	printf(" ");
}

void HuffmanCoding(FILE *psrc, FILE *pdst, FILE *pdeciphering)
{
	int i;
	char ch;
		int m = 2*NUM-1;
		int size = m*sizeof(HTNode);
		HuffmanTree HT = (HuffmanTree)malloc(size);
		assert(HT);
		memset(HT, -1, size);

		for (i=0; i<NUM; i++)
			HT[i].weight = 0;
		while ((ch=fgetc(psrc)) != EOF) {
			(HT[ch].weight)++;
		}
		rewind(psrc);
/******************printf the Huffman weight****
	int j;
	for(j=0; j<NUM; j++) {
		printf("%c:%d\t", j, HT[j].weight);
	}
**********************************************/
		int s1, s2;
		for (i=NUM; i<m; i++) {
			Select(HT, i-1, &s1, &s2);
			HT[s1].parent = i; HT[s2].parent = i;
			HT[i].lchild = s1; HT[i].rchild = s2;
			HT[i].weight = HT[s1].weight + HT[s2].weight;
		}
/*******************printf the HuffmanTree*********
		int j;
		for (j=0; j<m; j++)
			printf("%d:w%d p%d l%d r%d\t\t", j, HT[j].weight, 
					HT[j].parent, HT[j].lchild, HT[j].rchild);
**************************************************/		
		char **HC = (char**)malloc(NUM*sizeof(char*));
		char* cd = (char*)malloc(NUM*sizeof(char));
		cd[NUM-1] = '\0';
		int start,c,f;
		for (i=0; i<NUM; i++) {
			start = NUM-1;
			for (c=i,f=HT[i].parent; f!=-1; c=f,f=HT[f].parent) {
				if (HT[f].lchild==c) cd[--start] ='0';
				else cd[--start] ='1';
			}
			HC[i] = (char *)malloc((NUM-start)*sizeof(char));
			strcpy(HC[i], &cd[start]);
		}
/************printf the Huffmancode******************************
		int j;
		for (j=0; j<NUM; j++) {
			printf("%c:%s\t", j, HC[j]);
		}
****************************************************************/
		char buff[100] = {0};	
		char k = 0, j = 0;
		while ((ch=fgetc(psrc)) != EOF) {
			i = -1; 
			while (HC[ch][++i] != '\0') {
				buff[j] <<= 1;
				k++;
				if (HC[ch][i] == '1')
					buff[j] |= 0x01;
				if ((k %= 8) == 0)
					j++;
				if (j == 100) {
					j =0;
					fwrite(buff, 1, 100, pdst);
				}

			}
		}
		buff[j] <<= (8-k);
		fwrite(buff, 1, j + 1, pdst);
		/*****************************************************
		printf("\ndata write to %s\n", dstfile);
		for (i=0; i<=j; i++)
		show_binary(buff[i]);
		***************************************************/
		rewind(pdst);
		fflush(pdst);
		c = 510;
		while (!feof(pdst)) {
			j = fread(buff, 1, 100, pdst);
			/********************************************
			printf("\nfrom read:\n");
			for (i=0; i<j; i++)
				show_binary(buff[i]);
			*******************************************/
			for (i=0; i<j; i++) {
				for (k=0; k<8; k++) {
					if (buff[i]&0x80)
						c = HT[c].rchild;
					else c = HT[c].lchild;
					if (HT[c].lchild == -1) {
					fputc((char)c, pdeciphering);
					c = 510;
					}
					buff[i] <<= 1;
				}	
			}
		}

/**************free the memery and return*******************/
		for(i=0; i<NUM; i++) {
			free(HC[i]);
		}
		free(cd);
		free(HC);
		free(HT);
		HT = NULL;
		fclose(pdst);
		fclose(psrc);
		fclose(pdeciphering);
	return;

}

int main(void)
{
	char srcfile[100], dstfile[100],deciphering[100];
	printf("Input source file:");
	scanf("%s", srcfile);
	printf("Input dest file:");
	scanf("%s", dstfile);
	printf("Input deciphering file:");
	scanf("%s", deciphering);
	FILE *psrc = fopen(srcfile, "r");
	FILE *pdst = fopen(dstfile, "w+");
	FILE *pdeciphering = fopen(deciphering, "w");
	if (psrc == NULL || pdst == NULL || pdeciphering == NULL) {
		printf("file opened failed\n");
		return -1;
	} 
	else 
	HuffmanCoding(psrc, pdst, pdeciphering);
	return 0;
}

