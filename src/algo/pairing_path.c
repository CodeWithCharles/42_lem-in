/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:03:12 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/17 18:00:08 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

void	reset_visited(int *visited, int *room_visited, int start, int end, int size){
	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
	}
	visited[start] = 1;
	visited[end] = 1;
	room_visited = 2;
}

void	add_path_to_visited(int *visited, int *room_visited, int *path, int size_path){
	for (int i = 1; i < size_path -1; i++)
	{
		visited[path[i]] = 1;
	}
	room_visited += (size_path - 2);
}

int		is_already_visited(int *visited, int *path, int size_path){
	for (int i = 1; i < size_path - 1; i++)
	{
		if (visited[path[i]] == 1)
			return (1);
	}
	return (0);
}

t_path *init_path(void){
	t_path *path;

	path = malloc(sizeof(t_path));
	path->list_paths = malloc(sizeof(int *));
	path->length_paths = malloc(sizeof(int));
	path->nb = 0;

	return (path);
}

t_path **pairing_path(t_path res, int start, int end){
	t_path **pairing_path;
	int length_table_path = 1;
	int *visited;
	int total_room = g_ctx->farm->room_count;
	int room_visited = 0;

	pairing_path = malloc(sizeof(t_path *));
	visited = ft_calloc(total_room, sizeof(int));

	visited[start] = 1;
	visited[end] = 1;
	room_visited += 2;

	for (int i = 0; i < res.nb; i++)
	{
		
		for (int j = 0; j < res.nb; j++)
		{
			if (i != j){
				if (room_visited + (res.length_paths[j] - 2) <= total_room){
					if (!is_already_visited(visited, res.list_paths[j], res.length_paths[j])){

					}
				}
			}
			++j;
		}
		++i;
	}
	
}