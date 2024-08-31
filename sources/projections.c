/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:41:54 by mdanish           #+#    #+#             */
/*   Updated: 2024/08/31 17:03:44 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

float	rotate(int is_x, int x, int y, t_fdf *fdf)
{
	float	result;
	int		z;

	z = *(*(fdf->map.map_numbers + y) + x) * fdf->consts.spacing;
	y *= fdf->consts.spacing;
	x *= fdf->consts.spacing;
	if (is_x)
		result = fdf->xy.x_const_x * x + fdf->xy.x_const_y * y + \
			fdf->xy.x_const_z * z + fdf->consts.x_offset;
	else
		result = fdf->xy.y_const_x * x + fdf->xy.y_const_y * y + \
			fdf->xy.y_const_z * z + fdf->consts.y_offset;
	return (result);
}

unsigned int	identify_colour(int is_x, int *xy, t_fdf *fdf)
{
	if (*(*(fdf->map.map_colors + *(xy + 1) - 1) + *xy - 1))
		return (*(*(fdf->map.map_colors + *(xy + 1) - 1) + *xy - 1));
	if (is_x && *(*(fdf->map.map_colors + *(xy + 1) - 1) + *xy))
		return (*(*(fdf->map.map_colors + *(xy + 1) - 1) + *xy));
	if (!is_x && *(*(fdf->map.map_colors + *(xy + 1)) + *xy - 1))
		return (*(*(fdf->map.map_colors + *(xy + 1)) + *xy - 1));
	if (*(*(fdf->map.map_numbers + *(xy + 1) - 1) + *xy - 1))
		return (*(fdf->xy.colours + fdf->xy.z_colour_index));
	if (is_x && *(*(fdf->map.map_numbers + *(xy + 1) - 1) + *xy))
		return (*(fdf->xy.colours + fdf->xy.z_colour_index));
	if (!is_x && *(*(fdf->map.map_numbers + *(xy + 1)) + *xy - 1))
		return (*(fdf->xy.colours + fdf->xy.z_colour_index));
	return (*(fdf->xy.colours + fdf->xy.no_z_colour_index));
}

void	draw_line(int *xy, t_fdf *fdf)
{
	fdf->xy.x_1 = rotate(1, *xy - 1, *(xy + 1) - 1, fdf);
	fdf->xy.y_1 = rotate(0, *xy - 1, *(xy + 1) - 1, fdf);
	if (*(xy + 1) != fdf->map.map_height)
	{
		fdf->xy.pixel_colour = identify_colour(0, xy, fdf);
		fdf->xy.x_2 = rotate(1, *xy - 1, *(xy + 1), fdf);
		fdf->xy.y_2 = rotate(0, *xy - 1, *(xy + 1), fdf);
		dda(fdf);
	}
	if (*xy != fdf->map.map_width)
	{
		fdf->xy.pixel_colour = identify_colour(1, xy, fdf);
		fdf->xy.x_2 = rotate(1, *xy, *(xy + 1) - 1, fdf);
		fdf->xy.y_2 = rotate(0, *xy, *(xy + 1) - 1, fdf);
		dda(fdf);
	}
}

void	build_image(t_fdf *fdf)
{
	int		xy[2];

	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->map.size_x,
			fdf->map.size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.bits_per_pixel, &fdf->mlx.size_line, &fdf->mlx.endian);
	*xy = 0;
	while (++*xy <= fdf->map.map_width)
	{
		*(xy + 1) = 0;
		while (++*(xy + 1) <= fdf->map.map_height)
			draw_line(xy, fdf);
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
	if (fdf->consts.help_flag % 2)
		print_menu(fdf);
	else if (fdf->consts.prank_flag % 2)
		mlx_string_put(fdf->mlx.mlx, fdf->mlx.window, 10, 50, 0xFFFFFF,
			"the Help Menu.\n");
	else
		mlx_string_put(fdf->mlx.mlx, fdf->mlx.window, 10, 50, 0xFFFFFF,
			"Press [ H ] to display the Help Menu.\n");
}

void	execute_projection(t_fdf *fdf, int projection_code)
{
	if (projection_code == PROJECTION1)
	{
		fdf->projection = ISOMETRIC_VIEW;
		calculate_constants(235, 0, -135, fdf);
	}
	else if (projection_code == PROJECTION2)
	{
		fdf->projection = FRONT_VIEW;
		calculate_constants(90, 0, 0, fdf);
	}
	else if (projection_code == PROJECTION3)
	{
		fdf->projection = SIDE_VIEW;
		calculate_constants(0, 90, 0, fdf);
	}
	else if (projection_code == PROJECTION4)
	{
		fdf->projection = TOP_VIEW;
		calculate_constants(0, 0, 0, fdf);
	}
	build_image(fdf);
}
