/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:46:42 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/28 14:22:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./minilibx_macos/mlx.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <stdio.h>

int		ft_parse_line(char *line)
{
	int	count;

	count = 0;
	if (!ft_isdigit(line[0]) || !ft_isdigit(line[ft_strlen(line) - 1]))
		return (0);
	while (line[count + 1])
	{
		if (!ft_isdigit(line[count]) && line[count] != ' ')
			return (0);
		count++;
	}
	return (1);
}

int		ft_check_file(char *name)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(name, O_RDONLY);
	get_next_line(fd, &line);
	line = ft_epur_str(line);
	len = ft_strlen(line);
	while (get_next_line(fd, &line))
	{
		line = ft_epur_str(line);
		if (((int)ft_strlen(line) != len) || (!ft_parse_line(line)))
		{
			close(fd);
			return (0);
		}
	}
	close(fd);
	return (1);
}

void	print_map(t_list *map, int len)
{
	t_list	*tmp;
	int		count;
	int		count2;

	tmp = NULL;
	tmp = map;
	while (tmp)
	{
		count = 0;
		count2 = 0;
		while (count2 < len)
		{
			printf("%d ", ((int *)(tmp->content))[count]);
			count++;
			count2++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_tab(t_point *tab, int len)
{
	int	count;

	count = 0;
	while (count < len)
	{
		printf("x = %d y = %d\n", tab[count].x, tab[count].y);
		count++;
	}
}

void	ft_trace(t_meta mlx, t_point src, t_point dst)
{
	int	dx;
	int	dy;
	int	x;
	int	y;

	dx = dst.x - src.x;
	dy = dst.y - src.y;
	x = src.x;
	while (x < dst.x)
	{
		y = src.y + dy * (x - src.x) / dy;
		mlx_pixel_put(mlx.ptr, mlx.win, x, y, 0x00FF00);
		x++;
	}
}

void	ft_display_tab(t_meta mlx, t_point *tab, int len, int offset)
{
	int		count;
	int		count_index;
	int		tmp;
	int		*tab_tmp;

	count = 1;
	count_index = 0;
	tmp = tab[count].y;
	if (!(tab_tmp = (int *)malloc(sizeof(int) * len)))
		tab_tmp = NULL;
	while (count_index < len)
	{
		tab_tmp[count_index] = tab[count_index].x;
		count_index++;
	}
	count_index = 0;
	while (count_index < len)
	{
		if (tab[count_index].y != tmp)
		{
			count = 1;
			tmp = tab[count_index].y;
		}
		/*
		mlx_pixel_put(mlx.ptr, mlx.win,
		(count * offset / 2 - tab[count_index].y * offset / 2) + 150,
		(count * offset / 2 + tab[count_index].y * offset / 2) + 150,
		//(0x00FF00 + tab[count_index].x * 100));
		0x00FF00);
		*/
		tab[count_index].x = (count * offset / 2 - tab[count_index].y *
			offset / 2) + 150;
		tab[count_index].y = (count * offset / 2 + tab[count_index].y *
			offset / 2) + 150 - tab_tmp[count_index];
		count++;
		count_index++;
	}
	print_tab(tab, len);
	count = 0;
	while (count + 1 < len)
	{
		ft_trace(mlx, tab[count], tab[count + 1]);
		count++;
	}
	/*
	count = 0;
	while (count + 11 < len)
	{
		ft_trace(mlx, tab[count], tab[count + 11]);
		count += 11;
	}
	*/
}

int		main(int argc, char *argv[])
{
	int		err;
	int		len;
	t_meta	mlx;
	t_point	*tab;

	err = 0;
	len = 0;
	tab = ft_init_tab(argv[1], &err, &len);
	//print_tab(tab, len);
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 800, 600, "FdF");
	ft_display_tab(mlx, tab, len, 30);
	mlx_loop(mlx.ptr);
	argc++;
	return (0);
}
