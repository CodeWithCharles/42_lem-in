/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:23:34 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/14 16:12:53 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

typedef enum e_room_type
{
	ROOM = 0,
	START,
	EXIT
}	t_room_type;

typedef struct s_room
{
	char		*name;
	int			x;
	int			y;
	int			id;
	t_room_type	type;
	struct		s_room	**links;
	size_t		link_count;
}	t_room;
