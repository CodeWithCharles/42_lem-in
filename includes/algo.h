/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:50:58 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/22 16:53:36 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

#include "lem-in.h"
#include <stdlib.h>

typedef struct s_path
{
	int **list_paths;
	int *length_paths;
	int nb;
} t_path;

typedef struct s_path_comb{
	t_path **combined_paths;
	int nb;
} t_path_comb;

typedef struct s_path_combined
{
	int **list_paths;
	int *length_paths;
	int *possible_paths;
	int nb_path;
	int nb;
	int nb_rooms;
	int rooms_taken;
	int *rooms;
} t_path_combined;

typedef struct s_statut {
	int room;
	int *pathing;
	int len_path;
} t_statut;

typedef struct s_path_pile {
	t_path_combined *pile;
	int size_pile;
	int mem_pile;
} t_path_pile;

typedef struct s_pile // gestion de pile
{
	t_statut *pile; // la pile FILO comme dans asm
	int size_pile; //montre la taille de la pile
	int mem_pile; // montre la memoire allouer a la pile doit se reallouer si size_pile est >= mem_pile 
} t_pile;


/*---------------------------------------------------------------------------------------*/
/*                                           Graph                                       */
/*---------------------------------------------------------------------------------------*/

int			**create_graph(void);

int			find_link_on_rooms(
				t_room **rooms, 
				size_t size, 
				size_t idx);

		
void		show_graph(
				int **graph, 
				size_t size);
			
void		free_graph(
				int **graph, 
				size_t size);

/*---------------------------------------------------------------------------------------*/
/*                                           DFS_pile                                    */
/*---------------------------------------------------------------------------------------*/

t_pile		*create_pile(
				int mem);

int			empty_pile(
				t_pile *base_pile);

void		push_pile(
				t_pile *base_pile,
				t_statut sp);

t_statut	pop_pile(
				t_pile *base_pile);
		
/*---------------------------------------------------------------------------------------*/
/*                                           DFS                                         */
/*---------------------------------------------------------------------------------------*/

void	dfs(
			int **graph, 
			int start, 
			int end, 
			t_path *res);

void 	add_path(
			t_path *res,
			int *pathing,
			int size_pathing);

void	show_path(
			t_path res);

void	free_path(
			t_path path);

/*---------------------------------------------------------------------------------------*/
/*                                           PATH_PILE                                   */
/*---------------------------------------------------------------------------------------*/

t_path_pile			*create_pile_path(
						int mem);

int 				empty_path_pile(
						t_path_pile *base_pile);

void				push_path_pile(
						t_path_pile *base_pile,
						t_path_combined sp);

t_path_combined		pop_path_pile(
						t_path_pile *base_pile);

#endif