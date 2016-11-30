/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:02:57 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/30 12:32:59 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_len(t_point *tab)
{
	int		count;

	count = 0;
	while (tab[count].y == 0)
		count++;
	return (count);
}

void	ft_init_struct(t_wrapper *wrapper, int tile_size, char *name, int *err)
{
	wrapper->len = 0;
	wrapper->tab = ft_init_tab(name, &(wrapper->len), err);
	if (*err == -1)
		return ;
	wrapper->mlx.ptr = mlx_init();
	wrapper->mlx.win = mlx_new_window(wrapper->mlx.ptr, 1920, 1080, "FdF");
	wrapper->mlx.zoom = 1;
	wrapper->mlx.offset_x = 0;
	wrapper->mlx.offset_y = 0;
	wrapper->tile_size = tile_size;
	wrapper->line_size = ft_get_len(wrapper->tab);
}

t_point	*ft_change_offset(t_wrapper wrapper, char sign)
{
	int	count;

	count = 0;
	while (count < wrapper.len)
	{
		if (wrapper.tab[count].offset != 0)
		{
			if (wrapper.tab[count].offset == 1 && sign == '-')
				wrapper.tab[count].offset -= 2;
			else if (wrapper.tab[count].offset == -1 && sign == '+')
				wrapper.tab[count].offset += 2;
			else if (sign == '-')
				wrapper.tab[count].offset--;
			else if (sign == '+')
				wrapper.tab[count].offset++;
		}
		count++;
	}
	return (wrapper.tab);
}

int		ft_offset(int keycode, t_wrapper *wrapper)
{
	mlx_clear_window(wrapper->mlx.ptr, wrapper->mlx.win);
	if (keycode == 123)
		wrapper->mlx.offset_x -= 5;
	if (keycode == 124)
		wrapper->mlx.offset_x += 5;
	if (keycode == 126)
		wrapper->mlx.offset_y -= 5;
	if (keycode == 125)
		wrapper->mlx.offset_y += 5;
	if (keycode == 69)
		wrapper->mlx.zoom++;
	if (keycode == 78)
		wrapper->mlx.zoom <= 1 ? wrapper->mlx.zoom = 1 : wrapper->mlx.zoom--;
	if (keycode == 27)
		wrapper->tab = ft_change_offset(*wrapper, '-');
	if (keycode == 24)
		wrapper->tab = ft_change_offset(*wrapper, '+');
	if (keycode == 53)
		exit(1);
	ft_display_tab(*wrapper);
	return (0);
}
