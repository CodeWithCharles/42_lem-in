/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:52:46 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 14:54:12 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room	*find_room_by_name(
	t_farm *farm,
	const char *name
)
{
	size_t	i;

	if (!farm || !name)
		return (NULL);
	i = 0;
	while (i < farm->room_count)
	{
		if (farm->rooms[i] && ft_strcmp(farm->rooms[i]->name, name) == 0)
			return (farm->rooms[i]);
		i++;
	}
	return (NULL);
}
