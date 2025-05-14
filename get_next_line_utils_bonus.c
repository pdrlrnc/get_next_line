/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:50:13 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/14 15:34:29 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_find_init_nl(char *buff, int fd)
{
	int	i;

	i = 0;
	while (*(buff + fd * BUFFER_SIZE + i)
		&& *(buff + fd * BUFFER_SIZE + i) != '\n')
		i++;
	return (i);
}

char	*ft_handle_new_line(char *buff, char *result, int i, int fd)
{
	int	r;
	int	k;

	result = ft_realloc(result, i, &k);
	if (!result)
		return (NULL);
	r = 0;
	while (r <= i)
	{
		*(result + k) = *(buff + fd * BUFFER_SIZE + r);
		*(buff + fd * BUFFER_SIZE + r) = '\0';
		r++;
		k++;
	}
	*(result + k) = '\0';
	return (result);
}

char	*ft_process_buffer(char *buff, int i, int fd)
{
	int	k;

	k = 0;
	while (*(buff + fd * BUFFER_SIZE + i) && i < BUFFER_SIZE)
	{
		*(buff + fd * BUFFER_SIZE + k) = *(buff + fd * BUFFER_SIZE + i);
		*(buff + fd * BUFFER_SIZE + i) = '\0';
		i++;
		k++;
	}
	return (buff);
}

char	*get_next_line_cont(int fd, char *buffer, char *result, int bytes_read)
{
	int	i;

	result = NULL;
	while (bytes_read)
	{
		if (bytes_read != -2)
		{
			i = ft_find_init_nl(buffer, fd);
			result = ft_handle_new_line(buffer, result, i, fd);
			if (!result)
				return (NULL);
			buffer = ft_process_buffer(buffer, i + 1, fd);
			if (*(result + i) && i < BUFFER_SIZE)
				return (result);
		}
		bytes_read = read(fd, buffer + fd * BUFFER_SIZE, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(result), NULL);
		*(buffer + fd * BUFFER_SIZE + bytes_read) = '\0';
	}
	if (!bytes_read && !*result)
		return (free(result), NULL);
	return (result);
}

char	*ft_realloc(char *result, int i, int *r)
{
	char	*new_result;

	*r = 0;
	if (result)
		while (*(result + *r))
			(*r)++;
	new_result = malloc(i + *r + 2);
	if (!new_result)
	{
		if (result)
			free(result);
		return (NULL);
	}
	if (!result)
		return (new_result);
	*r = 0;
	while (*(result + *r))
	{
		*(new_result + *r) = *(result + *r);
		(*r)++;
	}
	free(result);
	return (new_result);
}
