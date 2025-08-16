/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:34:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 16:10:28 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	free_rooms(t_farm *farm);
static void	free_room(t_room *room);

void	free_context(t_context *ctx)
{
	if (!ctx) return;
	if (ctx->input_lines) ft_free_split(&ctx->input_lines);
	if (ctx->farm)
	{
		if (ctx->farm->rooms) free_rooms(ctx->farm);
		free(ctx->farm);
	}
	free(ctx);
}

static void	free_rooms(t_farm *farm)
{
	size_t	i;

	for (i = 0; i < farm->room_count; i++) free_room(farm->rooms[i]);
	free(farm->rooms);
}

static void	free_room(t_room *room)
{
	if (!room) return;
	free(room->name);
	free(room->links);
	free(room);
}
