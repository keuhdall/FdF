/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:46:42 by lmarques          #+#    #+#             */
/*   Updated: 2016/11/22 18:32:36 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx_macos/mlx.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"

int	main(int argc, char *argv[])
{
	int		fd;
	void	*mlx;
	void	*window;

	fd = open(argv[1], O_RDONLY);
	mlx = mlx_init();
	window = mlx_new_window(mlx, 800, 600, "test");
}
