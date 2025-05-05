/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:50:13 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/05 15:42:09 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_process_buffer(char *buff, char *result, int *i, int *j)
{
	while (*i < BUFFER_SIZE && buff[*i] == '\0')
		(*i)++;
	if (*i < BUFFER_SIZE)
	{
		while (*i < BUFFER_SIZE && buff[*i] != '\0' && buff[*i] != '\n')
		{
			result = ft_realloc(result);
			if (!result)
			{
				*i = -1;
				return (NULL);
			}
			*(result + *(j)) = buff[*i];
			buff[*(i)] = '\0';
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	return (result);
}

char	*ft_handle_new_line(char *buff, char *result, int i, int j)
{
	result = ft_realloc(result);
	if (!result)
		return (NULL);
	*(result + j) = '\n';
	buff[i] = '\0';
	return (result);
}

int	ft_read_data(int fd, char *buff, int *bytes_read)
{
	*bytes_read = read(fd, buff, BUFFER_SIZE);
	return (*bytes_read);
}

char	*ft_realloc(char *result)
{
	int		i;
	char	*new_result;

	if (result == NULL)
	{
		new_result = malloc(2);
		if (!new_result)
			return (NULL);
		*(new_result + 1) = '\0';
		return (new_result);
	}
	i = 0;
	while (*(result + i))
		i++;
	new_result = malloc(i + 2);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	i = -1;
	while (*(result + ++i))
		*(new_result + i) = *(result + i);
	free(result);
	*(new_result + i + 1) = '\0';
	return (new_result);
}
