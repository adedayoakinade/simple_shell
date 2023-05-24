#include "shell.h"

/**
 * print_all_aliases - prints a list of all aliases
 */
void print_all_aliases()
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * print_aliases - prints each alias name on a separate line
 * @aliases: array of alias names
 * @tally: number of aliases in the array
 */
void print_aliases(char **aliases, int tally)
{
	int i = 0;

	while (i < tally)
	{
		char *alias_val = getenv(aliases[i]);

		if (alias_val != NULL)
		{
			printf("%s='%s'\n", aliases[i], alias_val);
		}
		i++;
	}
}


/**
 * define_aliases - surprise! it defines aliases
 * @names: array of alias names
 * @vals: array of alias values
 * @tally: number of aliases
 */
void define_aliases(char **names, char **vals, int tally)
{
	int i = 0;
	while (i < tally)
	{
		set_env(names[i], vals[i]);
		i++;
	}
}
