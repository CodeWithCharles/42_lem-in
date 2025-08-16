/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:45:52 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 16:14:11 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room	*parse_room_line(
	const char *line,
	t_room_type type,
	int id
)
{
	char **parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
		exit_error(ERR_BAD_ROOM);
	t_room *room = create_room(parts[0],
		ft_atoi(parts[1]), ft_atoi(parts[2]), type, id);
	ft_free_split(&parts);
	return (room);
}

t_room	*create_room(
	const char *name,
	int x,
	int y,
	t_room_type type,
	int id
)
{
	t_room *room = ft_calloc(1, sizeof(t_room));
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->id = id;
	room->type = type;
	return (room);
}

void	add_room_to_farm(
	t_farm *farm,
	t_room *room
)
{
	farm->rooms = ft_reallocarray(
		farm->rooms,
		farm->room_count + 1,
		sizeof(t_room *),
		farm->room_count
	);
	farm->rooms[farm->room_count++] = room;
}
