#include "minishl.h"

void	*xmalloc(size_t size)
{
	void	*malloced_memory;

	malloced_memory = malloc(size);
	if (!malloced_memory)
		exit(EXIT_FAILURE);
	return (malloced_memory);
}