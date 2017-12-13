#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "argparser.h"

#define TRUE  1
#define FALSE 0

void parse_args(int argc, char *argv[], Argument *arguments[], int arguments_count) {
	for (int x = 1; x < argc; x++) {
		for (int y = 0; argv[x][y] != '\0'; y++) {
			if (argv[x][y] == '-') { // yey, parameter.
				char var = argv[x][(++y)++]; // Parameter, increment before to get form '-' to parameter, increment after
				char param[999] = {};        // to get to whitespace
				int c = 0; // length of passed data

				for (int j = ++y; argv[x][j] != ' ' && argv[x][j] != '\0'; j++) { // increment before to skip whitespace
					param[c++] = argv[x][j];
				}

				Argument *curr;
				int found = FALSE;
				for (int j = 0; j < arguments_count; j++) {
					curr = *(arguments + j);

					if ((var & ~32) == (curr->args & ~32)) { // find corresponding argument
						found = TRUE;
						break;
					}
				}

				if (!found)
					continue;

				curr->passed = FALSE;

				if (curr->type == TYPE_FLAG)
					curr->passed = TRUE;

				if (curr->type == TYPE_CHAR) {
					if (c > 1)
						curr->invalid = TRUE;
					else {
						curr->passed = TRUE;
						curr->value.chr = param[0];
					}
				}

				if (curr->type == TYPE_STR || curr->type == TYPE_STR_ALPHA || curr->type == TYPE_STR_ALPHANUM ||
						curr->type == TYPE_STR_ALPHA_LOWER || curr->type == TYPE_STR_ALPHA_UPPER) {
					for (int j = 0; j < c; j++) {
						if (curr->type == TYPE_STR && !(param[j] > 31 && param[j] < 127))
							curr->invalid = TRUE;

						if (curr->type == TYPE_STR_ALPHA && !(param[j] > 64 && param[j] < 91)
						    && !(param[j] > 96 && param[j] < 123))
							curr->invalid = TRUE;

						if (curr->type == TYPE_STR_ALPHA_LOWER && !(param[j] > 96 && param[j] < 123))
							curr->invalid = TRUE;

						if (curr->type == TYPE_STR_ALPHA_UPPER && !(param[j] > 64 && param[j] < 91))
							curr->invalid = TRUE;

						if (curr->type == TYPE_STR_ALPHANUM && !(param[j] > 47 && param[j] < 58)
						    && !(param[j] > 64 && param[j] < 91) && !(param[j] > 96 && param[j] < 123))
							curr->invalid = TRUE;
					}

					if (curr->invalid == FALSE) {
						curr->passed = TRUE;
						curr->value.str = malloc(strlen(param) * sizeof(char));

						if (curr->value.str == NULL) {
							printf("FAILED TO ALLOCATE MEMORY");
							exit(-1);
						}

						strcpy(curr->value.str, param);
					}
				}

				if (curr->type == TYPE_INT) {
					int num = 0;

					for (int j = 0; j < c; j++) {
						if (param[j] > 47 && param[j] < 58)
							num += (param[j] - 48) * pow(10, j);
						else {
							curr->invalid = TRUE;
						}
					}

					if (curr->invalid == FALSE) {
						curr->passed = TRUE;
						curr->value.integer = num;
					}
				}
			}
		}
	}
}