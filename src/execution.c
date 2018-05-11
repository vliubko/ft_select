/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:00:08 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/11 11:59:49 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	underline_space_change(t_select *data, int key)
{
	int		i;

	i = 0;
	while (i < data->length)
	{
		if (data->args->underline == 1)
		{
			data->args->underline = 0;
			if (key == DOWN_ARROW)
				data->args->next->underline = 1;
			if (key == UP_ARROW)
				data->args->prev->underline = 1;
			if (key == SPACE)
			{
				data->args->underline = 0;
				data->args->next->underline = 1;
				data->args->select = (data->args->select == 1) ? 0 : 1;
			}
			break ;
		}
		data->args = data->args->next;
		i++;
	}
}

void	handle_winch(int sig)
{
	char	buf[4];

	if (sig == SIGWINCH)
	{
		buf[0] = -55;
		ioctl(STDERR_FILENO, TIOCSTI, buf);
	}
}

void	key_handler(t_select data)
{
	int		key;

	signal(SIGWINCH, handle_winch);
	read(0, &key, 4);
//	printf("key: %d\n", key);
//	sleep(1);
	if (key == ESC || key == ESC_ALTERN)
	{
		set_default_mode(&data);
		exit(0);
	}
	if (key == UP_ARROW || key == DOWN_ARROW || key == SPACE)
		underline_space_change(&data, key);
}

void	clear_term(void)
{
	tputs(tgetstr("cl", NULL), 1, &term_putchar);
}

void	execution(t_select data)
{
	set_raw_mode(&data);
	while (42)
	{
		get_winsize(&data.win);
		data.cols = count_max_cols(&data);
		term_print_output(&data);
		key_handler(data);
		clear_term();
	}
}
