/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:30:24 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/14 17:14:21 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	has_unique_names(t_farm *farm);
static int	has_unique_coordinates(t_farm *farm);
static int	links_are_valid(t_farm *farm);
static int	has_unique_room_type(t_farm *farm, t_room_type type);

void	validate_farm(t_farm *farm)
{
	if (!farm)
		exit_error(NULL);
	if (farm->ant_count <= 0)
		exit_error(ERR_NO_ANTS);
	if (!farm->rooms || farm->room_count == 0)
		exit_error(ERR_NO_ROOMS);
	if (!farm->start || !farm->end)
		exit_error(ERR_NO_SE_ROOM);
	if (farm->start == farm->end)
		exit_error(ERR_SAME_SE_ROOM);
	if (!has_unique_names(farm))
		exit_error(ERR_DUP_ROOM_NAME);
	if (!has_unique_coordinates(farm))
		exit_error(ERR_DUP_ROOM_COOR);
	if (!links_are_valid(farm))
		exit_error(ERR_INVALID_LINK);
	if (!has_unique_room_type(farm, EXIT))
		exit_error(ERR_MUL_END);
	if (!has_unique_room_type(farm, START))
		exit_error(ERR_MUL_START);
}

static int	has_unique_names(t_farm *farm)
{
	for (size_t i = 0; i < farm->room_count; i++)
		for (size_t j = i + 1; j < farm->room_count; j++)
			if (ft_strcmp(farm->rooms[i]->name, farm->rooms[j]->name) == 0)
				return (0);
	return (1);
}

static int	has_unique_coordinates(t_farm *farm)
{
	for (size_t i = 0; i < farm->room_count; i++)
		for (size_t j = i + 1; j < farm->room_count; j++)
			if (farm->rooms[i]->x == farm->rooms[j]->x &&
				farm->rooms[i]->y == farm->rooms[j]->y)
				return (0);
	return (1);
}

static int	links_are_valid(t_farm *farm)
{
	unsigned short	found = 0;

	for (size_t	i = 0; i < farm->room_count; i++)
	{
		t_room *room = farm->rooms[i];
		for (size_t j = 0; j < room->link_count; j++)
		{
			t_room	*link = room->links[j];
			if (!link) return (0);
			found = 0;
			for (size_t	k = 0; k < farm->room_count; k++)
			{
				if (farm->rooms[k] == link)
				{
					found = 1;
					break;
				}
			}
			if (!found) return (0);
		}
	}
	return (1);
}

static int	has_unique_room_type(t_farm *farm, t_room_type type)
{
	unsigned short count = 0;
	for (size_t i = 0; i < farm->room_count; i++)
	{
		if (farm->rooms[i]->type == type)
			count++;
		if (count > 1)	return (0);
	}
	return (1);
}
