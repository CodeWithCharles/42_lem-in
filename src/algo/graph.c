/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:29:56 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/17 15:31:44 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

int find_link_on_rooms(t_room **rooms, size_t size, size_t idx){
	for (size_t i = 0; i < size; i++)
	{
		if (rooms[i]->id == (int)idx)
			return (1);
	}
	return (0);
}

int **create_graph(void){
	int **new_graph;
	size_t size = g_ctx->farm->room_count;
	
	new_graph = malloc(sizeof(int *) * (int)size);
	if (!new_graph)
		return (NULL);
	for (size_t i = 0; i < size; i++)
	{
		new_graph[i] = malloc(sizeof(int) * ((int)size));
	}
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i == j)
				new_graph[i][j] = 0;
			else {
				new_graph[i][j] = find_link_on_rooms(g_ctx->farm->rooms[i]->links, g_ctx->farm->rooms[i]->link_count ,j);
			}
		}
	}
	return (new_graph);
}

void free_graph(int **graph, size_t size){
	for (size_t i = 0; i < size; i++)
	{
		free(graph[i]);
	}
	free(graph);
}

void show_graph(int **graph, size_t size){
	for (size_t i = 0; i < size; i++)
	{
		if (i == 0)
			printf("    |%zu|", i);
		else 
			printf("|%zu|", i);
	}
	printf("\n");
	
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (j == 0)
				printf("|%zu| ", i);
			printf (" %d ", graph[i][j]);
		}
		printf ("\n");
	}
	
}