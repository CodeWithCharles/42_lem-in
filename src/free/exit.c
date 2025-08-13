/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:21:38 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 15:32:47 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	exit_error(const char *msg)
{
	if (msg && *msg)
		fd_printf(2, ERROR_FMT, (char *)msg);
	else
		fd_printf(2, ERROR_FMT, (char *)ERR_FATAL);
	if (g_ctx)
		free_context(g_ctx);
	exit(EXIT_FAILURE);
}
