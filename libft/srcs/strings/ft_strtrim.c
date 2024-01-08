/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:58:49 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/08 16:16:54 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	char_trim(char character, char const *set)
{
	while (*set)
	{
		if (*set == character)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *string, char const *set, int to_free)
{
	char	*start;
	char	*end;
	char	*trim;
	size_t	string_length;

	start = (char *)string;
	while (char_trim(*start, set))
		start++;
	string_length = ft_strlen(string) - 1;
	end = (char *)string + string_length;
	while (char_trim(*end, set))
		end--;
	if (start == string && end == (string + string_length))
		return ((char *)string);
	trim = (char *)malloc(end - start + 2);
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, start, end - start + 2);
	if (to_free)
		free((void *)string);
	return (trim);
}

