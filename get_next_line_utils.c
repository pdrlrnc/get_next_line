/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:50:13 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/13 14:32:42 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find_init_nl(char *buff)
{
	int	i;

	i = 0;
	while (*(buff + i) && *(buff + i) != '\n')
		i++;
	return (i);
}

char	*ft_handle_new_line(char *buff, char *result, int i)
{
	int	r;
	int	k;

	result = ft_realloc(result, i, &k);
	if (!result)
		return (NULL);
	r = 0;
	while (r <= i)
	{
		*(result + k) = *(buff + r);
		*(buff + r) = '\0';
		r++;
		k++;
	}
	*(result + k) = '\0';
	return (result);
	
}

char	*ft_process_buffer(char *buff, int i)
{
	int	k;

	k = 0;
	while (*(buff + i) && i < BUFFER_SIZE)
	{
		*(buff + k) = *(buff + i);
		*(buff + i) = '\0';
		i++;
		k++;
	}
	return (buff);
}

int	ft_read_data(int fd, char *buff)
{
	int	bytes_read;

	bytes_read = read(fd, buff, BUFFER_SIZE);
	return (bytes_read);
}

char	*ft_realloc(char *result, int i, int *r)
{
	char	*new_result;

	*r = 0;	
	if (result)
		while (*(result + *r))
			(*r)++;
	new_result = malloc(i + *r + 1);
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
