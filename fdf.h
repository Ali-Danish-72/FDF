/* ************************************************************************** */
/*	                                                                      */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:14:14 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/07 16:25:31 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <errno.h>
# include <math.h>

typedef struct s_fdf
{
	int			map_fd;
	int			map_height;
	int			map_width;
	int			**map_numbers;
	int			**map_colors;
	char		*map_line;
	char		*single_line;
	char		**parsed_map;
	void		*mlx_data;
	void		*mlx_window;
}				t_fdf;

/*		Error Handling	*/
void	call_exit(int status, t_fdf fdf);
int		print_error_message(int status);

/*		Parsing			*/
void	extract_heights_and_colours(t_fdf *fdf, int index, char **values);
void	extract_values(t_fdf *fdf);
int		ft_atoh(char const *string);
int		parse(t_fdf *fdf, char *map_path);

//	Exit Codes:
//	0 = Successful completion of the program.
//	1 = Incorrect number of arguments.
//	2 = Incorrect extension of file detected.
//	3 = Error encountered while opening the map.
//	4 = Malloc failed while parsing the map.
//	5 = Malloc failed while joining the map.
//	6 = Malloc failed while splitting the map.
//	7 = Malloc failed while splitting the values.

//	8 = Splitting of the command arguments failed.
//	9 = Malloc while trimming the qoutations failed.
//	10 = Duplication of the fd failed.
//	11 = Malloc while searching for the command failed.
//	12 = Command not found.
//	13 = Insufficient arguments for the here_doc bonus.
//	14 = Error while opening/creating the here_doc temp file.
//	15 = Error while opening/creating the here_doc output file.
//	16 = Error while opening the here_doc temp file for reading.

#endif