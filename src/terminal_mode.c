/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:31:26 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:06:18 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_raw_mode(t_select *data)
{
	if (!isatty(0))
		ft_error("Stdin not terminal\n");
	if (tgetent(NULL, getenv("TERM")) == -1)
		ft_error("Can't find TERM in env\n");
	if (tcgetattr(0, &data->tty) == -1)
		ft_error("Can't get attr terminal\n");
	tcgetattr(0, &data->savetty);
	data->tty.c_lflag &= ~ECHO;
	data->tty.c_lflag &= ~ICANON;
	data->tty.c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSAFLUSH, &data->tty))
		ft_error("Can't set attr terminal\n");
	tputs(tgetstr("ti", NULL), 1, &term_putchar);
	tputs(tgetstr("vi", NULL), 1, &term_putchar);
}

void	set_default_mode(t_select *data)
{
	tputs(tgetstr("ve", NULL), 1, &term_putchar);
	tputs(tgetstr("te", NULL), 1, &term_putchar);
	if (tcsetattr(0, TCSAFLUSH, &data->savetty))
		ft_error("Can't set attr terminal\n");
}
