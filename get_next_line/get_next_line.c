/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 23:22:24 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/21 15:41:39 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_data	*ft_manage_fd(t_data **tmp, int fd)
{
	while (*tmp && (*tmp)->fd != fd)
		tmp = &(*tmp)->next;
	if (!*tmp)
	{
		*tmp = (t_data *)malloc(sizeof(**tmp));
		(*tmp)->fd = fd;
		(*tmp)->content = NULL;
		(*tmp)->next = NULL;
	}
	return (*tmp);
}

int		ft_parse_content(char **line, t_data *tmp)
{
	char	*temp;

	if (!tmp->content)
		return (0);
	if ((temp = ft_strchr(tmp->content, '\n')))
	{
		*line = ft_strjoin(*line, ft_strsub(tmp->content, 0, temp -
			tmp->content));
		tmp->content = ft_strdup(tmp->content + (temp - tmp->content) + 1);
		return (1);
	}
	else
	{
		*line = ft_strjoin(*line, tmp->content);
		ft_strdel(&(tmp->content));
	}
	return (0);
}

int		ft_read(char **line, t_data *current)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(current->fd, buffer, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		if ((tmp = ft_strchr(buffer, '\n')))
		{
			*line = ft_strjoin(*line, ft_strsub(buffer, 0, tmp - buffer));
			current->content = ft_strdup(buffer + (tmp - buffer) + 1);
			return (1);
		}
		else
			*line = ft_strjoin(*line, buffer);
	}
	if (ret == 0 && **line == '\0')
		return (0);
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	static t_data	*tmp = NULL;
	t_data			*current;
	char			test;

	if (!line || fd < 0 || read(fd, &test, 0) != 0)
		return (-1);
	if (*line)
		*line = NULL;
	*line = ft_strdup("");
	current = ft_manage_fd(&tmp, fd);
	if (ft_parse_content(line, current))
		return (1);
	return (ft_read(line, current));
}
