/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:35:33 by mdanish           #+#    #+#             */
/*   Updated: 2024/08/29 22:12:43 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	switch_projection(int key_code, t_fdf *fdf)
{
	if (key_code >= PROJECTION1 && key_code <= PROJECTION4)
		execute_projection(fdf, key_code);
	else if (!fdf->projection)
		execute_projection(fdf, PROJECTION1);
	else if (fdf->projection == 1)
		execute_projection(fdf, PROJECTION2);
	else if (fdf->projection == 2)
		execute_projection(fdf, PROJECTION3);
	else if (fdf->projection == 3)
		execute_projection(fdf, PROJECTION4);
	return (0);
}

void	transformations(int key_code, t_fdf *fdf)
{
	if (key_code == PLUS)
		fdf->consts.spacing += 1;
	else if (key_code == MINUS)
		fdf->consts.spacing -= 1;
	else if (key_code == LEFT)
		fdf->consts.translate_x -= 10;
	else if (key_code == RIGHT)
		fdf->consts.translate_x += 10;
	else if (key_code == DOWN)
		fdf->consts.translate_y += 10;
	else if (key_code == UP)
		fdf->consts.translate_y -= 10;
	else if (key_code == W)
		fdf->consts.rotation_x += 5;
	else if (key_code == Q)
		fdf->consts.rotation_x -= 5;
	else if (key_code == S)
		fdf->consts.rotation_y += 5;
	else if (key_code == A)
		fdf->consts.rotation_y -= 5;
	else if (key_code == X)
		fdf->consts.rotation_z += 5;
	else if (key_code == Z)
		fdf->consts.rotation_z -= 5;
}

int	identify_key(int key_code, t_fdf *fdf)
{
	if (key_code == ESC)
		destroy_window(fdf);
	else if (key_code == O)
		fdf->xy.z_colour_index++;
	else if (key_code == I)
		fdf->xy.z_colour_index--;
	else if (key_code == L)
		fdf->xy.no_z_colour_index++;
	else if (key_code == K)
		fdf->xy.no_z_colour_index--;
	else if (key_code == H)
		fdf->consts.prank_flag += 1;
	else if (key_code == M)
		fdf->consts.help_flag += 1;
	else
		transformations(key_code, fdf);
	if (fdf->xy.z_colour_index == 7)
		fdf->xy.z_colour_index = 0;
	if (fdf->xy.z_colour_index == -1)
		fdf->xy.z_colour_index = 6;
	if (fdf->xy.no_z_colour_index == 7)
		fdf->xy.no_z_colour_index = 0;
	if (fdf->xy.no_z_colour_index == -1)
		fdf->xy.no_z_colour_index = 6;
	return (switch_projection(key_code, fdf));
}

int	identify_mouse(int mouse_code, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mouse_code == 4)
		identify_key(24, fdf);
	else if (mouse_code == 5)
		identify_key(27, fdf);
	return (0);
}
