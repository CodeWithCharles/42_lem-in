/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:39:59 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 16:15:15 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	parse_and_add_link(
	t_farm	*farm,
	const char *line
)
{
	char	**parts = ft_split(line, '-');
	if (!parts || !parts[0] || !parts[1])
		exit_error(ERR_BAD_LINK);
	t_room	*a = find_room_by_name(farm, parts[0]);
	t_room	*b = find_room_by_name(farm, parts[1]);
	if (!a || !b)
		exit_error(ERR_FIND_ROOM);
	add_link(a, b);
	add_link(b, a);
	ft_free_split(&parts);

}

void	add_link(
	t_room	*a,
	t_room	*b
)
{
	a->links = ft_reallocarray(a->links, a->link_count + 1, sizeof(t_room *), a->link_count);
	a->links[a->link_count++]	= b;
}
