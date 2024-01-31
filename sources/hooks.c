/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:35:33 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/31 17:00:22 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	switch_projection(int key_code, t_fdf *fdf)
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
}

void	change_colour(int key_code, t_fdf *fdf)
{
	if (key_code == 38)
		fdf->xy.z_colour_index++;
	else if (key_code == 40)
		fdf->xy.z_colour_index--;
	if (fdf->xy.z_colour_index == 9)
		fdf->xy.z_colour_index = 0;
	else if (fdf->xy.z_colour_index == -1)
		fdf->xy.z_colour_index = 8;
	if (key_code == 45)
		fdf->xy.no_z_colour_index++;
	else if (key_code == 46)
		fdf->xy.no_z_colour_index--;
	if (fdf->xy.no_z_colour_index == 9)
		fdf->xy.no_z_colour_index = 0;
	else if (fdf->xy.no_z_colour_index == -1)
		fdf->xy.no_z_colour_index = 8;
}

void	transformations(int key_code, t_fdf *fdf)
{
	if (key_code == 13)
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
	else if (key_code == 24)
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
	change_colour(key_code, fdf);
}

int	identify_key(int key_code, t_fdf *fdf)
{
	if (key_code == 53)
		destroy_window(fdf);
	else
		transformations(key_code, fdf);
	if (key_code > 17 && key_code < 22)
		execute_projection(fdf, key_code);
	switch_projection(key_code, fdf);
	return (0);
}

int	identify_mouse(int mouse_code, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mouse_code == 4)
		fdf->consts.spacing += 1;
	else if (mouse_code == 5)
		fdf->consts.spacing -= 1;
	switch_projection(mouse_code, fdf);
	return (0);
}
