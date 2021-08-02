/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:49:05 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/24 14:54:28 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# include "ber_reader.h"

unsigned int		ft_strlen(char *str);
void				my_strcpy(char *src, char *dst,
						int dst_start, unsigned int size);
void				exit_err(char *str);
void				set_pos(t_pos *pos, int x, int y);
int					leave();
void				print_int(int num);

#endif
