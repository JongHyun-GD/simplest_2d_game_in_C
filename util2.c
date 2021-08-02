/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:50:43 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/24 15:22:12 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "unistd.h"

void				print_int(int num)
{
	int			len;
	int			c;

	len = 1;
	while (len <= num)
		len *= 10;
	len /= 10;
	while (len)
	{
		c = num / len + '0';
		write(STDOUT_FILENO, &c, 1);
		num %= len;
		len /= 10;
	}
}
