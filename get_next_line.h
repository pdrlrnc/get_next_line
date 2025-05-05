/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:27:08 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/05 13:10:06 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_realloc(char *result);
char	*ft_process_buffer(char *buff, char *result, int *i, int *j);
char	*ft_handle_new_line(char *buff, char *result, int i, int j);
int		ft_read_data(int fd, char *buff, int *bytes_read);
char	*get_next_line_cont(int fd, char *buffer, char *result);

#endif
