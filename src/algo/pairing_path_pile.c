/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing_path_pile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:45:55 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/22 16:08:25 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

t_path_pile *create_pile_path(int mem) {
	t_path_pile *base_pile = malloc(sizeof(t_path_pile));
	base_pile->pile = malloc(malloc(mem * sizeof(t_path_combined)));
	base_pile->size_pile = -1;
	base_pile->mem_pile = mem;
	return (base_pile);
}

int empty_path_pile(t_path_pile *base_pile) {
	return (base_pile->size_pile == -1);
}

void push_path_pile(t_path_pile *base_pile, t_path_combined sp) {
	if (base_pile->size_pile + 1 >= base_pile->mem_pile) {
		base_pile->mem_pile *= 2;
		base_pile->pile = ft_reallocarray(base_pile->pile, (base_pile->mem_pile), sizeof(t_path_combined), (base_pile->mem_pile / 2));
	}
	base_pile->pile[++base_pile->size_pile].list_paths = malloc(sizeof(int*) * (sp.nb));
	for (int i = 0; i < sp.nb; i++)
	{
		base_pile->pile[base_pile->size_pile].list_paths[i] = malloc(sizeof(int) * (sp.length_paths[i]));
		for (int j = 0; j < sp.length_paths[i]; j++)
		{
			base_pile->pile[base_pile->size_pile].list_paths[i][j] = sp.list_paths[i][j];
		}
	}
	base_pile->pile[base_pile->size_pile].length_paths = malloc(sizeof(int) * sp.nb);
	for (int i = 0; i < sp.nb; i++)
	{
		base_pile->pile[base_pile->size_pile].length_paths[i] = sp.length_paths[i];
	}
	base_pile->pile[base_pile->size_pile].possible_paths = malloc(sizeof(int) * sp.nb_path);
	for (int i = 0; i < sp.nb_path; i++)
	{
		base_pile->pile[base_pile->size_pile].possible_paths[i] = sp.possible_paths[i];
	}
	base_pile->pile[base_pile->size_pile].nb_path = sp.nb_path;
	base_pile->pile[base_pile->size_pile].nb = sp.nb;
	base_pile->pile[base_pile->size_pile].nb_rooms = sp.nb_rooms;
	base_pile->pile[base_pile->size_pile].rooms = malloc(sizeof(int) * sp.nb_rooms);
	for (int i = 0; i < sp.nb_rooms; i++)
	{
		base_pile->pile[base_pile->size_pile].rooms[i] = sp.rooms[i];
	}
	base_pile->pile[base_pile->size_pile].rooms_taken = sp.rooms_taken;
}

t_path_combined pop_path_pile(t_path_pile *base_pile) {
	return (base_pile->pile[base_pile->size_pile--]);
}