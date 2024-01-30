/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:25:50 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/30 21:07:39 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	call_exit(int status, t_fdf *fdf)
{
	if (status == 1)
		ft_printf(2, "Use this format:\n./fdf <map_path.fdf>.\n");
	else if (status == 2)
		ft_printf(2, "Invalid file type detected.\n");
	else if (status == 3)
		ft_printf(2, "Error encountered while opening the map.\n");
	else if (status == 4)
		ft_printf(2, "Malloc while reading the map failed.");
	else if (status == 5)
		ft_printf(2, "Malloc while joining the map failed.");
	else if (status == 6)
		ft_printf(2, "Malloc while splitting up the map failed.");
	else if (status == 7)
		ft_printf(2, "Malloc while creating the value map failed.");
	else if (status == 8)
		ft_printf(2, "Malloc while creating the color map failed.");
	if (status > 3)
	{
		free_split((void **)fdf->map.parsed_map, fdf->map.map_height);
		free_split((void **)fdf->map.map_colors, fdf->map.map_height);
		free_split((void **)fdf->map.map_numbers, fdf->map.map_height);
		free(fdf->map.single_line);
		close(fdf->map.map_fd);
	}
	exit(status);
}

int	destroy_window(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.window);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.window);
	call_exit(0, fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		call_exit(1, NULL);
	if (ft_strncmp((*(argv + 1) + (ft_strlen(*(argv + 1)) - 4)), ".fdf", 4))
		call_exit(2, NULL);
	parse(&fdf, *(argv + 1));
	initialise_window(fdf);
}
