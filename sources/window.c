/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:40:42 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/30 21:34:45 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_pixel(t_fdf *fdf)
{
	char	*dst;

	if (!(fdf->xy.final_x > -1 && fdf->xy.final_x < fdf->map.size_x && 
		fdf->xy.final_y > -1 && fdf->xy.final_y < fdf->map.size_y))
		return ;
	dst = fdf->mlx.image_address + (int)fdf->xy.final_y * fdf->mlx.size_line + 
			(int)fdf->xy.final_x * (fdf->mlx.bits_per_pixel / 8);
	*(unsigned int *)dst = fdf->xy.pixel_colour;
}

void	dda(t_fdf *fdf)
{
	float	dx;
	float	dy;
	int		increments;

	dx = fdf->xy.x_2 - fdf->xy.x_1;
	dy = fdf->xy.y_2 - fdf->xy.y_1;
	if (fabs(dx) > fabs(dy))
		increments = fabs(dx);
	else
		increments = fabs(dy);
	dx = (dx / increments);
	dy = (dy / increments);
	fdf->xy.final_x = fdf->xy.x_1;
	fdf->xy.final_y = fdf->xy.y_1;
	while (increments--)
	{
		draw_pixel(fdf);
		fdf->xy.final_x += dx;
		fdf->xy.final_y += dy;
	}
}

void	calculate_constants(float alpha, float beta, float gamma, t_fdf *fdf)
{
	alpha = (alpha + fdf->consts.rotation_x) * M_PI / 180;
	beta = (beta + fdf->consts.rotation_y) * M_PI / 180;
	gamma = (gamma + fdf->consts.rotation_z) * M_PI / 180;
	fdf->xy.x_const_x = cos(beta) * cos(gamma);
	fdf->xy.x_const_y = sin(alpha) * sin(beta) * cos(gamma) - 
		cos(alpha) * sin(gamma);
	fdf->xy.x_const_z = cos(alpha) * sin(beta) * cos(alpha) + 
		sin(alpha) * sin(gamma);
	fdf->xy.y_const_x = cos(beta) * sin(gamma);
	fdf->xy.y_const_y = sin(alpha) * sin(beta) * sin(gamma) + 
		cos(alpha) * cos(gamma);
	fdf->xy.y_const_z = cos(alpha) * sin(beta) * sin(gamma) - 
		sin(alpha) * cos(gamma);
	fdf->consts.x_offset = (fdf->map.size_x / 2) + fdf->consts.translate_x - 
		(fdf->map.map_width * fdf->consts.spacing / 2);
	fdf->consts.y_offset = (fdf->map.size_y / 2) + fdf->consts.translate_y - 
		(fdf->map.map_height * fdf->consts.spacing / 2);
}

void	initialise_window(t_fdf fdf)
{
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.window = mlx_new_window(fdf.mlx.mlx, fdf.map.size_x, fdf.map.size_y,
			"FDF projection - Property of mdanish");
	mlx_mouse_hook(fdf.mlx.window, identify_mouse, &fdf);
	mlx_hook(fdf.mlx.window, 2, 0, identify_key, &fdf);
	mlx_hook(fdf.mlx.window, 17, 0, destroy_window, &fdf);
	execute_projection(&fdf, 18);
	mlx_loop(fdf.mlx.mlx);
}
