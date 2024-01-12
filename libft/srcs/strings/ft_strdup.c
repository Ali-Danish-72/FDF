/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:49:38 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/12 16:51:44 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strdup(char const *string)
{
	char	*duplicate;
	size_t	string_length;

	string_length = ft_strlen(string) + 1;
	duplicate = (char *)ft_calloc(string_length, sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, string, string_length);
	return (duplicate);
}
