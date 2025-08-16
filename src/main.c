/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:54 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/16 21:48:35 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"
#include "algo.h"

t_context *g_ctx = NULL;

int	main(void)
{
	g_ctx = ft_calloc(1, sizeof(t_context));
	if (!g_ctx)
		exit_error(ERR_MALLOC);

	g_ctx->farm = ft_calloc(1, sizeof(t_farm));
	if (!g_ctx->farm)
		exit_error(ERR_MALLOC);
	parse_input();
	validate_farm(g_ctx->farm);
	print_original_input();
	// algo
	int **graph = create_graph();
	show_graph(graph, g_ctx->farm->room_count);
	t_path res = {NULL, NULL, 0};
	dfs(graph, g_ctx->farm->start->id, g_ctx->farm->end->id, &res);
	show_path(res);
	free_path(res);
	// free graph
	free_graph(graph, g_ctx->farm->room_count);
	//end algo
	free_context(g_ctx);
	return (0);
}
