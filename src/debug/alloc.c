#include <stdlib.h>
#include <stdio.h>

#include "exit.h"

typedef struct s_alloc
{
	void	*ptr;
	size_t	size;
}	t_alloc;

t_alloc	g_allocs[1000];
size_t	g_alloci = 0;

void	*ft_malloc(size_t size)
{
	void		*res;

#ifndef DEBUG
	return (malloc(size));
#endif
	res = malloc(size);
	if (!res)
		exit_error("malloc failure");
	g_allocs[g_alloci].ptr = res;
	g_allocs[g_alloci].size = size;
	fprintf(stderr, "malloc: %02lu %p size %lu\n", g_alloci++, res, size);
	return (res);
}

void	*ft_free(void **m)
{
	size_t	i;

#ifndef DEBUG
	free(*m);
	*m = NULL;
	return (*m);
#endif
	i = 0;
	while (i < g_alloci && *m)
	{
		if (g_allocs[i].ptr == *m)
		{
			fprintf(stderr, "free:   %02lu %p size %lu\n", i, *m, g_allocs[i].size);
			g_allocs[i].ptr = NULL;
			free(*m);
			*m = NULL;
			return (*m);
		}
		++i;
	}
	fprintf(stderr, "unknown free: %p\n", *m);
	return (*m);
}

void	ft_exit(void)
{
	size_t	i;

	i = 0;
	while (i < g_alloci)
	{
		if (g_allocs[i].ptr)
		{
			fprintf(stderr, "leak: %02lu %p size %lu\n", i, g_allocs[i].ptr, g_allocs[i].size);
			free(g_allocs[i].ptr);
		}
		++i;
	}
}
