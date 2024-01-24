/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:40:42 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/24 16:59:45 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_pixel(t_fdf *fdf)
{
	unsigned int	*dst;

	dst = (unsigned int *)(fdf->mlx.image_address + fdf->final_y * 
			fdf->mlx.size_line + fdf->final_x * (fdf->mlx.pixel_bit / 8));
	if (fdf->colour)
		*dst = fdf->colour;
	else
		*dst = 0xFFFFFF;
}

void	dda(int *x, int *y, t_fdf *fdf)
{
	float	dx;
	float	dy;
	int		increments;

	dx = *(x + 1) - *x;
	dy = *(y + 1) - *y;
	if (dx > dy)
		increments = fabs(dx);
	else
		increments = fabs(dy);
	if (increments)
		dx = round(dx / increments);
	if (increments)
		dy = round(dy / increments);
	fdf->final_x = *x;
	fdf->final_y = *y;
	while (increments--)
	{
		if (fdf->final_x > -1 && fdf->final_x < fdf->size_x && 
			fdf->final_y > -1 && fdf->final_y < fdf->size_y)
			draw_pixel(fdf);
		fdf->final_x += dx;
		fdf->final_y += dy;
	}
	fdf->colour = 0;
}

void	calculate_offset(t_fdf *fdf)
{
	fdf->x_offset = (fdf->size_x / 2) - (fdf->map_width * fdf->spacing / 2)
		+ fdf->translate_x;
	fdf->y_offset = (fdf->size_y / 2) - (fdf->map_height * fdf->spacing / 2)
		+ fdf->translate_y;
}

void	initialise_window(t_fdf fdf)
{
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.window = mlx_new_window(fdf.mlx.mlx, fdf.size_x, fdf.size_y,
			"mdanish's FDF projection");
	mlx_mouse_hook(fdf.mlx.window, identify_mouse, &fdf);
	mlx_hook(fdf.mlx.window, 2, 0, identify_key, &fdf);
	mlx_hook(fdf.mlx.window, 17, 0, destroy_window, &fdf);
	isometric_view(&fdf);
	mlx_loop(fdf.mlx.mlx);
}
