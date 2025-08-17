/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_pile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:34:21 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/17 15:47:46 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algo.h"
#include "../../includes/libft.h"

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
		base_pile->pile = ft_reallocarray(base_pile->pile, (base_pile->mem_pile), sizeof(t_statut), (base_pile->mem_pile /2));
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