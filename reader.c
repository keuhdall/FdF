/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:04:23 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/25 01:31:10 by                  ###   ########.fr       */
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

t_list	*ft_create_map(char *name, int *err)
{
	t_list	*map;
	int		fd;
	char	*line;

	map = NULL;
	fd = open(name, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line))
		ft_lst_push_back(&map, ft_lstnew(ft_create_tab(
			ft_strsplit(ft_epur_str(line), ' ')),
			ft_count_elem(ft_strsplit(ft_epur_str(line), ' ')) * sizeof(int)));
	*err = 0; //TO CHANGE
	return (map);
}
