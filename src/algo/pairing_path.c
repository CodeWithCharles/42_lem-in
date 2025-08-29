/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:19:59 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/29 16:29:02 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

void add_path_combined(t_path_comb *res, t_path_combined *path_res){
	res->combined_paths = ft_reallocarray(res->combined_paths, (res->nb + 1), sizeof(t_path*), res->nb);
	res->combined_paths[res->nb]->list_paths = malloc(sizeof(int*) * path_res->nb);
	res->combined_paths[res->nb]->length_paths = malloc(sizeof(int) * path_res->nb);
	for (int i = 0; i < path_res->nb; i++)
	{
		res->combined_paths[res->nb]->length_paths[i] = path_res->length_paths[i];
	}
	for (int i = 0; i < path_res->nb; i++)
	{
		res->combined_paths[res->nb]->list_paths[i] = malloc(sizeof(int) * path_res->length_paths[i]);
		for (int j = 0; j < path_res->length_paths[i]; j++)
		{
			res->combined_paths[res->nb]->list_paths[i][j] = path_res->list_paths[i][j];
		}
	}
	res->combined_paths[res->nb]->nb = path_res->nb;
	res->nb++;
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

void cp_cur_pile_to_next_pile(t_path_combined *current_pile, t_path_combined *next_pile){
	next_pile->nb = current_pile->nb + 1;
	next_pile->nb_rooms = current_pile->nb_rooms;
	next_pile->rooms_taken = current_pile->rooms_taken;
	next_pile->nb_path = current_pile->nb_path;
	next_pile->rooms = malloc(sizeof(int) * next_pile->nb_rooms);
	for (int i = 0; i < next_pile->nb_rooms; i++)
	{
		next_pile->rooms[i] = current_pile->rooms[i];
	}
	next_pile->possible_paths = malloc(sizeof(int) * next_pile->nb_path);
	for (int i = 0; i < next_pile->nb_path; i++)
	{
		next_pile->possible_paths[i] = current_pile->possible_paths[i];
	}
	next_pile->list_paths = malloc(sizeof(int *) * next_pile->nb);
	next_pile->length_paths = malloc(sizeof(int) * next_pile->nb);
	for (int i = 0; i < current_pile->nb; i++)
	{
		next_pile->length_paths[i] = current_pile->length_paths[i];
	}
	for (int i = 0; i < current_pile->nb; i++)
	{
		next_pile->list_paths[i] = malloc(sizeof(int) * next_pile->length_paths[i]);
		for (int j = 0; j < current_pile->length_paths[i]; j++)
		{
			next_pile->list_paths[i][j] = current_pile->list_paths[i][j];
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

void find_best_path(t_path *all_path, t_path_comb *combined_path, int idx){
	t_path_pile *pile = create_pile_path(100);

	t_path_combined init;
	init.nb = 1;
	init.length_paths = malloc(sizeof(int));
	init.length_paths[0] = all_path->length_paths[idx];
	init.list_paths = malloc(sizeof(int *));
	init.list_paths[0] = malloc(sizeof(int) * init.length_paths[0]);
	for (int i = 0; i < init.length_paths[0]; i++)
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
				cp_cur_pile_to_next_pile(&current_pile, &next_pile);
				next_pile.list_paths[next_pile.nb] = malloc(sizeof(int) * all_path->length_paths[i]);
				for (int j = 0; j < all_path->length_paths[i] ; j++)
				{
					next_pile.list_paths[next_pile.nb][j] = all_path->list_paths[i][j];
				}
				visited_rooms(next_pile.rooms, all_path->list_paths[i], all_path->length_paths[i]);
				pruning_path(&next_pile, all_path);
				push_path_pile(pile, next_pile);
				free_path_combined(&next_pile);
			}
		}
		free_path_combined(&current_pile);
	}
	free(pile->pile);
	free(pile);
}

void free_path_comb(t_path_comb *val){
	for (int i = 0; i < val->nb; i++)
	{
		free_path(val->combined_paths[i]);
	}
	free(val);
}

#include <stdio.h>
t_path_comb *best_combined_path(t_path *all_path) {
	t_path_comb *comb_path;
	comb_path = malloc(sizeof(t_path_comb));
	comb_path->combined_paths = malloc(sizeof(t_path*));
	comb_path->combined_paths[0] = NULL;
	comb_path->nb = 0;

	for (int i = 0; i < all_path->nb; i++)
	{
		printf("int value : %d\n", i);
		find_best_path(all_path, comb_path, i);
	}
	return (comb_path);
}