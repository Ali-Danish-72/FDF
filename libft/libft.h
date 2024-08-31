/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:21:19 by mdanish           #+#    #+#             */
/*   Updated: 2024/08/30 19:58:34 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>

# define HEX_LOW "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"
# define DECIMAL "0123456789"

/*****************************************************************************/
/*								CONVERTERS									 */
/*****************************************************************************/
long	ft_atoi(char const *string);

/*****************************************************************************/
/*								COUNTERS									 */
/*****************************************************************************/
size_t	word_counter(char const *source, char delimiters);
size_t	word_length(char const *source, char delimiters);

/*****************************************************************************/
/*								FT_PRINTF									 */
/*****************************************************************************/
size_t	print_address(void *variable, int fd);
size_t	print_character(int character, int fd);
size_t	print_hexadecimal(size_t number, char specifier, int fd);
size_t	print_number(long int number, int fd);
size_t	ft_printf(int fd, char *string, ...);
size_t	print_string(char const *string, int fd);
size_t	print_unsigned_base(size_t number, int fd, char *base, size_t base_len);

/*****************************************************************************/
/*								GET_NEXT_LINE								 */
/*****************************************************************************/
char	*get_next_line(int fd);

/*****************************************************************************/
/*								MEMORY										 */
/*****************************************************************************/
void	*ft_calloc(size_t count, size_t size);

/*****************************************************************************/
/*								STRINGS										 */
/*****************************************************************************/
void	free_split(void **split, size_t word_count);
char	**ft_split(char const *source, char delimiters);
char	*ft_strchr(char const *string, int character);
char	*ft_strjoin(char const *string1, char const *string2);
char	*ft_strjoin_free(char const *string1, char const *string2, int flag);
size_t	ft_strlcpy(char *destination, char const*source, size_t destsize);
size_t	ft_strlen(char const *string);
int		ft_strncmp(char const *string1, char const *string2, size_t characters);
char	*ft_substr(char const *source, size_t start, size_t length);

#endif
