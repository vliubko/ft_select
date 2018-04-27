/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:00:08 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/27 19:51:25 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	underline_change(t_select *data, int key)
{
	if (key == UP_ARROW)
	{
		data->args->prev->underline = 1;
		data->args->underline = 0;
	}
	if (key == DOWN_ARROW)
	{
		data->args->prev->underline = 0;
		data->args->underline = 1;
	}
	if (key == SPACE)
	{
		data->args->select = (data->args->select == 1) ? 0 : 1;
	}
}

void	key_handler(t_select data)
{
	int		key;

	read(0, &key, 4);

	if (key == ESC)
	{
		set_default_mode(&data);
		exit (0);
	}
	else if (key == UP_ARROW || key == DOWN_ARROW || key == SPACE)
		underline_change(&data, key);
}

void	clear_term(void)
{
	tputs(tgetstr("cl", NULL), 1, &term_putchar);
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
