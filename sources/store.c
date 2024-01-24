// int	cal_iso_rot(_Bool is_x, int x, int y, t_fdf *fdf)
// {
// 	//theta -> -135, beta -> 0, alpha -> -235
// 	if (is_x)
// 		return ((fdf->rot * (x * fdf->spacing)) - (fdf->rot1) * 
// 		(y * fdf->spacing) + (fdf->rot2) * *(*(fdf->map_numbers + y) + x));
// 	return ((fdf->rot3) * (x * fdf->spacing) + (fdf->rot4) * 
// 		(y * fdf->spacing) - (fdf->rot5) * *(*(fdf->map_numbers + y) + x));
// }

// void	check_last_point_for_isometric_view(int x, int y, t_fdf *fdf)
// {
// 	fdf->x_1 = cal_iso_rot(1, x, y, fdf) + fdf->x_offset;
// 	fdf->y_1 = cal_iso_rot(0, x, y, fdf) + fdf->y_offset;
// 	if (y + 1 != fdf->map_height)
// 	{
// 		if (*(*(fdf->map_colors + y) + x))
// 			fdf->colour = *(*(fdf->map_colors + y) + x);
// 		else if (*(*(fdf->map_colors + y + 1) + x))
// 			fdf->colour = *(*(fdf->map_colors + y + 1) + x);
// 		fdf->x_2 = cal_iso_rot(1, x, y, fdf) + fdf->x_offset;
// 		fdf->y_2 = cal_iso_rot(0, x, y + 1, fdf) + fdf->y_offset;
// 		dda(fdf);
// 	}
// 	if (x + 1 != fdf->map_width)
// 	{
// 		if (*(*(fdf->map_colors + y) + x))
// 			fdf->colour = *(*(fdf->map_colors + y) + x);
// 		else if (*(*(fdf->map_colors + y) + x + 1))
// 			fdf->colour = *(*(fdf->map_colors + y) + x + 1);
// 		fdf->x_2 = cal_iso_rot(1, x + 1, y, fdf) + fdf->x_offset;
// 		fdf->y_2 = cal_iso_rot(0, x, y, fdf) + fdf->y_offset;
// 		dda(fdf);
// 	}
// }

// void	draw(t_fdf *fdf)
// {
// 	int	x;
// 	int	y;

// 	x = -1;
// 	while (++x < fdf->map_width)
// 	{
// 		y = -1;
// 		while (++y < fdf->map_height)
// 			check_last_point_for_isometric_view(x, y, fdf);
// 	}
// }

// void	isometric_view(t_fdf *fdf)
// {
// 	fdf->mlx.image = mlx_new_image(fdf->mlx.mlx, fdf->size_x, fdf->size_y);
// 	fdf->mlx.image_address = mlx_get_data_addr(fdf->mlx.image,
// 			&fdf->mlx.pixel_bit, &fdf->mlx.size_line, &fdf->mlx.endian);
// 	fdf->projs = ISO;
// 	calculate_offset(fdf);
// 	draw(fdf);
// 	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.window,
// 		fdf->mlx.image, 0, 0);
// 	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.image);
// }
