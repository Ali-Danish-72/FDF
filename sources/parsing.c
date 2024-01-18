/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:20:59 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/18 19:56:31 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_atoh(char const *string)
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

	*(fdf->map_numbers + index) = ft_calloc(fdf->map_width, sizeof(int));
	if (!fdf->map_numbers)
		call_exit(7, *fdf);
	*(fdf->map_colors + index) = ft_calloc(fdf->map_width, sizeof(int));
	if (!fdf->map_colors)
		call_exit(8, *fdf);
	width = fdf->map_width;
	while (width--)
	{
		value = *(values + width);
		*(*(fdf->map_numbers + index) + width) = ft_atoi(value);
		while (*value && *value != ',')
			value++;
		if (!*value)
			*(*(fdf->map_colors + index) + width) = 0;
		else
			*(*(fdf->map_colors + index) + width) = ft_atoh(++value);
	}
}

void	extract_values(t_fdf *fdf)
{
	char	**map;
	char	**values;
	int		index;

	fdf->map_numbers = ft_calloc(fdf->map_height, sizeof(int *));
	if (!fdf->map_numbers)
		call_exit(7, *fdf);
	fdf->map_colors = ft_calloc(fdf->map_height, sizeof(int *));
	if (!fdf->map_colors)
		call_exit(8, *fdf);
	index = -1;
	map = fdf->parsed_map;
	while (*map)
	{
		values = ft_split(*map, ' ');
		if (!values)
			call_exit(7, *fdf);
		fdf->map_width = word_counter(*map++, ' ');
		extract_heights_and_colours(fdf, ++index, values);
		free_split((void **)values, fdf->map_width);
	}
}

void	initialise_constants(t_fdf *fdf)
{
	fdf->map_height = 0;
	fdf->parsed_map = NULL;
	fdf->single_line = NULL;
	fdf->map_colors = NULL;
	fdf->map_numbers = NULL;
	fdf->size_x = 1600;
	fdf->size_y = 1200;
	fdf->spacing = 30;
	fdf->translate_x = 0;
	fdf->translate_y = 0;
}

int	parse(t_fdf *fdf, char *map_path)
{
	fdf->map_fd = open(map_path, O_RDONLY);
	if (fdf->map_fd < 0)
		return (3);
	initialise_constants(fdf);
	fdf->map_line = get_next_line(fdf->map_fd);
	if (!fdf->map_line)
		call_exit(4, *fdf);
	while (fdf->map_line)
	{
		fdf->single_line = ft_strjoin_free(fdf->single_line, fdf->map_line, 3);
		if (!fdf->single_line)
			call_exit(5, *fdf);
		fdf->map_height++;
		fdf->map_line = get_next_line(fdf->map_fd);
	}
	fdf->parsed_map = ft_split(fdf->single_line, '\n');
	if (!fdf->parsed_map)
		call_exit(6, *fdf);
	extract_values(fdf);
	return (0);
}
