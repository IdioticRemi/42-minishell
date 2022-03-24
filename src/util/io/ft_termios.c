/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termios.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:06:45 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 15:06:59 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_termios_init(void)
{
	struct termios	attrs;

	tcgetattr(STDIN_FILENO, &attrs);
	g_shell->c_lflag = attrs.c_lflag;
	attrs.c_lflag = ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attrs);
}

void	ft_termios_revert(void)
{
	struct termios	attrs;

	tcgetattr(STDIN_FILENO, &attrs);
	attrs.c_lflag = g_shell->c_lflag;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attrs);
}
