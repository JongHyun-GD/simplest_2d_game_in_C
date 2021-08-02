/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:17:00 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 15:20:32 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void					my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char				*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_pos					world_to_screen(t_pos *w_pos, t_ber *ber, t_bmp *bmp)
{
	t_pos				pos;

	pos.x = 400 + ((w_pos->x - ber->player.x) * bmp->width);
	pos.y = 300 + ((w_pos->y - ber->player.y) * bmp->height);
	return (pos);
}
