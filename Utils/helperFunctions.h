#include <string.h>

char* parsePath(char line[], const char symbol[])
{
	char *message;
	char * token = strtok(line, symbol);
	int current = 0;

	while (token != NULL) {

		token = strtok(NULL, " ");
		if (current == 0) {
			message = token;
			return message;
		}
		current = current + 1;
	}
	return message;
}