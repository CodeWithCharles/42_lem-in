/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:26:43 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 12:27:46 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "room.h"

typedef	struct	s_farm
{
	int		ant_count;
	t_room	**rooms;
	int		room_count;
	t_room	*start;
	t_room	*end;
}	t_farm;
