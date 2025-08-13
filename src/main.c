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
		if (i = 0){
			rooms[i]->name = ft_strdup("start");
			rooms[i]->id = i;
			rooms[i]->link_count = 2;
			rooms[i]->type = START;
			room_link = malloc(sizeof(t_room) * (3));
			rooms[i]->links = room_link;
			rooms[i]->links[0] = rooms[5]; 
			rooms[i]->links[1] = rooms[1]; 
			rooms[i]->links[2] = NULL; 
		}
	}
	
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
	ant_farm->end = ant_farm->rooms[0];
	ant_farm->start = ant_farm->rooms[1];
	if (!fill_rooms(ant_farm->rooms)){
		free_inside_room(ant_plan, ant_farm->room_count);
		return(NULL);
	}
};


int	main(void)
{

}
