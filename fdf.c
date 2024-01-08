/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:25:50 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/08 19:55:39 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_error_message(int status)
{
	if (status == 1)
		ft_printf(2, "Use this format:\n./fdf <map_path.fdf>.\n");
	else if (status == 2)
		ft_printf(2, "Invalid file type detected.\n");
	else if (status == 3)
		ft_printf(2, "Error encountered while opening the map.\n");
	else if (status == 4)
		ft_printf(2, "%s\nMalloc during map read failed.", strerror(errno));
	else if (status == 5)
		ft_printf(2, "%s\nMalloc during map join failed.", strerror(errno));
	else if (status == 6)
		ft_printf(2, "%s\nMalloc during map split failed.", strerror(errno));
	// else if (status == 9)
	// 	ft_printf(2, "%s. Trimming the qoutations failed.\n", strerror(errno));
	// else if (status == 11)
	// 	ft_printf(2, "%s. Search for the command failed.\n", strerror(errno));
	// else if (status == 12)
	// 	ft_printf(2, "Open quotes detected in the command or its arguments\n");
	// else if (status == 13)
	// 	ft_printf(2, "Use this:\n./pipex here_doc LIMITER cmd cmd1 file\n");
	return (status);
}

void	call_exit(int status, t_fdf fdf)
{
	free_split(fdf.parsed_map, word_counter(fdf.complete_map, '\n'));
	free(fdf.complete_map);
	close(fdf.map_fd);
	exit(print_error_message(status));
}

int	parse(t_fdf *fdf, char *map_path)
{
	fdf->map_fd = open(map_path, O_RDONLY);
	if (fdf->map_fd < 0)
		return (print_error_message(3));
	fdf->complete_map = NULL;
	fdf->map_line = get_next_line(fdf->map_fd);
	if (!fdf->map_line)
		call_exit(4, *fdf);
	while (fdf->map_line)
	{
		fdf->complete_map = ft_strjoin_free(fdf->complete_map, fdf->map_line, 3);
		if (!fdf->complete_map)
			call_exit(5, *fdf);
		fdf->map_line = get_next_line(fdf->map_fd);
	}
	fdf->parsed_map = ft_split(fdf->complete_map, '\n');
	if (!fdf->parsed_map)
		call_exit(6, *fdf);
	return (0);
}

int main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (print_error_message(1));
	if (ft_strncmp((*(argv + 1) + (ft_strlen(*(argv + 1)) - 4)), ".fdf", 4))
		return (print_error_message(2));
	if (parse(&fdf, *(argv + 1)))
		return (print_error_message(3));
	call_exit(0, fdf);
}
