/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:09:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 15:21:05 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include "bmp_reader.h"
# include "ber_reader.h"
# include "util.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_berbmp
{
	t_bmp		*empty;
	t_bmp		*wall;
	t_bmp		*player;
	t_bmp		*collectible;
	t_bmp		*exit;
}				t_berbmp;

typedef struct	s_vars
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_berbmp	berbmp;
	t_ber		*ber;
	t_data		img;
}				t_vars;

#endif
