/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:04:23 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/30 02:11:18 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_count_elem(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != 0)
		count++;
	return (count);
}

int		*ft_create_tab(char **tmp)
{
	int		count;
	int		count2;
	int		*tab;

	count2 = 0;
	count = ft_count_elem(tmp);
	if (!(tab = (int *)malloc(sizeof(int) * count)))
		return (NULL);
	while (count2 < count)
	{
		tab[count2] = ft_atoi(tmp[count2]);
		count2++;
	}
	return (tab);
}

t_list	*ft_create_map(char *name, int *len, int *err)
{
	t_list	*map;
	int		fd;
	char	*line;

	map = NULL;
	fd = open(name, O_RDONLY);
	line = NULL;
	get_next_line(fd, &line);
	ft_lst_push_back(&map, ft_lstnew(ft_create_tab(
		ft_strsplit(ft_epur_str(line), ' ')),
		ft_count_elem(ft_strsplit(ft_epur_str(line), ' ')) * sizeof(int)));
	*len = ft_count_elem(ft_strsplit(ft_epur_str(line), ' '));
	while (get_next_line(fd, &line))
	{
		ft_lst_push_back(&map, ft_lstnew(ft_create_tab(
			ft_strsplit(ft_epur_str(line), ' ')),
			ft_count_elem(ft_strsplit(ft_epur_str(line), ' ')) * sizeof(int)));
	}
	if (!map || !line || len == 0)
		*err = -1;
	return (map);
}

t_point	*ft_init_tab(char *name, int *len, int *err)
{
	t_point	count;
	int		count_tab;
	t_list	*tmp;
	t_point	*tab;

	count_tab = 0;
	count.y = 0;
	tmp = ft_create_map(name, len, err);
	if (!(tab = (t_point *)malloc(sizeof(t_point) * *len * ft_lstsize(tmp))))
		tab = NULL;
	while (tmp)
	{
		count.x = -1;
		while (++count.x < *len)
		{
			tab[count_tab].x = count.x;
			tab[count_tab].y = count.y;
			tab[count_tab].offset = ((int *)(tmp->content))[count.x];
			count_tab++;
		}
		tmp = tmp->next;
		count.y++;
	}
	*len *= count.y;
	return (tab);
}
