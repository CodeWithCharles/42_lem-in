/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:23:20 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/13 16:14:52 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* -------------------------------------------------------------------------- */
/*                                   Colors                                   */
/* -------------------------------------------------------------------------- */

#define TERM_RESET		"\033[0m"
#define TERM_BLACK		"\033[0;30m"
#define TERM_RED		"\033[0;31m"
#define TERM_GREEN		"\033[0;32m"
#define TERM_YELLOW		"\033[0;33m"
#define TERM_BLUE		"\033[0;34m"
#define TERM_MAGENTA	"\033[0;35m"
#define TERM_CYAN		"\033[0;36m"
#define TERM_GRAY		"\033[0;37m"
#define TERM_NULL		"\033[0m"

/* -------------------------------------------------------------------------- */
/*                                 Logs prefix                                */
/* -------------------------------------------------------------------------- */

#define ERROR			"[ERROR]"
#define WARNING			"[WARNING]"
#define LOG				"[LOG]"

/* -------------------------------------------------------------------------- */
/*                                 Log formats                                */
/* -------------------------------------------------------------------------- */

#define ERROR_FMT		TERM_RED"[LEM-IN]"ERROR" | %s\n"TERM_RESET
#define WARNING_FMT		TERM_YELLOW"[LEM-IN]"WARNING" | %s\n"TERM_RESET
#define LOG_FMT			TERM_BLUE"[LEM-IN]"LOG" | %s\n"TERM_RESET

/* -------------------------------------------------------------------------- */
/*                                   Errors                                   */
/* -------------------------------------------------------------------------- */

#define ERR_FATAL		"Fatal Error"
#define ERR_BAD_ROOM	"Invalid room definition"
#define ERR_FIND_ROOM	"Unknown room name"
#define ERR_BAD_LINK	"Invalid link definition"
