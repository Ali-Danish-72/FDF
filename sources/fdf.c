/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:25:50 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/13 21:02:29 by mdanish          ###   ########.fr       */
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
	// else if (status == 9)
	// 	ft_printf(2, "%s. Trimming the qoutations failed.\n", strerror(errno));
	// else if (status == 11)
	// 	ft_printf(2, "%s. Search for the command failed.\n", strerror(errno));
	// else if (status == 12)
	// 	ft_printf(2, "Open quotes detected in the command or its arguments\n");
	// else if (status == 13)
	// 	ft_printf(2, "Use this:\n./pipex here_doc LIMITER cmd cmd1 file\n");

int	call_exit(int status, t_fdf fdf)
{
	free_split((void **)fdf.parsed_map, fdf.map_height);
	free_split((void **)fdf.map_colors, fdf.map_height);
	free_split((void **)fdf.map_numbers, fdf.map_height);
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

int	identify_key(int key_code, t_fdf *fdf)
{
	if (key_code == 53)
		destroy_window(fdf);
	return (0);
}

void	initialise_window(t_fdf fdf)
{
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.window = mlx_new_window(fdf.mlx.mlx, fdf.size_x, fdf.size_y,
			"mdanish's FDF projection");
	mlx_key_hook(fdf.mlx.window, identify_key, &fdf);
	mlx_hook(fdf.mlx.window, 17, 0, destroy_window, &fdf);
	fdf.mlx.image = mlx_new_image(fdf.mlx.mlx, fdf.size_x, fdf.size_y);
	fdf.mlx.image_address = mlx_get_data_addr(fdf.mlx.image,
			&fdf.mlx.bits_per_pixel, &fdf.mlx.size_line, &fdf.mlx.endian);
	mlx_put_image_to_window(fdf.mlx.mlx, fdf.mlx.window,
		fdf.mlx.image, 0, 0);
	mlx_loop(fdf.mlx.mlx);
}

// int x = 700;
// int y = 500;
// while (x < 901)
// {
// 	char *var = fdf.mlx.image_address + 
// 		(500 * fdf.mlx.size_line + x * (fdf.mlx.bits_per_pixel / 8));
// 	*((unsigned int *)var) = 0xFFFFFF;
// 	var = fdf.mlx.image_address + 
// 		(700 * fdf.mlx.size_line + x++ * (fdf.mlx.bits_per_pixel / 8));
// 	*((unsigned int *)var) = 0xFFFFFF;
// 	var = fdf.mlx.image_address + 
// 		(y * fdf.mlx.size_line + 700 * (fdf.mlx.bits_per_pixel / 8));
// 	*((unsigned int *)var) = 0xFFFFFF;
// 	var = fdf.mlx.image_address + 
// 		(y++ * fdf.mlx.size_line + 900 * (fdf.mlx.bits_per_pixel / 8));
// 	*((unsigned int *)var) = 0xFFFFFF;
// }

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
