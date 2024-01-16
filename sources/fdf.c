/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:25:50 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/16 19:19:51 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	print_error_message(int status)
{
	if (status == 1)
		ft_printf(2, "Use this format:\n./fdf <map_path.fdf>.\n");
	else if (status == 2)
		ft_printf(2, "Invalid file type detected.\n");
	else if (status == 3)
		ft_printf(2, "Error encountered while opening the map.\n");
	else if (status == 4)
		ft_printf(2, "%s\nMalloc during map read failed.", strerror(errno));
	else if (status == 5)
		ft_printf(2, "%s\nMalloc during map join failed.", strerror(errno));
	else if (status == 6)
		ft_printf(2, "%s\nMalloc during map split failed.", strerror(errno));
	else if (status == 7)
		ft_printf(2, "%s\nMalloc during value split failed.", strerror(errno));
	else if (status == 8)
		ft_printf(2, "%s\nMalloc during color split failed.", strerror(errno));
	return (status);
}

void	call_exit(int status, t_fdf fdf)
{
	free_split((void **)fdf.parsed_map, fdf.map_height);
	free_split((void **)fdf.map_colors, fdf.map_height);
	free_split((void **)fdf.map_numbers, fdf.map_height);
	free(fdf.single_line);
	close(fdf.map_fd);
	exit(print_error_message(status));
}

int	destroy_window(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.window);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.window);
	call_exit(0, *fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (print_error_message(1));
	if (ft_strncmp((*(argv + 1) + (ft_strlen(*(argv + 1)) - 4)), ".fdf", 4))
		return (print_error_message(2));
	if (parse(&fdf, *(argv + 1)))
		return (print_error_message(3));
	initialise_window(fdf);
}
