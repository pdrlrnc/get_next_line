/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:26:40 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/13 13:14:14 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result;

	result = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	return (get_next_line_cont(fd, buffer, result));
}

char	*get_next_line_cont(int fd, char *buffer, char *result)
{
	int	i;
	int	bytes_read;

	result = NULL;
	bytes_read = 1;
	if (!buffer[0])
		bytes_read = -1;
	while (bytes_read)
	{
		if (bytes_read != -1)
		{
			i = ft_find_init_nl(buffer);
			result = ft_handle_new_line(buffer, result, i);
			if (!result)
				return (NULL);
			buffer = ft_process_buffer(buffer, i + 1);
			if (i < BUFFER_SIZE)
				return (result);
		}
		bytes_read = ft_read_data(fd, buffer);
		buffer[bytes_read] = '\0';
	}
	if (!bytes_read)
	{
		free(result);
		return (NULL);
	}
	return (result);
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
		close(fd);
	}
}
