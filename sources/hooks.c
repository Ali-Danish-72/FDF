/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:35:33 by mdanish           #+#    #+#             */
/*   Updated: 2024/08/30 15:01:04 by mdanish          ###   ########.fr       */
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
	if (key_code == ZOOM_IN)
		fdf->consts.spacing += 1;
	else if (key_code == ZOOM_OUT)
		fdf->consts.spacing -= 1;
	else if (key_code == TRANSLATE_LEFT)
		fdf->consts.translate_x -= 10;
	else if (key_code == TRANSLATE_RIGHT)
		fdf->consts.translate_x += 10;
	else if (key_code == TRANSLATE_DOWN)
		fdf->consts.translate_y += 10;
	else if (key_code == TRANSLATE_UP)
		fdf->consts.translate_y -= 10;
	else if (key_code == X_POSITIVE_ROTATE)
		fdf->consts.rotation_x += 5;
	else if (key_code == X_NEGATIVE_ROTATE)
		fdf->consts.rotation_x -= 5;
	else if (key_code == Y_POSITIVE_ROTATE)
		fdf->consts.rotation_y += 5;
	else if (key_code == Y_NEGATIVE_ROTATE)
		fdf->consts.rotation_y -= 5;
	else if (key_code == Z_POSITIVE_ROTATE)
		fdf->consts.rotation_z += 5;
	else if (key_code == Z_NEGATIVE_ROTATE)
		fdf->consts.rotation_z -= 5;
}

int	identify_key(int key_code, t_fdf *fdf)
{
	if (key_code == ESCAPE)
		destroy_window(fdf);
	else if (key_code == Z_COLOUR_FORWARD)
		fdf->xy.z_colour_index++;
	else if (key_code == Z_COLOUR_BACKWARD)
		fdf->xy.z_colour_index--;
	else if (key_code == NO_Z_COLOUR_FORWARD)
		fdf->xy.no_z_colour_index++;
	else if (key_code == NO_Z_COLOUR_BACKWARD)
		fdf->xy.no_z_colour_index--;
	else if (key_code == HELP_LOL)
		fdf->consts.prank_flag += 1;
	else if (key_code == MENU)
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
