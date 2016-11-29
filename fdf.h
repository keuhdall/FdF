/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/29 20:15:36 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

typedef struct	s_meta
{
	void		*ptr;
	void		*win;
	int			zoom;
	int			offset_x;
	int			offset_y;
}				t_meta;

typedef struct	s_point
{
	int			x;
	int			y;
	int			offset;
}				t_point;

typedef struct	s_wrapper
{
	int			len;
	int			line_size;
	int			tile_size;
	t_meta		mlx;
	t_point		*tab;
}				t_wrapper;

void			ft_display_tab(t_wrapper wrapper);
void			ft_init_struct(t_wrapper *wrapper, int tile_size, char *name,
					int *err);
int				ft_offset(int keycode, t_wrapper *wrapper);
t_point			*ft_init_tab(char *name, int *err, int *len);

#endif
