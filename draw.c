/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:08:48 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 15:18:54 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void					draw_bmp(t_data *img, int px, int py, t_bmp *bmp)
{
	unsigned int		x;
	unsigned int		y;

	y = bmp->height - 1;
	while (1)
	{
		x = 0;
		while (x < bmp->width)
		{
			if (!(bmp->pixels[y * bmp->width + x].r == 0xff) ||
				!(bmp->pixels[y * bmp->width + x].g == 0xff) ||
				!(bmp->pixels[y * bmp->width + x].b == 0xff))
				my_mlx_pixel_put(img, px + x, py + (bmp->height - y),
								bmp->pixels[y * bmp->width + x].r << 16 |
								bmp->pixels[y * bmp->width + x].g << 8 |
								bmp->pixels[y * bmp->width + x].b);
			x++;
		}
		if (y == 0)
			break ;
		y--;
	}
}

void					draw_bg(t_data *img, t_berbmp *bmps, t_ber *ber)
{
	unsigned int		i;
	t_pos				pos;

	i = 0;
	while (i < ber->width * ber->height)
	{
		pos.x = i % ber->width;
		pos.y = i / ber->width;
		pos = world_to_screen(&pos, ber, bmps->wall);
		if (pos.x < 0 || pos.x >= 800 - (bmps->wall->width)
		|| pos.y < 0 || pos.y >= 600 - (bmps->wall->height))
		{
			i++;
			continue;
		}
		if (ber->map[i] == '1')
			draw_bmp(img, pos.x, pos.y, bmps->wall);
		else
			draw_bmp(img, pos.x, pos.y, bmps->empty);
		i++;
	}
}

void					draw_obj(t_data *img, t_berbmp *bmps, t_ber *ber)
{
	int					i;
	t_pos				pos;

	i = 0;
	draw_bmp(img, 400, 300, bmps->player);
	while (i < ber->c_cnt)
	{
		pos = world_to_screen(&ber->collectibles[i], ber, bmps->collectible);
		if (pos.x >= 0 && pos.x < 800 - (bmps->collectible->width)
			&& pos.y >= 0 && pos.y < 600 - (bmps->collectible->height))
			if (ber->collectibles[i].x != 1 || ber->collectibles[i].y != 0)
				draw_bmp(img, pos.x, pos.y, bmps->collectible);
		i++;
	}
	i = 0;
	while (i < ber->e_cnt)
	{
		pos = world_to_screen(&ber->exits[i], ber, bmps->exit);
		if (pos.x >= 0 && pos.x < 800 - (bmps->exit->width)
		&& pos.y >= 0 && pos.y < 600 - (bmps->exit->height))
			draw_bmp(img, pos.x, pos.y, bmps->exit);
		i++;
	}
}

void					clear_image(t_data *img)
{
	int					y;
	int					x;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			my_mlx_pixel_put(img, x, y, 0);
			x++;
		}
		y++;
	}
}

void					draw_all(t_data *img, t_berbmp *bmps, t_ber *ber)
{
	clear_image(img);
	draw_bg(img, bmps, ber);
	draw_obj(img, bmps, ber);
}
