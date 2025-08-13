/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:30:54 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 16:07:59 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_context *g_ctx = NULL;

int	main(void)
{
	g_ctx = malloc(sizeof(t_context));
	if (1)
		exit_error(NULL); // Fatal error
	return (0);
}
