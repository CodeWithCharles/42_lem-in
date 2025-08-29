/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:54 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/29 16:29:13 by jbergos          ###   ########.fr       */
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
	// t_path res = {NULL, NULL, 0};
	t_path *res;
	res = malloc(sizeof(t_path));
	res->length_paths = NULL;
	res->list_paths = NULL;
	res->nb = 0;
	dfs(graph, g_ctx->farm->start->id, g_ctx->farm->end->id, res);
	show_path(res);
	t_path_comb *bcp;
	bcp = best_combined_path(res);
	// for (int i = 0; i < bcp->nb; i++)
	// {
	// 	printf("%d : combined path\n", i);
	// 	show_path(bcp->combined_paths[i]);
	// }
	free_path(res);
	free(res);
	free(bcp);
	free_graph(graph, g_ctx->farm->room_count);
	//end algo
	free_context(g_ctx);
	return (0);
}
