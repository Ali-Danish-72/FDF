/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:35:33 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/24 16:47:15 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	rotation_keys(int key_code, t_fdf *fdf)
{
	(void)fdf;
	if (key_code == 13)
		printf("Rotate the x-axis positively\n");		/*Rotate the x-axis positively*/
	else if (key_code == 12)
		printf("Rotate the x-axis negatively\n");		/*Rotate the x-axis negatively*/
	else if (key_code == 1)
		printf("Rotate the y-axis positively\n");		/*Rotate the y-axis positively*/
	else if (key_code == 0)
		printf("Rotate the y-axis negatively\n");		/*Rotate the y-axis negatively*/
	else if (key_code == 7)
		printf("Rotate the z-axis positively\n");		/*Rotate the z-axis positively*/
	else if (key_code == 6)
		printf("Rotate the z-axis negatively\n");		/*Rotate the z-axis negatively*/
}

int	identify_key(int key_code, t_fdf *fdf)
{
	if (key_code == 53)
		destroy_window(fdf);							/*Destroy window and exit*/
	else if (key_code == 24)
		zoom_in(fdf);									/*Zoom in*/
	else if (key_code == 27)
		zoom_out(fdf);									/*Zoom out*/
	else if (key_code == 18)
		isometric_view(fdf);							/*Projection 1*/
	else if (key_code == 19)
		front_view(fdf);								/*Projection 2*/
	else if (key_code == 20)
		side_view(fdf);									/*Projection 3*/
	else if (key_code == 21)
		top_view(fdf);									/*Projection 4*/
	else if (key_code == 123)
		translate_x(key_code, fdf);						/*Translate left*/
	else if (key_code == 124)
		translate_x(key_code, fdf);						/*Translate right*/
	else if (key_code == 125)
		translate_y(key_code, fdf);						/*Translate up*/
	else if (key_code == 126)
		translate_y(key_code, fdf);						/*Translate down*/
	else
		rotation_keys(key_code, fdf);
	return (0);
}

int	identify_mouse(int mouse_code, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mouse_code == 4)
		zoom_in(fdf);									/*Zoom in*/
	else if (mouse_code == 5)
		zoom_out(fdf);									/*Zoom out*/
	return (0);
}
