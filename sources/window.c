/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:40:42 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/18 18:48:08 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_pixel(int colour, t_fdf *fdf)
{
	unsigned int	*dst;

	dst = (unsigned int *)(fdf->mlx.image_address + 
			(fdf->y * fdf->mlx.size_line + fdf->x * (fdf->mlx.pixel_bit / 8)));
	if (colour)
		*dst = colour;
	else
		*dst = 0xFFFFFF;
}

void	dda(int *x, int *y, int colour, t_fdf *fdf)
{
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
		if (fdf->x > -1 && fdf->x < fdf->size_x && 
			fdf->y > -1 && fdf->y < fdf->size_y)
			draw_pixel(colour, fdf);
		fdf->x += dx;
		fdf->y += dy;
	}
}

void	initialise_window(t_fdf fdf)
{
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.window = mlx_new_window(fdf.mlx.mlx, fdf.size_x, fdf.size_y,
			"mdanish's FDF projection");
	mlx_mouse_hook(fdf.mlx.window, identify_mouse, &fdf);
	mlx_hook(fdf.mlx.window, 2, 0, identify_key, &fdf);
	mlx_hook(fdf.mlx.window, 17, 0, destroy_window, &fdf);
	// isometric_view(&fdf);
	top_view(&fdf);
	mlx_loop(fdf.mlx.mlx);
}
