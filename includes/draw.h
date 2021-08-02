/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:11:36 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 15:18:43 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "main.h"

void	draw_all(t_data *img, t_berbmp *bmps, t_ber *ber);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_pos	world_to_screen(t_pos *w_pos, t_ber *ber, t_bmp *bmp);

#endif
