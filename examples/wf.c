//static char rcsid[] = "$Id$";
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "atom.h"
#include "table.h"
#include "mem.h"
#include "getword.h"
#include <string.h>
void wf(char *, FILE *);
int wf_first(int c);
int wf_rest (int c);
int wf_compare(const void *x, const void *y);
void wf_vfree(const void *, void **, void *);
int wf_main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "%s: can't open '%s' (%s)\n",
				argv[0], argv[i], strerror(errno));
			return EXIT_FAILURE;
		} else {
			wf(argv[i], fp);
			fclose(fp);
		}
	}
	if (argc == 1) wf(NULL, stdin);
	return EXIT_SUCCESS;
}
void wf(char *name, FILE *fp) {
	Table_T table = Table_new(0, NULL, NULL);
	char buf[128];
	while (getword(fp, buf, sizeof buf, wf_first, wf_rest)) {
		const char *word;
		int i, *count;
		for (i = 0; buf[i] != '\0'; i++)
			buf[i] = tolower(buf[i]);
		word = Atom_string(buf);
		count = Table_get(table, word);
		if (count)
			(*count)++;
		else {
			NEW(count);
			*count = 1;
			Table_put(table, word, count);
		}
	}
	if (name)
		printf("%s:\n", name);
	{ int i;
	  void **array = Table_toArray(table, NULL);
	  qsort(array, Table_length(table), 2*sizeof (*array),
	  	wf_compare);
	  for (i = 0; array[i]; i += 2)
	  	printf("%d\t%s\n", *(int *)array[i+1],
	  		(char *)array[i]);
	  FREE(array); }
	Table_map(table, wf_vfree, NULL);
	Table_free(&table);
}
int wf_first(int c) {
	return isalpha(c);
}
int wf_rest(int c) {
	return isalpha(c) || c == '_';
}
int wf_compare(const void *x, const void *y) {
	return strcmp(*(char **)x, *(char **)y);
}
void wf_vfree(const void *key, void **count, void *cl) {
	FREE(*count);
}
