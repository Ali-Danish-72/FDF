/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:21:42 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/12 18:36:06 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	digit_counter(long number)
{
	int	counter;

	if (number == 0)
		return (1);
	counter = 0;
	if (number < 0)
		counter++;
	while (number)
	{
		counter++;
		number /= 10;
	}
	return (counter);
}

char	*ft_itoa(long num)
{
	int		counter;
	size_t	number;
	char	*string;

	counter = digit_counter(num);
	string = (char *)ft_calloc((counter + 1), sizeof(char));
	if (!string)
		return (NULL);
	*(string + counter) = '\0';
	number = ft_absolute(num);
	while (counter--)
	{
		*(string + counter) = (number % 10 + 48);
		number /= 10;
	}
	if (num < 0)
		*string = '-';
	return (string);
}
