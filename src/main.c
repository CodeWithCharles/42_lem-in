/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:54 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/16 14:19:35 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/libft.h"
// #include "../includes/algo.h"
// #include <stdio.h>



// int	main(void)
// {
// 	t_context *test;
// 	test = brut_init();
// 	int i = 0;
// 	while (test->farm->rooms[i])
// 	{
// 		printf("rooms name : %s\n", test->farm->rooms[i]->name);
// 		for (int j = 0; test->farm->rooms[i]->links[j]; j++)
// 		{
// 	 		printf("----- Linked rooms to her : %s\n", test->farm->rooms[i]->links[j]->name);
// 		}
// 	++i;
//  	}
//  	int **graph;
//  	graph = create_graph(test, test->farm->room_count);
// 	show_graph(graph, test->farm->room_count);
// 	int visited[8] = {0};
// 	int way[8];
// 	printf("all way to %s at %s\n", test->farm->start->name, test->farm->end->name);
// 	dfs(graph, test->farm->start->id, test->farm->end->id, visited, way, 0, test->farm->room_count);
// 	free_graph(graph, test->farm->room_count);
//  	free_ant(test);
//  	return (0);
// }

#include "lem-in.h"

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
	free_context(g_ctx);
	return (0);
}
