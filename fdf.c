/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:46:42 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/30 15:58:06 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_trace(t_wrapper wrapper, t_point src, t_point dst)
{
	t_point	tab[2];
	int		err;
	int		e2;

	tab[0].x = abs(dst.x - src.x);
	tab[0].y = abs(dst.y - src.y);
	tab[1].x = src.x < dst.x ? 1 : -1;
	tab[1].y = src.y < dst.y ? 1 : -1;
	err = (tab[0].x > tab[0].y ? tab[0].x : -tab[0].y) / 2;
	while (1)
	{
		mlx_pixel_put(wrapper.mlx.ptr, wrapper.mlx.win, src.x, src.y,
			src.offset * 15 + 0x007777);
		if (src.x == dst.x && src.y == dst.y)
			break ;
		e2 = err;
		if (e2 > -tab[0].x)
			err -= tab[0].y;
		if (e2 > -tab[0].x)
			src.x += tab[1].x;
		if (e2 < tab[0].y)
			err += tab[0].x;
		if (e2 < tab[0].y)
			src.y += tab[1].y;
	}
}

t_point	*ft_copy_tab(t_point *tab, int len)
{
	int		count;
	t_point	*tab_new;

	count = 0;
	if (!(tab_new = (t_point *)malloc(sizeof(t_point) * len)))
		return (NULL);
	while (count < len)
	{
		tab_new[count] = tab[count];
		count++;
	}
	return (tab_new);
}

t_point	*ft_iso(t_wrapper wrapper)
{
	int		count_index;
	int		tmp;
	t_point	*tab;

	count_index = 0;
	if (!(tab = (t_point *)malloc(sizeof(t_point) * wrapper.len)))
		tab = NULL;
	tab = ft_copy_tab(wrapper.tab, wrapper.len);
	while (count_index < wrapper.len)
	{
		tmp = tab[count_index].x;
		tab[count_index].x = ((tmp * wrapper.tile_size / 2 -
			tab[count_index].y * wrapper.tile_size / 2) + 150 +
			wrapper.mlx.offset_x) * wrapper.mlx.zoom;
		tab[count_index].y = ((tmp * wrapper.tile_size / 2 +
			tab[count_index].y * wrapper.tile_size / 2) + 150 -
			(tab[count_index].offset * 5) + wrapper.mlx.offset_y) *
			wrapper.mlx.zoom;
		count_index++;
	}
	return (tab);
}

void	ft_display_tab(t_wrapper wrapper)
{
	int		count;
	t_point	*tab;

	count = 0;
	tab = ft_iso(wrapper);
	while (count + 1 < wrapper.len)
	{
		if (!(count % wrapper.line_size == wrapper.line_size - 1) || count == 0)
			ft_trace(wrapper, tab[count], tab[count + 1]);
		count++;
	}
	count = 0;
	while (count + wrapper.line_size < wrapper.len)
	{
		ft_trace(wrapper, tab[count], tab[count + wrapper.line_size]);
		count++;
	}
}

int		main(int argc, char *argv[])
{
	int			err;
	t_wrapper	wrapper;

	err = 0;
	if (argc != 2)
	{
		ft_putendl("error");
		return (-1);
	}
	ft_init_struct(&wrapper, 10, argv[1], &err);
	if (err == -1)
	{
		ft_putendl("error");
		return (-1);
	}
	ft_display_tab(wrapper);
	mlx_key_hook(wrapper.mlx.win, &ft_offset, &wrapper);
	mlx_loop(wrapper.mlx.ptr);
	return (0);
}
