/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:32:22 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/17 15:34:18 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

void add_path(t_path *res, int *pathing, int size_pathing) {
	res->list_paths = ft_reallocarray(res->list_paths, (res->nb  + 1), sizeof(int *), res->nb);
	res->length_paths = ft_reallocarray(res->length_paths, (res->nb + 1), sizeof(int), res->nb);

	int *copy = malloc(sizeof(int) * size_pathing);
	for (int i = 0; i < size_pathing; i++) copy[i] = pathing[i];
	
	res->list_paths[res->nb] = copy;
	res->length_paths[res->nb] = size_pathing;
	res->nb++;
}

int is_room_alrdy_in_path(int *pathing, int size_pathing, int room) {
	for (int i = 0; i < size_pathing; i++)
	{
		if (pathing[i] == room) return (1);
	}
	return (0);
}

void dfs(int **graph, int start, int end, t_path *res) {
	t_pile *pile = create_pile((int)g_ctx->farm->room_count);

	t_statut init;
	init.room = start;
	init.len_path = 1;
	init.pathing = malloc(g_ctx->farm->room_count * sizeof(int));
	init.pathing[0] = start;
	push_pile(pile, init);
	free(init.pathing);

	while (!empty_pile(pile)) {
		t_statut current_pile = pop_pile(pile);

		if (current_pile.room == end) {
			add_path(res, current_pile.pathing, current_pile.len_path);
			free(current_pile.pathing);
			continue;
		}

		for (int i = 0; i < (int)g_ctx->farm->room_count; i++) {
			if (graph[current_pile.room][i] == 1 && !is_room_alrdy_in_path(current_pile.pathing, current_pile.len_path, i)) {
				t_statut next_pile;
				next_pile.room = i;
				next_pile.len_path = current_pile.len_path + 1;
				next_pile.pathing = malloc(next_pile.len_path * sizeof(int));
				for (int j = 0; j < current_pile.len_path; j++)
				{
					next_pile.pathing[j] = current_pile.pathing[j];
				}
				next_pile.pathing[current_pile.len_path] = i;
				push_pile(pile, next_pile);
				free(next_pile.pathing);
			}
		}
		free(current_pile.pathing);
	}
	free(pile->pile);
	free(pile);
}

void show_path(t_path res) {
	printf("Nombre de chemins simples trouvés : %d\n", res.nb);
    for (int i = 0; i < res.nb; i++) {
        printf("Chemin %d : ", i + 1);
        for (int j = 0; j < res.length_paths[i]; j++) {
            printf("%d ", res.list_paths[i][j]);
        }
        printf("\n");
    }
	for (int i = 0; i < res.nb; i++) free(res.list_paths[i]);
}

void free_path(t_path path){
	free(path.list_paths);
	free(path.length_paths);
}