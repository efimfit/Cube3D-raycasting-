#include "cub3d.h"

char	*ft_empty(void)
{
	char	*empty;

	empty = (char *)malloc(sizeof(char));
	if (!empty)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}
