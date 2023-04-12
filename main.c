#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>


int main(int ac, char**argv)
{
	char *prompt = "$ ";
	char *input;
	char *inputCopy
	size_t n = 0;
	ssize_t numChars;
	const char *delim = " \n";
	int numTokens = 0;
	char *token;
	int i;

	(void)ac;

	while (1)
	{
		printf("%s", prompt);
		numChars = getline(&input, &n, stdin);

		if (numChars == -1)
		{
			printf("Exiting shell....\n");
			return (-1);
		}

		inputCopy = malloc(sizeof(char) * numChars);
		if ( inputCopy == NULL)
		{
			perror("Memory allocation error");
			return (-1);
		}

		strcpy(inputCopy, input);

		token = strtok(input, delim);

		while (token != NULL)
		{
			numTokens++;
			token = strtok(NULL, delim);
		}
		numTokens++;

		argv = malloc(sizeof(char *) * numTokens);

		token = strtok(inputCopy, delim);

		for ( i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		execve(argv);
	}

	free(inputCopy);
	free(input);

	return (0);
}

