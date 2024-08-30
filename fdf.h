/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:14:14 by mdanish           #+#    #+#             */
/*   Updated: 2024/08/29 21:59:25 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

# if __APPLE__
#  include "minilibx-mac/mlx.h"
#  define ESC 53
#  define Q 12
#  define W 13
#  define A 0
#  define S 1
#  define Z 6
#  define X 7
#  define O 31
#  define I 34
#  define L 37
#  define K 40
#  define H 4
#  define M 46
#  define LEFT 123
#  define RIGHT 124
#  define UP 126
#  define DOWN 125
#  define PLUS 24
#  define MINUS 27
#  define PROJECTION1 18
#  define PROJECTION2 19
#  define PROJECTION3 20
#  define PROJECTION4 21
# elif __linux__
#  define ESC 65307
#  define Q 113
#  define W 119
#  define A 97
#  define S 115
#  define Z 122
#  define X 120
#  define O 111
#  define I 105
#  define L 108
#  define K 107
#  define H 104
#  define M 109
#  define LEFT 65361
#  define RIGHT 65363
#  define UP 65362
#  define DOWN 65364
#  define PLUS 61
#  define MINUS 45
#  define PROJECTION1 49
#  define PROJECTION2 50
#  define PROJECTION3 51
#  define PROJECTION4 52
# endif

/*		An enum to identify the projection currently in display.			*/
typedef enum e_projection
{
	ISOMETRIC_VIEW,
	FRONT_VIEW,
	SIDE_VIEW,
	TOP_VIEW
}			t_project;

/*		Contains all the data relating to the map obtained from parsing.	*/
typedef struct s_map_data
{
	int				map_fd;
	int				map_height;
	int				map_width;
	int				size_x;
	int				size_y;
	int				**map_numbers;
	unsigned int	**map_colors;
	char			*map_line;
	char			*single_line;
	char			**parsed_map;
}					t_map_data;

/*		Contains all data relating to the mlx window and images.			*/
typedef struct s_mlx
{
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	char			*image_address;
	void			*mlx;
	void			*window;
	void			*image;
}					t_mlx;

/*		Contains all data related to (x, y) as well as rotation constants.	*/
typedef struct s_coordinates
{
	float			x_1;
	float			y_1;
	float			x_2;
	float			y_2;
	float			final_x;
	float			final_y;
	float			x_const_x;
	float			x_const_y;
	float			x_const_z;
	float			y_const_x;
	float			y_const_y;
	float			y_const_z;
	int				z_colour_index;
	int				no_z_colour_index;
	unsigned int	pixel_colour;
	unsigned int	colours[7];
}					t_coords;

/*		Contains all data related to the transformation constants.			*/
typedef struct s_transformations
{
	float			rotation_x;
	float			rotation_y;
	float			rotation_z;
	int				spacing;
	int				translate_x;
	int				translate_y;
	int				x_offset;
	int				y_offset;
	int				help_flag;
	int				prank_flag;
}					t_transform;

/*		The main struct that contains all the other structs.				*/
typedef struct s_fdf
{
	t_map_data		map;
	t_mlx			mlx;
	t_coords		xy;
	t_transform		consts;
	t_project		projection;
}					t_fdf;

/*				Hooks				*/
int				identify_key(int key_code, t_fdf *fdf);
int				identify_mouse(int mouse_code, int x, int y, t_fdf *fdf);
int				switch_projection(int key_code, t_fdf *fdf);
void			transformations(int key_code, t_fdf *fdf);

/*				Parsing				*/
unsigned int	ft_atoh(char const *string);
void			extract_heights_and_colours(t_fdf *fdf, int index, char **vals);
void			extract_values(t_fdf *fdf);
void			initialise_constants(t_fdf *fdf);
void			parse(t_fdf *fdf, char *map_path);

/*				Projections			*/
void			build_image(t_fdf *fdf);
void			draw_line(int *xy, t_fdf *fdf);
void			execute_projection(t_fdf *fdf, int projection_code);
unsigned int	identify_colour(int is_x, int *xy, t_fdf *fdf);
float			rotate(int is_x, int x, int y, t_fdf *fdf);

/*				Window				*/
void			calculate_constants(float a, float b, float g, t_fdf *fdf);
void			dda(t_fdf *fdf);
void			draw_pixel(t_fdf *fdf);
void			initialise_window(t_fdf fdf);
void			print_menu(t_fdf *fdf);

/*				Error Handling		*/
void			call_exit(int status, t_fdf *fdf);
int				destroy_window(t_fdf *fdf);
void			free_data(t_fdf *fdf);

//	Exit codes:
//	0 = Successful completion of the program.
//	1 = Incorrect number of arguments.
//	2 = Incorrect extension of file detected.
//	3 = Error encountered while opening the map.
//	4 = Malloc failed while parsing the map.
//	5 = Malloc failed while joining the map.
//	6 = Malloc failed while splitting the map.
//	7 = Malloc failed while splitting the values.

#endif