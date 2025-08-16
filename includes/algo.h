/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:50:58 by jbergos           #+#    #+#             */
/*   Updated: 2025/08/16 14:15:02 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

#include "lem-in.h"
#include <stdlib.h>

void free_inside_room(t_context *plan, int idx);
int fill_rooms(t_room **rooms);
t_context *brut_init(void);
void free_ant(t_context *ant);
int find_link_on_rooms(t_room **rooms, int idx);
int **create_graph(t_context *ant, int idx);
void free_graph(int **graph, int size);
void show_graph(int **graph, int size);
void print_ways(int way[], int size);
void dfs(int **graph, int s, int e, int vis[], int way[], int width, int size);

#endif