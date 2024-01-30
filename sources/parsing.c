/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:20:59 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/30 21:21:42 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

unsigned int	ft_atoh(char const *string)
{
	int			negative_flag;
	long int	number;

	if (!*string)
		return (0);
	number = 0;
	negative_flag = 1;
	if (*string == '0' && *(string + 1) == 'x')
		string += 2;
	while (*string == 48)
		string++;
	while (*string)
	{
		if (ft_strchr(HEX_UP, *string))
			number = (number * 16) + ft_strchr(HEX_UP, *string++) - HEX_UP;
		else if (ft_strchr(HEX_LOW, *string))
			number = (number * 16) + ft_strchr(HEX_LOW, *string++) - HEX_LOW;
	}
	return (number * negative_flag);
}

void	extract_heights_and_colours(t_fdf *fdf, int index, char **values)
{
	char	*value;
	int		width;

	*(fdf->map.map_numbers + index) = ft_calloc(fdf->map.map_width, 
			sizeof(int));
	if (!fdf->map.map_numbers)
		call_exit(7, fdf);
	*(fdf->map.map_colors + index) = ft_calloc(fdf->map.map_width, 
			sizeof(unsigned));
	if (!fdf->map.map_colors)
		call_exit(8, fdf);
	width = fdf->map.map_width;
	while (width--)
	{
		value = *(values + width);
		*(*(fdf->map.map_numbers + index) + width) = ft_atoi(value);
		while (*value && *value != ',')
			value++;
		if (!*value)
			*(*(fdf->map.map_colors + index) + width) = 0;
		else
			*(*(fdf->map.map_colors + index) + width) = ft_atoh(++value);
	}
}

void	extract_values(t_fdf *fdf)
{
	char	**map;
	char	**values;
	int		index;

	fdf->map.map_numbers = ft_calloc(fdf->map.map_height, sizeof(int *));
	if (!fdf->map.map_numbers)
		call_exit(7, fdf);
	fdf->map.map_colors = ft_calloc(fdf->map.map_height, sizeof(unsigned *));
	if (!fdf->map.map_colors)
		call_exit(8, fdf);
	index = -1;
	map = fdf->map.parsed_map;
	while (*map)
	{
		values = ft_split(*map, ' ');
		if (!values)
			call_exit(7, fdf);
		fdf->map.map_width = word_counter(*map++, ' ');
		extract_heights_and_colours(fdf, ++index, values);
		free_split((void **)values, fdf->map.map_width);
	}
}

void	initialise_constants(t_fdf *fdf)
{
	fdf->map.map_height = 0;
	fdf->map.parsed_map = NULL;
	fdf->map.single_line = NULL;
	fdf->map.map_colors = NULL;
	fdf->map.map_numbers = NULL;
	fdf->map.size_x = 1600;
	fdf->map.size_y = 1200;
	fdf->consts.spacing = 30;
	fdf->consts.translate_x = 0;
	fdf->consts.translate_y = 0;
	fdf->consts.rotation_x = 0;
	fdf->consts.rotation_y = 0;
	fdf->consts.rotation_z = 0;
	fdf->xy.z_colour_index = 4;
	fdf->xy.no_z_colour_index = 0;
	*(fdf->xy.colours + 0) = 0xFFFFFF;
	*(fdf->xy.colours + 1) = 0xFEFE33;
	*(fdf->xy.colours + 2) = 0xFF8C00;
	*(fdf->xy.colours + 3) = 0x68217A;
	*(fdf->xy.colours + 4) = 0xE81123;
	*(fdf->xy.colours + 5) = 0xEC008C;
	*(fdf->xy.colours + 6) = 0x00BCF2;
	*(fdf->xy.colours + 7) = 0x00B294;
	*(fdf->xy.colours + 8) = 0x009E49;
}

void	parse(t_fdf *fdf, char *map_path)
{
	
	fdf->map.map_fd = open(map_path, O_RDONLY);
	if (fdf->map.map_fd < 0)
		call_exit(3, fdf);
	initialise_constants(fdf);
	fdf->map.map_line = get_next_line(fdf->map.map_fd);
	if (!fdf->map.map_line)
		call_exit(4, fdf);
	while (fdf->map.map_line)
	{
		fdf->map.single_line = ft_strjoin_free(fdf->map.single_line, 
				fdf->map.map_line, 3);
		if (!fdf->map.single_line)
			call_exit(5, fdf);
		fdf->map.map_height++;
		fdf->map.map_line = get_next_line(fdf->map.map_fd);
	}
	fdf->map.parsed_map = ft_split(fdf->map.single_line, '\n');
	if (!fdf->map.parsed_map)
		call_exit(6, fdf);
	extract_values(fdf);
}
