/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:48:28 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:06:02 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handle_winch(void)
{
	char	buf[4];

	buf[0] = -55;
	ioctl(STDERR_FILENO, TIOCSTI, buf);
}

void	handle_continue(t_select *data)
{
	clear_term();
	set_raw_mode(data);
	handle_winch();
}

void	handle_stop(t_select *data)
{
	set_default_mode(data);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\032");
}

void	sig_callback(int signo)
{
	t_select	*data;

	data = data_keeper(NULL);
	if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP ||
		signo == SIGKILL || signo == SIGQUIT)
		exit_signal(data);
	else if (signo == SIGWINCH)
		handle_winch();
	else if (signo == SIGTSTP)
		handle_stop(data);
	else if (signo == SIGCONT)
		handle_continue(data);
}

void	signals(void)
{
	signal(SIGINT, sig_callback);
	signal(SIGABRT, sig_callback);
	signal(SIGSTOP, sig_callback);
	signal(SIGKILL, sig_callback);
	signal(SIGQUIT, sig_callback);
	signal(SIGWINCH, sig_callback);
	signal(SIGTSTP, sig_callback);
	signal(SIGCONT, sig_callback);
}
