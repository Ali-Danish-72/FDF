/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:40:42 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/16 20:49:55 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_pixel(int *i, t_fdf *fdf)
{
	// if (*i < fdf->map_width - 1 && *(i + 1) < fdf->map_height - 1)
	// {
	// 	if (*(*(fdf->map_colors + *(i + 1)) + *i))
	// 		mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.window, fdf->x, fdf->y,
	// 			*(*(fdf->map_colors + *(i + 1)) + *i));
	// 	else if (*(*(fdf->map_colors + *(i + 1) + 1) + (*i + 1)))
	// 			mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.window, fdf->x, fdf->y,
	// 				*(*(fdf->map_colors + *(i + 1) + 1) + (*i + 1)));
	// 	else
	// 		mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.window, fdf->x, fdf->y, 0xFFFFFF);
	// }
	(void)i;
	char *dst = fdf->mlx.image_address + (fdf->y * fdf->mlx.size_line + fdf->x * (fdf->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = 0xFFFFFF;
}

void	dda(int *x, int *y, int *i, t_fdf *fdf)
{
	// char	*var;
	float	dx;
	float	dy;
	int		increments;

	dx = *(x + 1) - *x;
	dy = *(y + 1) - *y;
	if (dx > dy)
		increments = dx;
	else
		increments = dy;
	dx /= increments;
	dy /= increments;
	fdf->x = *x;
	fdf->y = *y;
	while (increments--)
	{
		draw_pixel(i, fdf);
		fdf->x += dx;
		fdf->y += dy;
	}
}

void	check_last_point_for_top_view(int *x, int *y, int *i, t_fdf *fdf)
{
	int	gap;

	gap = fdf->sp;
	if (*(i + 1) != fdf->map_height)
	{
		*(x + 1) = *i * gap + (800 - (fdf->map_width / 2) * gap);
		*(y + 1) = (*(i + 1) + 1) * gap + (600 - (fdf->map_height / 2) * gap);
		dda(x, y, i, fdf);
	}
	if (*i != fdf->map_width)
	{
		*(x + 1) = (*i + 1) * gap + (800 - (fdf->map_width / 2) * gap);
		*(y + 1) = *(i + 1) * gap + (600 - (fdf->map_height / 2) * gap);
		dda(x, y, i, fdf);
	}
}

void	top_view(t_fdf *fdf)
{
	int		x[2];
	int		y[2];
	int		i[2];

	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.bits_per_pixel, &fdf->mlx.size_line, &fdf->mlx.endian);
	*i = 0;
	while (++*i <= fdf->map_width)
	{
		*(i + 1) = 0;
		while (++*(i + 1) <= fdf->map_height)
		{
			*x = *i * fdf->sp + (800 - (fdf->map_width / 2) * fdf->sp);
			*y = *(i + 1) * fdf->sp + (600 - (fdf->map_height / 2) * fdf->sp);
			check_last_point_for_top_view(x, y, i, fdf);
		}
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
}

void	front_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.bits_per_pixel, &fdf->mlx.size_line, &fdf->mlx.endian);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
}

void	isometric_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.bits_per_pixel, &fdf->mlx.size_line, &fdf->mlx.endian);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
}

void	side_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.bits_per_pixel, &fdf->mlx.size_line, &fdf->mlx.endian);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
}

void	initialise_window(t_fdf fdf)
{
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.window = mlx_new_window(fdf.mlx.mlx, fdf.size_x, fdf.size_y,
			"mdanish's FDF projection");
	mlx_mouse_hook(fdf.mlx.window, identify_mouse, &fdf);
	mlx_key_hook(fdf.mlx.window, identify_key, &fdf);
	mlx_hook(fdf.mlx.window, 17, 0, destroy_window, &fdf);
	isometric_view(&fdf);
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
