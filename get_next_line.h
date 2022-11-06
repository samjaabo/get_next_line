/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:12:46 by samjaabo          #+#    #+#             */
/*   Updated: 2022/11/06 12:52:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
#define FT_GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

char		*ft_join(char *s1, char *s2);
char		*ft_read(int fd, int *count, int *eof);
char		*get_line(char *data, int *count, int *lock);
char		*del_line(char *data);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);

#endif