/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:19:59 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/22 17:24:40 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

void add_path_combined(t_path_comb *res, t_path_combined *path_res){
	res->combined_paths = ft_reallocarray(res->combined_paths, (res->nb + 1), sizeof(t_path*), res->nb);
	res->nb++;
}

t_path_comb *best_combined_path(t_path *all_path) {
	t_path_comb *comb_path;
	comb_path = malloc(sizeof(t_path *));
	comb_path->combined_paths[0] = NULL;
	comb_path->nb = 0;

	for (int i = 0; i < all_path->nb; i++)
	{
		
	}
}
void free_path_combined(t_path_combined *path){
	for (int i = 0; i < path->nb; i++)
	{
		free(path->list_paths[i]);
	}
	free(path->list_paths);
	free(path->length_paths);
	free(path->possible_paths);
	free(path->rooms);
}

void visited_rooms(int *rooms, int* path, int size_path){
	for (int i = 0; i < size_path; i++)
	{
		rooms[path[i]] = 1;
	}
}

void pruning_path(t_path_combined *path, t_path *all_path) {
	for (int i = 0; i < all_path->nb; i++)
	{
		if (!path->possible_paths[i]){
			if (path->rooms_taken + (all_path->length_paths[i] - 2) > path->nb_rooms) {
				path->possible_paths[i] = 1;
			} else {
				for (int j = 0; j < all_path->length_paths[i]; j++)
				{
					if (path->rooms[all_path->list_paths[i][j]]){
						path->possible_paths[i] = 1;
						break;
					}
				}
				
			}
		}
	}
	
}

int resting_possible_path(int *all_pathing, int nb_path) {
	for (int i = 0; i < nb_path; i++)
	{
		if (all_pathing[i])
			return (1);
	}
	return (0);
}

void *find_best_path(t_path *all_path, t_path_comb *combined_path, int idx){
	t_path_pile *pile = create_pile_path(10);

	t_path_combined init;
	init.nb = 1;
	init.length_paths = malloc(sizeof(int));
	init.length_paths[0] = all_path->length_paths[idx];
	init.list_paths = malloc(sizeof(int *));
	init.list_paths[0] = malloc(sizeof(int) * init.length_paths[0]);
	for (int i = 0; i < init.length_paths; i++)
	{
		init.list_paths[0][i] = all_path->list_paths[idx][i];
	}
	init.nb_path = all_path->nb;
	init.possible_paths = ft_calloc(init.nb_path, sizeof(int));
	init.possible_paths[idx] = 1;
	init.nb_rooms = (int)g_ctx->farm->room_count;
	init.rooms = ft_calloc(init.nb_rooms, sizeof(int));
	init.rooms_taken = init.length_paths[0];
	visited_rooms(init.rooms, init.list_paths[0], init.length_paths[0]);
	pruning_path(&init, all_path);
	push_path_pile(pile, init);
	free_path_combined(&init);
	
	while (!empty_path_pile(pile)) {
		t_path_combined current_pile = pop_path_pile(pile);

		if (!resting_possible_path(current_pile.possible_paths, current_pile.nb_path)){
			add_path_combined(combined_path, &current_pile);
			free_path_combined(&current_pile);
			continue;
		}

		for (int i = 0; i < all_path->nb; i++)
		{
			if (!current_pile.possible_paths[i]) {
				t_path_combined next_pile;
				next_pile.nb++;
				init.length_paths = malloc(sizeof(int) * next_pile.nb);
				for (int j = 0; j < current_pile.nb; j++)
				{
					next_pile.length_paths[j] = current_pile.length_paths[i];
				}
				next_pile.length_paths[next_pile.nb - 1] = all_path->length_paths[i];
				next_pile.list_paths = malloc(sizeof(int*) * next_pile.nb);
				for (int j = 0; j < next_pile.nb; j++)
				{
					next_pile.list_paths[j] = malloc(sizeof(int) * next_pile.length_paths[j]);
					for (int k = 0; k < next_pile.length_paths[j]; k++)
					{
						/* code */
					}
					
				}
				
			}
		}
		
	}
}