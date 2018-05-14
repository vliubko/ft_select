/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:00:08 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/14 11:12:57 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	underline_space_change(t_select *data, int key)
{
	int		i;
	t_args	*list;

	list = data->args;
	i = 0;
	while (i < data->length)
	{
		if (list->underline == 1)
		{
			list->underline = 0;
			if (key == DOWN_ARROW)
				list->next->underline = 1;
			if (key == UP_ARROW)
				list->prev->underline = 1;
			if (key == SPACE)
			{
				list->underline = 0;
				list->next->underline = 1;
				list->select = (list->select == 1) ? 0 : 1;
			}
			break ;
		}
		list = list->next;
		i++;
	}
}

void	remove_arg(t_select *data)
{
	int 	i;
	t_args	*list;

	list = data->args;
	i = 0;
	while (i < data->length)
	{
		if (list->underline == 1)
		{
			ft_list_remove_node(data, list, i);
			break ;
		}
		list = list->next;
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

void	key_handler(t_select *data)
{
	int		key;

	signal(SIGWINCH, handle_winch);
	read(0, &key, 4);
//	printf("key: %d\n", key);
//	sleep(1);
	if (key == ESC || key == ESC_ALTERN)
	{
		set_default_mode(data);
		exit(0);
	}
	if (key == UP_ARROW || key == DOWN_ARROW || key == SPACE)
		underline_space_change(data, key);
	if (key == BACKSPACE || key == BACKSPACE_ALTERN || key == DEL)
		remove_arg(data);
}

void	clear_term(void)
{
	tputs(tgetstr("cl", NULL), 1, &term_putchar);
}

int		check_win_size(t_select *data, int cur_width, int max_width)
{
	if (cur_width + max_width > data->win.ws_col) {
		clear_term();
		ft_putstr_fd(RED_FONT, 2);
		ft_putendl_fd("Your window is too small to show all files.", 2);
		ft_putstr_fd("Please, resize it before doing something", 2);
		if (data->win.ws_col <= 44)
		{
			clear_term();
			ft_putstr_fd("ERROR", 2);
		}
		ft_putstr_fd(COLOR_OFF, 2);
		return (1);
	}
	return (0);
}

void	execution(t_select data)
{
	set_raw_mode(&data);
	while (42)
	{
		get_winsize(&data.win);
		data.cols = count_max_cols(&data);
		term_print_output(&data);
		key_handler(&data);
		clear_term();
	}
}
