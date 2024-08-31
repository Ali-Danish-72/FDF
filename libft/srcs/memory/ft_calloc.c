/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:28:07 by mdanish           #+#    #+#             */
/*   Updated: 2024/08/30 19:55:23 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	size_t	length;

	if (size && (count > (UINT32_MAX / size)))
		return (NULL);
	length = count * size;
	pointer = (void *)malloc(length);
	if (!pointer)
		return (NULL);
	while (length--)
		((char *)pointer)[length] = '\0';
	return (pointer);
}
