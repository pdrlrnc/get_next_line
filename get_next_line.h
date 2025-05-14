/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:27:08 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/14 15:32:35 by pedde-so         ###   ########.fr       */
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
char	*get_next_line_cont(int fd, char *buffer, char *result, int bytes_read);
int		ft_find_init_nl(char *buff);
char	*ft_handle_new_line(char *buff, char *result, int i);
char	*ft_process_buffer(char *buff, int i);
int		ft_read_data(int fd, char *buff);
char	*ft_realloc(char *result, int i, int *r);

#endif
