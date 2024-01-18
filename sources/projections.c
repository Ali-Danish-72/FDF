/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:41:54 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/18 19:49:21 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	calculate_offset(t_fdf *fdf)
{
	fdf->x_offset = (fdf->size_x / 2) - ((fdf->map_width / 2) * fdf->spacing)
		+ fdf->translate_x;
	fdf->y_offset = (fdf->size_y / 2) - ((fdf->map_height / 2) * fdf->spacing)
		+ fdf->translate_y;
}

void	check_last_point_for_top_view(int *x, int *y, int *i, t_fdf *fdf)
{
	int	colour;

	colour = 0;
	if (*(i + 1) != fdf->map_height)
	{
		if (*(*(fdf->map_colors + *(i + 1) - 1) + *i - 1))
			colour = *(*(fdf->map_colors + *(i + 1) - 1) + *i - 1);
		else if (*(*(fdf->map_colors + *(i + 1)) + *i - 1))
			colour = *(*(fdf->map_colors + *(i + 1)) + *i - 1);
		*(x + 1) = (*i - 1) * fdf->spacing + fdf->x_offset;
		*(y + 1) = *(i + 1) * fdf->spacing + fdf->y_offset;
		dda(x, y, colour, fdf);
	}
	colour = 0;
	if (*i != fdf->map_width)
	{
		if (*(*(fdf->map_colors + *(i + 1) - 1) + *i - 1))
			colour = *(*(fdf->map_colors + *(i + 1) - 1) + *i - 1);
		else if (*(*(fdf->map_colors + *(i + 1) - 1) + *i))
			colour = *(*(fdf->map_colors + *(i + 1) - 1) + *i);
		*(x + 1) = *i * fdf->spacing + fdf->x_offset;
		*(y + 1) = (*(i + 1) - 1) * fdf->spacing + fdf->y_offset;
		dda(x, y, colour, fdf);
	}
}

void	top_view(t_fdf *fdf)
{
	int		x[2];
	int		y[2];
	int		i[2];

	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	calculate_offset(fdf);
	*i = 0;
	while (++*i <= fdf->map_width)
	{
		*(i + 1) = 0;
		while (++*(i + 1) <= fdf->map_height)
		{
			*x = (*i - 1) * fdf->spacing + fdf->x_offset;
			*y = (*(i + 1) - 1) * fdf->spacing + fdf->y_offset;
			check_last_point_for_top_view(x, y, i, fdf);
		}
	}
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.window);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
	fdf->projs = TP;
}

void	front_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	calculate_offset(fdf);
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.window);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
	fdf->projs = FR;
}

void	isometric_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	calculate_offset(fdf);
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.window);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
	fdf->projs = ISO;
}

void	side_view(t_fdf *fdf)
{
	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
	calculate_offset(fdf);
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.window);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image_address);
	fdf->projs = SD;
}
