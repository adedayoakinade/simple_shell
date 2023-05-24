#include "shell.h"

/**
 * comment_handler - checks for comments in code
 * 	and deals with them accordingly
 *
 */
void comment_handler(char *line)
{
	char *com_ptr = strchr(line, '#');

	if (com_ptr != NULL)
	{
		*com_ptr = '\0';
	}
}
