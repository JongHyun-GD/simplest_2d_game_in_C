/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:06:11 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 14:17:22 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_READER_H
# define BMP_READER_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_px
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_px;

typedef struct		s_bmp
{
	unsigned int	size;
	unsigned int	data_offset;
	unsigned int	width;
	unsigned int	height;
	t_px			*pixels;
}					t_bmp;

t_bmp				*read_bmp(char *filename);
#endif
