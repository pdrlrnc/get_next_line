/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:26:40 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/05 15:50:24 by pedde-so         ###   ########.fr       */
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
	int	j;
	int	bytes_read;

	i = 0;
	j = 0;
	result = NULL;
	result = ft_process_buffer(buffer, result, &i, &j);
	if (i == -1)
	{
		
		return (NULL);
	}
	if (i < BUFFER_SIZE)
		return (ft_handle_new_line(buffer, result, i, j));
	while (ft_read_data(fd, buffer, &bytes_read) != 0)
	{
		if (bytes_read == -1)
		{
			free(result);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		i = 0;
		result = ft_process_buffer(buffer, result, &i, &j);
		if (i == -1)
		{
			free(result);
			return (NULL);
		}
		if (i < BUFFER_SIZE)
			return (ft_handle_new_line(buffer, result, i, j));
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
			result = get_next_line(fd);
			i++;
		}
		close(fd);
	}
}
