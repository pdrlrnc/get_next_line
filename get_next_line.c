/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:26:40 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/16 10:10:09 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result;
	int			bytes_read;

	result = NULL;
	bytes_read = 1;
	if (!buffer[0])
		bytes_read = -2;
	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	return (get_next_line_cont(fd, buffer, result, bytes_read));
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*result;
	int		i;

	i = 1;
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		result = get_next_line(fd);
		while (result != NULL)
		{
			printf("call #%d: %s", i, result);
			free(result);
			result = get_next_line(fd);
			i++;
		}
		free(result);
		if(fd != -1)
			close(fd);
	}
}
