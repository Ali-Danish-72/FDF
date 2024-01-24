/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:41:54 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/24 16:58:45 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//		Send x and y as *i - 1 and *(i + 1) - 1 respectively.
//		theta -> -135, beta -> 0, alpha -> -235
int	cal_iso_rot(_Bool is_x, int x, int y, t_fdf *fdf)
{
	if (is_x)
		return (round((fdf->rot1 * (x * fdf->spacing)) + (fdf->rot2) * 
		(y * fdf->spacing) + (fdf->rot3) * *(*(fdf->map_numbers + y) + x)));
	return (round((fdf->rot4) * (x * fdf->spacing) + (fdf->rot5) * 
		(y * fdf->spacing) + (fdf->rot6) * *(*(fdf->map_numbers + y) + x)));
}

void	check_last_point_for_isometric_view(int *x, int *y, int *coords, t_fdf *fdf)
{
	*x = cal_iso_rot(1, *coords - 1, *(coords + 1) - 1, fdf) + fdf->x_offset;
	*y = cal_iso_rot(0, *coords - 1, *(coords + 1) - 1, fdf) + fdf->y_offset;
	if (*(coords + 1) != fdf->map_height)
	{
		if (*(*(fdf->map_colors + *(coords + 1) - 1) + *coords - 1))
			fdf->colour = *(*(fdf->map_colors + *(coords + 1) - 1) + *coords - 1);
		else if (*(*(fdf->map_colors + *(coords + 1)) + *coords - 1))
			fdf->colour = *(*(fdf->map_colors + *(coords + 1)) + *coords - 1);
		*(x + 1) = cal_iso_rot(1, *coords - 1, *(coords + 1), fdf) + fdf->x_offset;
		*(y + 1) = cal_iso_rot(0, *coords - 1, *(coords + 1), fdf) + fdf->y_offset;
		dda(x, y, fdf);
	}
	if (*coords != fdf->map_width)
	{
		if (*(*(fdf->map_colors + *(coords + 1) - 1) + *coords - 1))
			fdf->colour = *(*(fdf->map_colors + *(coords + 1) - 1) + *coords - 1);
		else if (*(*(fdf->map_colors + *(coords + 1) - 1) + *coords))
			fdf->colour = *(*(fdf->map_colors + *(coords + 1) - 1) + *coords);
		*(x + 1) = cal_iso_rot(1, *coords, *(coords + 1) - 1, fdf) + fdf->x_offset;
		*(y + 1) = cal_iso_rot(0, *coords, *(coords + 1) - 1, fdf) + fdf->y_offset;
		dda(x, y, fdf);
	}
}

void	isometric_view(t_fdf *fdf)
{
	int		x[2];
	int		y[2];
	int		coords[2];

	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	fdf->projs = ISO;
	calculate_offset(fdf);
	*coords = 0;
	while (++*coords <= fdf->map_width)
	{
		*(coords + 1) = 0;
		while (++*(coords + 1) <= fdf->map_height)
			check_last_point_for_isometric_view(x, y, coords, fdf);
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
}

void	front_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	fdf->projs = FR;
	calculate_offset(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
}

void	side_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	fdf->projs = SD;
	calculate_offset(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
}
