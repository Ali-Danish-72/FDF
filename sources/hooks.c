/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:35:33 by mdanish           #+#    #+#             */
/*   Updated: 2024/02/01 20:49:35 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	switch_projection(int key_code, t_fdf *fdf)
{
	if (key_code > 17 && key_code < 22)
		execute_projection(fdf, key_code);
	else if (!fdf->projection)
		execute_projection(fdf, 18);
	else if (fdf->projection == 1)
		execute_projection(fdf, 19);
	else if (fdf->projection == 2)
		execute_projection(fdf, 20);
	else if (fdf->projection == 3)
		execute_projection(fdf, 21);
	return (0);
}

void	transformations(int key_code, t_fdf *fdf)
{
	if (key_code == 24)
		fdf->consts.spacing += 1;
	else if (key_code == 27)
		fdf->consts.spacing -= 1;
	else if (key_code == 123)
		fdf->consts.translate_x -= 10;
	else if (key_code == 124)
		fdf->consts.translate_x += 10;
	else if (key_code == 125)
		fdf->consts.translate_y += 10;
	else if (key_code == 126)
		fdf->consts.translate_y -= 10;
	else if (key_code == 13)
		fdf->consts.rotation_x += 5;
	else if (key_code == 12)
		fdf->consts.rotation_x -= 5;
	else if (key_code == 1)
		fdf->consts.rotation_y += 5;
	else if (key_code == 0)
		fdf->consts.rotation_y -= 5;
	else if (key_code == 7)
		fdf->consts.rotation_z += 5;
	else if (key_code == 6)
		fdf->consts.rotation_z -= 5;
}

int	identify_key(int key_code, t_fdf *fdf)
{
	if (key_code == 53)
		destroy_window(fdf);
	else if (key_code == 31)
		fdf->xy.z_colour_index++;
	else if (key_code == 34)
		fdf->xy.z_colour_index--;
	else if (key_code == 37)
		fdf->xy.no_z_colour_index++;
	else if (key_code == 40)
		fdf->xy.no_z_colour_index--;
	else if (key_code == 4)
		fdf->consts.prank_flag += 1;
	else if (key_code == 46)
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
