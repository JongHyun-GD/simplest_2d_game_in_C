/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:48:03 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 15:11:28 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "unistd.h"
#include "stdlib.h"
#include "ber_reader.h"

unsigned int		ft_strlen(char *str)
{
	unsigned int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void				set_pos(t_pos *dst, int x, int y)
{
	dst->x = x;
	dst->y = y;
}

void				exit_err(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	exit(0);
}

void				my_strcpy(char *src, char *dst,
						int dst_start, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		dst[dst_start] = src[i];
		i++;
		dst_start++;
	}
}

int					leave(void)
{
	exit(0);
	return (0);
}
