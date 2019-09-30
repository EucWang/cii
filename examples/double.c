//static char rcsid[] = "$Id$";
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
int linenum;
int double_getword(FILE *, char *, int);
void double_word(char *, FILE *);
int double_main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "%s: can't open '%s' (%s)\n",
				argv[0], argv[i], strerror(errno));
			return EXIT_FAILURE;
		} else {
			double_word(argv[i], fp);
			fclose(fp);
		}
	}
	if (argc == 1) double_word(NULL, stdin);
	return EXIT_SUCCESS;
}
int double_getword(FILE *fp, char *buf, int size) {
	int c;
	c = getc(fp);
	for ( ; c != EOF && isspace(c); c = getc(fp))
		if (c == '\n')
			linenum++;
	{
		int i = 0;
		for ( ; c != EOF && !isspace(c); c = getc(fp))
			if (i < size - 1)
				buf[i++] = tolower(c);
		if (i < size)
			buf[i] = '\0';
	}
	if (c != EOF)
		ungetc(c, fp);
	return buf[0] != '\0';
}
void double_word(char *name, FILE *fp) {
	char prev[128], word[128];
	linenum = 1;
	prev[0] = '\0';
	while (double_getword(fp, word, sizeof word)) {
		if (isalpha(word[0]) && strcmp(prev, word)==0)
			{
				if (name)
					printf("%s:", name);
				printf("%d: %s\n", linenum, word);
			}
		strcpy(prev, word);
	}
}
