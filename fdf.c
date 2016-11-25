/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:46:42 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/25 16:39:59 by                  ###   ########.fr       */
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



void	print_map(t_list *map)
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
		//while (((int *)(tmp->content))[count])
		while (count2 <= 10)
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
	printf("LEN = %d\n", len);
	while (count < len)
	{
		printf("x = %d y = %d\n", tab[count].x, tab[count].y);
		count++;
	}
}

int		main(int argc, char *argv[])
{
	int		err;
	int		len;
	t_point	*tab;
	void	*mlx;
	void	*window;

	err = 0;
	len = 0;
	tab = ft_init_tab(argv[1], &err, &len);
	print_tab(tab, len);
	/*
	if (argc != 2 || !ft_check_file(argv[1]))
	{
		ft_putendl("error");
		return (0);
	}
	*/
	mlx = mlx_init();
	window = mlx_new_window(mlx, 800, 600, "test");
	//mlx_loop(mlx);
	argc++;
	return (0);
}
