/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:56:39 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/12 16:46:37 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_strncmp(char const *string1, char const *string2, size_t characters)
{
	while (characters && *string1 && *string2 && *string1 == *string2)
	{
		string1++;
		string2++;
		characters--;
	}
	if (!characters)
		return (0);
	return (*string1 - *string2);
}
