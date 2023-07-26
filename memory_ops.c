#include "shell.h"

/**
 * free_buffer - Frees a buffer.
 * @buffer: The buffer to be freed.
 */
void free_buffer(char **buffer)
{
	int counter = 0;

	if (buffer)
	{
		for (counter = 0; buffer[counter]; counter++)
			free(buffer[counter]);
		free(buffer);
	}
}
