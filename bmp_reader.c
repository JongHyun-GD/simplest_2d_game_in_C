/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:05:20 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 14:13:16 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_reader.h"
#include "math.h"

unsigned int			hex_to_uint(unsigned char *buf, int start, int end)
{
	unsigned int	res;
	int				exp;

	res = 0;
	exp = 0;
	while (start < end)
	{
		res += (buf[start] % 16) * pow(16, exp);
		exp++;
		res += ((buf[start] / 16) % 16) * pow(16, exp);
		exp++;
		start++;
	}
	return (res);
}

int						read_file_header(int fd, t_bmp *bmp)
{
	unsigned char		buf[14];

	if (read(fd, &buf, 14) == -1)
		return (-1);
	if (buf[0] != 0x42 && buf[1] != 0x4d)
		return (-1);
	bmp->size = hex_to_uint((unsigned char*)&buf, 2, 6);
	bmp->data_offset = hex_to_uint((unsigned char*)&buf, 10, 14);
	return (0);
}

int						read_info_header(int fd, t_bmp *bmp)
{
	unsigned char		buf[40];

	if (read(fd, &buf, 40) == -1)
		return (-1);
	bmp->width = hex_to_uint((unsigned char*)&buf, 4, 8);
	bmp->height = hex_to_uint((unsigned char*)&buf, 8, 12);
	return (0);
}

int						read_pixels(int fd, t_bmp *bmp)
{
	char				buf1[bmp->size - bmp->data_offset];
	char				buf2[bmp->size - bmp->data_offset];
	unsigned int		i;

	if (read(fd, buf1, bmp->data_offset - 54) == -1 ||
		read(fd, buf2, bmp->size - bmp->data_offset) == -1)
		return (-1);
	if (!(bmp->pixels = (t_px*)malloc(sizeof(t_px) * bmp->height * bmp->width)))
		return (-1);
	i = 0;
	while (i < bmp->height * bmp->width)
	{
		bmp->pixels[i].b = buf2[i * 3];
		bmp->pixels[i].g = buf2[i * 3 + 1];
		bmp->pixels[i].r = buf2[i * 3 + 2];
		i++;
	}
	return (0);
}

t_bmp					*read_bmp(char *filename)
{
	int					fd;
	t_bmp				*bmp;

	if (!(bmp = (t_bmp*)malloc(sizeof(t_bmp))))
		return (0);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror("failed to open file.\n");
		return (0);
	}
	if (read_file_header(fd, bmp) || read_info_header(fd, bmp)
		|| read_pixels(fd, bmp))
	{
		perror("failed to read bmp.\n");
		return (0);
	}
	close(fd);
	return (bmp);
}
