/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:58:28 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/12 16:52:52 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_substr(char const *source, size_t start, size_t len)
{
	char	*string;
	size_t	source_length;

	if (!len)
		return (NULL);
	source_length = ft_strlen(source);
	if (source_length <= len)
		len = source_length - start;
	if ((start + len) > source_length)
		len--;
	if (source_length < start || !source_length || (len == (size_t)-1))
		len = 0;
	string = (char *)ft_calloc(++len, sizeof(char));
	if (!string)
		return (NULL);
	ft_strlcpy(string, source + start, len);
	return (string);
}
