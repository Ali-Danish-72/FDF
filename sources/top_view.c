/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_view.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:31:16 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/21 22:45:46 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	check_last_point_for_top_view(int *x, int *y, int *i, t_fdf *fdf)
{
	if (*(i + 1) != fdf->map_height)
	{
		if (*(*(fdf->map_colors + *(i + 1) - 1) + *i - 1))
			fdf->colour = *(*(fdf->map_colors + *(i + 1) - 1) + *i - 1);
		else if (*(*(fdf->map_colors + *(i + 1)) + *i - 1))
			fdf->colour = *(*(fdf->map_colors + *(i + 1)) + *i - 1);
		*(x + 1) = (*i - 1) * fdf->spacing + fdf->x_offset;
		*(y + 1) = *(i + 1) * fdf->spacing + fdf->y_offset;
		dda(x, y, fdf);
	}
	if (*i != fdf->map_width)
	{
		if (*(*(fdf->map_colors + *(i + 1) - 1) + *i - 1))
			fdf->colour = *(*(fdf->map_colors + *(i + 1) - 1) + *i - 1);
		else if (*(*(fdf->map_colors + *(i + 1) - 1) + *i))
			fdf->colour = *(*(fdf->map_colors + *(i + 1) - 1) + *i);
		*(x + 1) = *i * fdf->spacing + fdf->x_offset;
		*(y + 1) = (*(i + 1) - 1) * fdf->spacing + fdf->y_offset;
		dda(x, y, fdf);
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
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
		fdf->mlx.image, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
	fdf->projs = TP;
}
