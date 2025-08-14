/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:54 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 14:31:10 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/lem-in.h"
#include <stdio.h>

void free_inside_room(t_context *plan, int idx){
	for (int i = 0; i < idx; i++)
	{
		free(plan->farm->rooms[i]);
	}
	free(plan->farm);
	free(plan);
	return ;
}

int fill_rooms(t_room **rooms){
	for (int i = 0; i < 8; i++)
	{
		t_room **room_link;
		if (i == 0){
			rooms[i]->name = ft_strdup("start");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = START;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[4];
			rooms[i]->links[1] = rooms[2]; 
			rooms[i]->links[2] = NULL; 
		}
		if (i == 1){
			rooms[i]->name = ft_strdup("end");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = EXIT;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[7];
			rooms[i]->links[1] = rooms[3]; 
			rooms[i]->links[2] = NULL; 
		}
		if (i == 2){
			rooms[i]->name = ft_strdup("1");
			rooms[i]->id = i;
			rooms[i]->link_count = 3;
			rooms[i]->type = ROOM;
			room_link = malloc(sizeof(t_room) * (4));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[0];
			rooms[i]->links[1] = rooms[6]; 
			rooms[i]->links[2] = rooms[3]; 
			rooms[i]->links[3] = NULL; 
		}
		if (i == 3){
			rooms[i]->name = ft_strdup("2");
			rooms[i]->id = i;
			rooms[i]->link_count = 3;
			rooms[i]->type = ROOM;
			room_link = malloc(sizeof(t_room) * (4));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[2];
			rooms[i]->links[1] = rooms[5];
			rooms[i]->links[2] = rooms[1];  
			rooms[i]->links[3] = NULL; 
		}
		if (i == 4){
			rooms[i]->name = ft_strdup("3");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = ROOM;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[0];
			rooms[i]->links[1] = rooms[5];  
			rooms[i]->links[2] = NULL; 
		}
		if (i == 5){
			rooms[i]->name = ft_strdup("4");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = ROOM;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[4];
			rooms[i]->links[1] = rooms[3]; 
			rooms[i]->links[2] = NULL; 
		}
		if (i == 6){
			rooms[i]->name = ft_strdup("5");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = ROOM;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[2];
			rooms[i]->links[1] = rooms[7];  
			rooms[i]->links[2] = NULL; 
		}
		if (i == 7){
			rooms[i]->name = ft_strdup("6");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = ROOM;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[1];
			rooms[i]->links[1] = rooms[6];  
			rooms[i]->links[2] = NULL; 
		}
	}
	return (1);
}

t_context	*brut_init(void){
	t_context *ant_plan;
	t_farm *ant_farm;
	t_room **all_rooms;

	ant_plan = malloc(sizeof(t_context));
	if (!ant_plan)
		return (NULL);
	ant_farm = malloc(sizeof(t_farm));
	if (!ant_farm){
		free(ant_plan);
		return (NULL);
	}
	ant_plan->farm = ant_farm;
	ant_farm->ant_count = 10;
	ant_farm->room_count = 8;
	all_rooms = malloc(sizeof(t_room*) * (ant_farm->room_count + 1));
	if (!all_rooms){
		free(ant_plan);
		free(ant_farm);
		return (NULL);
	}
	ant_farm->rooms = all_rooms;
	for (int i = 0; i < ant_farm->room_count + 1; i++)
	{
		t_room *new_room;
		if (i == ant_farm->room_count)
			ant_farm->rooms[i] = NULL;
		else {
			new_room = malloc(sizeof(t_room));
			if (!new_room)
			{
				free_inside_room(ant_plan, i);
				return (NULL);
			}
			ant_farm->rooms[i] = new_room;
		}
	}
	ant_farm->end = ant_farm->rooms[1];
	ant_farm->start = ant_farm->rooms[0];
	if (!fill_rooms(ant_farm->rooms)){
		free_inside_room(ant_plan, ant_farm->room_count);
		return(NULL);
	}
	return (ant_plan);
};

void free_ant(t_context *ant){
	int i = 0;

	while (ant->farm->rooms[i])
	{
		free(ant->farm->rooms[i]->name);
		free(ant->farm->rooms[i]->links);
		free(ant->farm->rooms[i]);
		++i;
	}
	free(ant->farm->rooms);
	free(ant->farm);
	free(ant);
}

int find_link_on_rooms(t_room **rooms, int idx){
	for (int i = 0; rooms[i]; i++)
	{
		if (rooms[i]->id == idx)
			return (1);
	}
	return (0);
}

int **create_graph(t_context *ant, int idx){
	int **new_graph;

	new_graph = malloc(sizeof(int *) * (idx));
	if (!new_graph)
		return (NULL);
	for (int i = 0; i < idx; i++)
	{
		new_graph[i] = malloc(sizeof(int) * (idx));
	}
	for (int i = 0; i < idx; i++)
	{
		for (int j = 0; j < idx; j++)
		{
			if (i == j)
				new_graph[i][j] = 0;
			else {
				new_graph[i][j] = find_link_on_rooms(ant->farm->rooms[i]->links, j);
			}
		}
	}
	return (new_graph);
}

void free_graph(int **graph, int size){
	for (int i = 0; i < size; i++)
	{
		free(graph[i]);
	}
	free(graph);
}

void show_graph(int **graph, int size){
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			printf("    |%d|", i);
		else 
			printf("|%d|", i);
	}
	printf("\n");
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == 0)
				printf("|%d| ", i);
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

void dfs(int **graph, int s, int e, int vis[], int way[], int width, int size){
	vis[s] = 1;
	way[width] = s;
	width++;

	if (s == e) {
		print_ways(way, width);
	} else {
		for (int i = 0; i < size; i++)
		{
			if (graph[s][i] == 1 && !vis[i]){
				dfs(graph, i, e, vis, way, width, size);
			}
		}
	}

	width--;
	vis[s] = 0;
}

int	main(void)
{
	t_context *test;
	test = brut_init();
	int i = 0;
	while (test->farm->rooms[i])
	{
		printf("rooms name : %s\n", test->farm->rooms[i]->name);
		for (int j = 0; test->farm->rooms[i]->links[j]; j++)
		{
	 		printf("----- Linked rooms to her : %s\n", test->farm->rooms[i]->links[j]->name);
		}
	++i;
 	}
 	int **graph;
 	graph = create_graph(test, test->farm->room_count);
	show_graph(graph, test->farm->room_count);
	int visited[8] = {0};
	int way[8];
	printf("all way to %s at %s\n", test->farm->start->name, test->farm->end->name);
	dfs(graph, 4, 0, visited, way, 0, test->farm->room_count);
	free_graph(graph, test->farm->room_count);
 	free_ant(test);
 	return (0);
}
