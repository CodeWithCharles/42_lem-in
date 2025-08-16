/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:13:30 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/14 18:10:25 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	store_line(char *line);
static int	is_room_definition(const char *line);
static int	is_link_definition(const char *line);

void	parse_input(void)
{
	char	*line = NULL;
	int		next_type = ROOM;
	char	*nl_pos;

	line = get_next_line(STDIN_FILENO);
	if (!line || !ft_isdigit(line[0]))
		exit_error(ERR_BAD_ANT_CNT);
	nl_pos = ft_strchr(line, '\n');
	if (nl_pos) *nl_pos = '\0';
	store_line(line);
	g_ctx->farm->ant_count = ft_atoi(line);
	free(line);

	while ((line = get_next_line(STDIN_FILENO)))
	{
		nl_pos = ft_strchr(line, '\n');
		if (nl_pos) *nl_pos = '\0';
		store_line(line);
		if (!*line || (line[0] == '#' && line[1] != '#')) {
			free(line);
			continue;
		}
		if (!ft_strncmp(line, PRS_START, 7))
			next_type = START;
		else if (!ft_strncmp(line, PRS_END, 5))
			next_type = EXIT;
		else if (is_room_definition(line)) {
			t_room *room = parse_room_line(line, next_type, g_ctx->farm->room_count);
			add_room_to_farm(g_ctx->farm, room);
			if (next_type == START) g_ctx->farm->start = room;
			if (next_type == EXIT) g_ctx->farm->end = room;
			next_type = ROOM;
		}
		else if (is_link_definition(line))
			parse_and_add_link(g_ctx->farm, line);
		else {
			ft_printf(LOG_FMT, line);
			exit_error(ERR_BAD_LINE);
		}
		free(line);
	}
}

static void	store_line(char *line)
{
	g_ctx->input_lines = ft_reallocarray(
		g_ctx->input_lines,
		g_ctx->line_count + 2,
		sizeof(char *),
		g_ctx->line_count
	);
	g_ctx->input_lines[g_ctx->line_count++] = ft_strdup(line);
	g_ctx->input_lines[g_ctx->line_count] = NULL;
}

static int	is_room_definition(const char *line)
{
	char	**parts;
	int		count = 0;
	int		result = 0;
	char	*p;

	if (!line || *line == PRS_ANT_PFX || *line == PRS_CMT_PFX)
		return (0);
	parts = ft_split(line, ' ');
	if (!parts)
		return (0);
	while (parts[count])
		count++;
	if (count == 3)
	{
		p = parts[1];
		if (*p == '-' || *p == '+') p++;
		while (*p && ft_isdigit(*p)) p++;
		if (*p == '\0')
		{
			p = parts[2];
			if (*p == '-' || *p == '+') p++;
			while (*p && ft_isdigit(*p)) p++;
			if (*p == '\0')
				result = 1;
		}
	}
	ft_free_split(&parts);
	return (result);
}

static int	is_link_definition(const char *line)
{
	char	**parts;
	int		count = 0;
	int		result = 0;

	if (!line || *line == PRS_CMT_PFX || ft_strchr(line, ' '))
		return (0);
	parts = ft_split(line, '-');
	if (!parts)
		return (0);
	while (parts[count])
		count++;
	result = (count == 2 && parts[0][0] != '\0' && parts[1][0] != '\0');
	ft_free_split(&parts);
	return (result);
}
