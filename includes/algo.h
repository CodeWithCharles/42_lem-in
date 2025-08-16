/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:50:58 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/16 21:48:09 by jbergos          ###   ########.fr       */
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

typedef struct s_statut {
	int room;
	int *pathing;
	int len_path;
} t_statut;

typedef struct s_pile // gestion de pile
{
	t_statut *pile; // la pile FILO comme dans asm
	int size_pile; //montre la taille de la pile
	int mem_pile; // montre la memoire allouer a la pile doit se reallouer si size_pile est >= mem_pile 
} t_pile;


/*---------------------------------------------------------------------------------------*/
/*                                           Graph                                       */
/*---------------------------------------------------------------------------------------*/

int **create_graph(void);

int		find_link_on_rooms(
			t_room **rooms, 
			size_t size, 
			size_t idx);

		
void	show_graph(
			int **graph, 
			size_t size);
			
void	free_graph(
			int **graph, 
			size_t size);

			
/*---------------------------------------------------------------------------------------*/
/*                                           DFS                                       */
/*---------------------------------------------------------------------------------------*/
			
void 	print_ways(
			int way[], 
			int size);

void	dfs(
			int **graph, 
			int start, 
			int end, 
			t_path *res);

void	show_path(
			t_path res);

void	free_path(
			t_path path);

#endif