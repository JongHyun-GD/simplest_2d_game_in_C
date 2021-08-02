/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ber_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:28:09 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/25 13:01:35 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ber_reader.h"
#include "get_next_line.h"
#include "util.h"

void				cnt_obj(t_ber *ber, char *line)
{
	unsigned int	i;

	i = -1;
	while (++i < ber->width)
	{
		if (line[i] == 'C')
			ber->c_cnt++;
		else if (line[i] == 'E')
			ber->e_cnt++;
	}
}

int					check_format(char *filename, t_ber *ber)
{
	int				fd;
	int				h;
	char			*line;

	h = 0;
	ber->c_cnt = 0;
	ber->e_cnt = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit_err("Error\nFailed to open\n");
	while (get_next_line(fd, &line) == 1)
	{
		ber->width = (h++) == 0 ? ft_strlen(line) : ber->width;
		if (ber->width != ft_strlen(line) || line[0] != '1' ||
			line[ber->width - 1] != '1')
			exit_err("Error\nThe map is not closed or rect!\n");
		cnt_obj(ber, line);
		free(line);
	}
	free(line);
	ber->height = h;
	return (close(fd));
}

int					read_map(char *filename, t_ber *ber)
{
	int				fd;
	int				i;
	char			*line;
	int				flag;

	if ((fd = open(filename, O_RDONLY)) == -1)
		exit_err("Error\nFailed to open\n");
	if (!(ber->map = (char *)malloc(ber->width * ber->height)))
		exit_err("Error\nMalloc failed\n");
	i = 0;
	while ((flag = get_next_line(fd, &line)) >= 0)
	{
		if (flag == 0)
		{
			free(line);
			break ;
		}
		my_strcpy(line, ber->map, i, ber->width);
		free(line);
		i += ber->width;
	}
	return (0);
}

int					read_obj(t_ber *ber)
{
	unsigned int	i;
	int				c;
	int				e;

	if (!(ber->collectibles = (t_pos*)malloc(sizeof(t_pos) * ber->c_cnt)) |
		!(ber->exits = (t_pos*)malloc(sizeof(t_pos) * ber->e_cnt)))
		exit_err("Error\nMalloc failed\n");
	i = 0;
	c = 0;
	e = 0;
	while (i < ber->height * ber->width)
	{
		if (ber->map[i] == 'P')
			set_pos(&ber->player, i % ber->width, i / ber->width);
		else if (ber->map[i] == 'C')
			set_pos(&ber->collectibles[c++], i % ber->width, i / ber->width);
		else if (ber->map[i] == 'E')
			set_pos(&ber->exits[e++], i % ber->width, i / ber->width);
		else if (ber->map[i] != '0' && ber->map[i] != '1')
			exit_err("Error\nInvalid map format!\n");
		i++;
	}
	return (0);
}

t_ber				*read_ber(char *filename)
{
	t_ber			*ber;
	int				len;

	len = ft_strlen(filename);
	if (filename[len - 4] == '.' && filename[len - 3] == 'b' &&
	filename[len - 3] == 'e' && filename[len - 3] == 'r')
		exit_err("Error\nfile format is not '.ber'!\n");
	if (!(ber = (t_ber*)malloc(sizeof(t_ber))))
		return (0);
	if (check_format(filename, ber) == -1)
		exit_err("Error\nInvalid map format!\n");
	read_map(filename, ber);
	ber->player.x = 0;
	if (read_obj(ber) == -1 | ber->player.x == 0)
		exit_err("Error\nInvalid map format!\n");
	return (ber);
}
