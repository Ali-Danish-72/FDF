/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanish <mdanish@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:29:00 by mdanish           #+#    #+#             */
/*   Updated: 2024/01/12 16:32:39 by mdanish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*get_next_line(int fd)
{
	char	*store;
	char	*line;

	store = ft_calloc(10000, sizeof(char));
	if (!store || fd < 0)
		return (free(store), NULL);
	line = store;
	while (read(fd, store, 1) > 0 && *store != '\n')
		store++;
	if (store == line && *store != '\n')
		return (free(line), NULL);
	*++store = '\0';
	return (line);
}
