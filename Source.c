/*
	Assigned by:
	Lorin_Ben_Sasson #212289847
	Student2_Full_Name #ID
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/* Constant definitions */

#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Declarations of auxiliary functions */

void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* Function definitions */

void Ex1()
{
	/* Called functions:
		split, printStringsArray, freeMatrix */
	char letter = 'g';
	char str[] =  "Rony Goodman got a good mark";
	int size = strlen(str);
	int* p_size = &size;
	char** A = split(letter, str, p_size);
	printStringsArray(A, *p_size);
	freeMatrix(A, N);

}

void Ex2()
{
	createFile("filename.txt");
	printf("%c\n\n", commonestLetter("filename.txt"));
}

void Ex3()
{
	// char* str = "bc8 d"; // Create a const string "bc8 d". str is a pointer to that string.
	char str[] = "bc8 d"; // Same as char str[] = {'b', 'c', '8', ' ', 'd', '\0'}
	printf("Original string: %s\n", str);
	decode(str);
	printf("Decoded string : %s\n\n", str);
}

char** split(char letter, char* str, int* p_size)
{
	int i, j = 0;
	char** result;
	int countLetters = 0;
	bool isNewWord = true;
	for (i = 0; i < *p_size; i++) {
		if (isNewWord && (str[i] == letter || str[i] == toupper(letter))) {
			countLetters++;
		}
		if (str[i] == ' ') {
			isNewWord = true;
		}
		else {
			isNewWord = false;
		}
	}

	result = (char**)malloc(countLetters * sizeof(char*));
	isNewWord = true;
	int wordWithLetterStart = 0;
	bool isNewLetterWord = false; // Word that starts with "letter"
	bool isEndWord = false;
	for (i = 0; i < *p_size; i++) {
		if (isNewWord && (str[i] == letter || str[i] == toupper(letter))) {
			wordWithLetterStart = i;
			isNewLetterWord = true;
		}
		else if (isNewWord) {
			isNewLetterWord = false;
		}
		isNewWord = str[i] == ' ';
		isEndWord = str[i + 1] == ' ' || str[i + 1] == '\0';
		if (isNewLetterWord && isEndWord) {
			int wordSize = i + 1 - wordWithLetterStart;
			result[j] = malloc(wordSize + 1); // +1 for /0
			strncpy(result[j], str + wordWithLetterStart, wordSize);
			result[j][wordSize] = '\0';
			j++;

		}
	}
	*p_size = j; // pass by reference
	return result;
}

void createFile(char* filename)
{
	FILE* f = fopen(filename, "w"); // Returns a file handler, we work with the handler to operat on the file
	printf("Please enter your string:\n");
	char str[100];
	scanf("%s", str);
	fwrite(str, 1, strlen(str), f);
	fclose(f);

}
char commonestLetter(char* file) {
	FILE* f = fopen(file, "r");
	int max = 0;
	int monim[128] = { 0 };
	char rc;
	char c;



	rc = fscanf(f, "%c", &c);
	char common = c;
	while (rc != EOF) {

		if (c >= 'a' && c <= 'z') {
			toupper(c);
			monim[c]++;
		}
		if (c >= 'A' && c <= 'Z') {
			monim[c]++;
		}

		if (monim[c] >= max) {
			if (c > common) {
				max = monim[c];
				common = c;
			}

		}
		if (monim[c] > max) {

			max = monim[c];
			common = c;


		}
		rc = fscanf(f, "%c", &c);
	}

	fclose(f);
	return common;

}

void decode(char* text)
{
	int i = 0;
	int offset = 1;
	for (i = 0; i < strlen(text); i++) {
		if (text[i] == ' ') {
			offset = 1;
			continue;
		}
		text[i] = text[i] - offset;
		offset++;
	}
	/* Write Code Here! */
}

/* Definitions of auxiliary functions */

/* Write Definitions Here! */

void printStringsArray(char** str_arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%s\n", str_arr[i]);
	}
}
void freeMatrix(void** A, int rows) {
	for (int i = 0; i < rows; i++) {
		free(A[i]); // Free each row
	}
	 // Free the array of pointers
	free(A);
}