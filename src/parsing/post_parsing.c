/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:30:24 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/14 17:00:21 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_original_input(void)
{
	for (size_t i = 0; i < g_ctx->line_count; i++)
	{
		ft_putendl_fd(g_ctx->input_lines[i], STDOUT_FILENO);
	}
}
