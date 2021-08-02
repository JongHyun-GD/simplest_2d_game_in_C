/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 22:58:33 by jongpark          #+#    #+#             */
/*   Updated: 2021/06/25 12:57:13 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "draw.h"

void			load_bmps(t_berbmp *bmps)
{
	bmps->empty = read_bmp("bmp/empty_tile.bmp");
	bmps->wall = read_bmp("bmp/wall_tile.bmp");
	bmps->player = read_bmp("bmp/player.bmp");
	bmps->collectible = read_bmp("bmp/collectible.bmp");
	bmps->exit = read_bmp("bmp/exit.bmp");
}

void			check_collision(t_ber *ber)
{
	int			i;

	i = -1;
	while (++i < ber->c_cnt)
	{
		if (ber->player.x == ber->collectibles[i].x &&
			ber->player.y == ber->collectibles[i].y)
		{
			ber->collectibles[i].x = 1;
			ber->collectibles[i].y = 0;
			ber->collected++;
		}
	}
	i = -1;
	while (++i < ber->e_cnt)
	{
		if (ber->player.x == ber->exits[i].x &&
			ber->player.y == ber->exits[i].y &&
			ber->collected == ber->c_cnt)
		{
			write(STDOUT_FILENO, "CLEAR!!\n", 8);
			exit(0);
		}
	}
}

void			move_player(int dx, int dy, t_vars *vars)
{
	int			x;
	int			y;

	x = vars->ber->player.x + dx;
	y = vars->ber->player.y + dy;
	if (vars->ber->map[y * vars->ber->width + x] != '1')
	{
		vars->ber->move += 1;
		write(STDOUT_FILENO, "move: ", 6);
		print_int(vars->ber->move);
		write(STDOUT_FILENO, "\n", 1);
		vars->ber->player.x = x;
		vars->ber->player.y = y;
		check_collision(vars->ber);
	}
	mlx_clear_window(vars->mlx_ptr, vars->mlx_win);
	draw_all(&(vars->img), &(vars->berbmp), vars->ber);
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, vars->img.img, 0, 0);
}

int				parsing_key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		move_player(0, -1, vars);
	else if (keycode == KEY_A)
		move_player(-1, 0, vars);
	else if (keycode == KEY_S)
		move_player(0, 1, vars);
	else if (keycode == KEY_D)
		move_player(1, 0, vars);
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_vars		vars;

	if (argc != 2)
		exit_err("[Usage]: ./so_long [.ber file]\n");
	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 800, 600, "so_long");
	vars.img.img = mlx_new_image(vars.mlx_ptr, 800, 600);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
									&vars.img.line_length, &vars.img.endian);
	load_bmps(&(vars.berbmp));
	vars.ber = read_ber(argv[1]);
	if (!vars.ber)
		exit(0);
	vars.ber->collected = 0;
	vars.ber->move = 0;
	if (!(vars.ber))
		return (-1);
	draw_all(&vars.img, &(vars.berbmp), vars.ber);
	mlx_put_image_to_window(vars.mlx_ptr, vars.mlx_win, vars.img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 0, parsing_key_press, &vars);
	mlx_hook(vars.mlx_win, 17, 0, leave, 0);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
