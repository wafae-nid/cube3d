/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:53:03 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/07 05:24:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

typedef struct s_trash
{
	void			*point;
	struct s_trash	*next;
}					t_trash;

typedef struct s_plines
{
	char	*prev;
	char	*line;
	char	*next;
}				t_plines;

int	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*custom_strdup(const char	*s1);
void	*gcmalloc(size_t size, int status_flag);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1, char *temp);
char	*until_newline(char *rest);
char	*rest_of_line(char *temp);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen2(const char *str, char *temp);
int 	is_valid_char(char c);
char	*ft_strtrim(const char *s1, const char *set);

#endif