/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:00:08 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/27 18:27:53 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


void	key_handler(t_select data)
{
	int		key;

	read(0, &key, 4);

	ft_putnbr(key);
	ft_putstr("\n");

	if (key == ESC)
	{
		set_default_mode(&data);
		exit (0);
	}
}

void	clear_term(void)
{
	tputs(tgetstr("ve", NULL), 1, &term_putchar);
}

void	execution(t_select data)
{
	while (42)
	{
		set_raw_mode(&data);
		term_print_output(data);
		key_handler(data);
		clear_term();
	}
}
