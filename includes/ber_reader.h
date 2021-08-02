/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ber_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:30:22 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/23 15:06:02 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BER_READER_H
# define BER_READER_H
# include "unistd.h"
# include "fcntl.h"
# include "stdlib.h"
# include "stdio.h"

typedef struct		s_pos
{
	unsigned int	x;
	unsigned int	y;
}					t_pos;

typedef struct		s_ber
{
	unsigned int	width;
	unsigned int	height;
	char			*map;
	t_pos			player;
	t_pos			*collectibles;
	int				c_cnt;
	t_pos			*exits;
	int				e_cnt;
	int				collected;
	int				move;
}					t_ber;

t_ber				*read_ber(char *filename);

#endif
