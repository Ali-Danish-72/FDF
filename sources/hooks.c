/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:35:33 by mdanish           #+#    #+#             */
/*   Updated: 2024/09/24 01:44:57 by mdanish          ###   ########.fr       */
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

void	reset_projection(t_fdf *fdf)
{
	fdf->consts.spacing = 30;
	fdf->consts.translate_x = 0;
	fdf->consts.translate_y = 0;
	fdf->consts.rotation_x = 0;
	fdf->consts.rotation_y = 0;
	fdf->consts.rotation_z = 0;
	fdf->xy.z_colour_index = 3;
	fdf->xy.no_z_colour_index = 0;
	fdf->projection = ISOMETRIC_VIEW;
}

void	transformations(int key_code, t_fdf *fdf)
{
	if (key_code == ZOOM_IN)
		fdf->consts.spacing += ZOOM_CONSTANT;
	else if (key_code == ZOOM_OUT)
		fdf->consts.spacing -= ZOOM_CONSTANT;
	else if (key_code == TRANSLATE_LEFT)
		fdf->consts.translate_x -= TRANSLATION_CONSTANT;
	else if (key_code == TRANSLATE_RIGHT)
		fdf->consts.translate_x += TRANSLATION_CONSTANT;
	else if (key_code == TRANSLATE_DOWN)
		fdf->consts.translate_y += TRANSLATION_CONSTANT;
	else if (key_code == TRANSLATE_UP)
		fdf->consts.translate_y -= TRANSLATION_CONSTANT;
	else if (key_code == X_POSITIVE_ROTATE)
		fdf->consts.rotation_x += ROTATION_CONSTANT;
	else if (key_code == X_NEGATIVE_ROTATE)
		fdf->consts.rotation_x -= ROTATION_CONSTANT;
	else if (key_code == Y_POSITIVE_ROTATE)
		fdf->consts.rotation_y += ROTATION_CONSTANT;
	else if (key_code == Y_NEGATIVE_ROTATE)
		fdf->consts.rotation_y -= ROTATION_CONSTANT;
	else if (key_code == Z_POSITIVE_ROTATE)
		fdf->consts.rotation_z += ROTATION_CONSTANT;
	else if (key_code == Z_NEGATIVE_ROTATE)
		fdf->consts.rotation_z -= ROTATION_CONSTANT;
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
	else if (key_code == RESET)
		reset_projection(fdf);
	if (fdf->xy.z_colour_index == 7)
		fdf->xy.z_colour_index = 0;
	else if (fdf->xy.z_colour_index == -1)
		fdf->xy.z_colour_index = 6;
	else if (fdf->xy.no_z_colour_index == 7)
		fdf->xy.no_z_colour_index = 0;
	else if (fdf->xy.no_z_colour_index == -1)
		fdf->xy.no_z_colour_index = 6;
	return (transformations(key_code, fdf), switch_projection(key_code, fdf));
}

int	identify_mouse(int mouse_code, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mouse_code == 4)
		identify_key(ZOOM_IN, fdf);
	else if (mouse_code == 5)
		identify_key(ZOOM_OUT, fdf);
	return (0);
}
