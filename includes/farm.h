/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:26:43 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 16:09:37 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "room.h"

typedef	struct	s_farm
{
	size_t	ant_count;
	t_room	**rooms;
	size_t	room_count;
	t_room	*start;
	t_room	*end;
}	t_farm;
