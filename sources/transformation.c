/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:33:04 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/18 16:22:18 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	zoom_in(t_fdf *fdf)
{
	fdf->spacing += 1;
	if (!fdf->projs)
		isometric_view(fdf);
	else if (fdf->projs == 1)
		front_view(fdf);
	else if (fdf->projs == 2)
		side_view(fdf);
	else
		top_view(fdf);
}

void	zoom_out(t_fdf *fdf)
{
	fdf->spacing -= 1;
	if (!fdf->projs)
		isometric_view(fdf);
	else if (fdf->projs == 1)
		front_view(fdf);
	else if (fdf->projs == 2)
		side_view(fdf);
	else
		top_view(fdf);
}

void	translate_x(int key_code, t_fdf *fdf)
{
	if (key_code == 124)
		fdf->translate_x += 10;
	else
		fdf->translate_x -= 10;
	if (!fdf->projs)
		isometric_view(fdf);
	else if (fdf->projs == 1)
		front_view(fdf);
	else if (fdf->projs == 2)
		side_view(fdf);
	else
		top_view(fdf);
}

void	translate_y(int key_code, t_fdf *fdf)
{
	if (key_code == 125)
		fdf->translate_y += 10;
	else
		fdf->translate_y -= 10;
	if (!fdf->projs)
		isometric_view(fdf);
	else if (fdf->projs == 1)
		front_view(fdf);
	else if (fdf->projs == 2)
		side_view(fdf);
	else
		top_view(fdf);
}
