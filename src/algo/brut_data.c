/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brut_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:58:41 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/16 21:47:51 by jbergos          ###   ########.fr       */
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

void print_ways(int way[], int size){
	 for (int i = 0; i < size; i++) {
        printf("%d ", way[i]);
    }
    printf("\n");
}

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

t_pile *create_pile(int mem) {
	t_pile *base_pile = malloc(sizeof(t_pile));
	base_pile->pile = malloc(mem * sizeof(t_statut));
	base_pile->size_pile = -1; // index qui signifie que la pile est vide
	base_pile->mem_pile = mem; // la taille allouer pour pile 
	return (base_pile);
}

int empty_pile(t_pile *base_pile) {
	return (base_pile->size_pile == -1);
}

void push_pile(t_pile *base_pile, t_statut sp) {
	if (base_pile->size_pile + 1 >= base_pile->mem_pile) { // si la taille deviens egale ou superieur que la memoire allouer on double la taille de la pile
		base_pile->mem_pile *=2;
		base_pile->pile = realloc(base_pile->pile, base_pile->mem_pile * sizeof(t_statut)); // a changer pour ft_reallocarray
	}
	base_pile->pile[++base_pile->size_pile].room = sp.room;
	base_pile->pile[base_pile->size_pile].len_path = sp.len_path;
	base_pile->pile[base_pile->size_pile].pathing = malloc(sp.len_path * sizeof(int));
	for (int i = 0; i < sp.len_path; i++)
	{
		base_pile->pile[base_pile->size_pile].pathing[i] = sp.pathing[i];
	}
	
}

t_statut pop_pile(t_pile *base_pile) {
	return (base_pile->pile[base_pile->size_pile--]);
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