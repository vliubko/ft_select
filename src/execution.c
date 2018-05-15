/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:00:08 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:19:08 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	remove_arg(t_select *data)
{
	int		i;
	t_args	*list;

	list = data->args;
	i = 0;
	while (i < data->length)
	{
		if (list->underline == 1)
		{
			remove_node(data, list, i);
			break ;
		}
		list = list->next;
		i++;
	}
}

void	return_selected(t_select *data)
{
	int		i;
	int		first;

	set_default_mode(data);
	first = 0;
	i = 0;
	while (i < data->length)
	{
		if (first && data->args->select)
			ft_putstr(" ");
		if (data->args->select)
		{
			ft_putstr(data->args->value);
			first = 1;
		}
		data->args = data->args->next;
		i++;
	}
	ft_free_select(data);
	exit(0);
}

void	key_handler(t_select *data)
{
	int		key;

	signals();
	read(0, &key, 4);
//	printf("key: %d\n", key);
//	sleep(1);
	if (key == ESC || key == ESC_ALTERN)
		exit_signal(data);
	if (key == UP_ARROW || key == DOWN_ARROW || key == SPACE ||
			key == SPACE_1 || key == LEFT_ARROW || key == RIGHT_ARROW)
		move_and_select(data, key);
	if (key == BACKSPACE || key == BACKSPACE_1 || key == DEL)
		remove_arg(data);
	if (key == ENTER || key == ENTER_1)
		return_selected(data);
}

int		check_win_size(t_select *data, int cur_width)
{
	if (cur_width + data->cols > data->win.ws_col)
	{
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
	data_keeper(&data);
	while (42)
	{
		get_winsize(&data.win);
		data.cols = count_max_size(&data);
		term_print_legend(&data);
		term_print_args(&data);
		key_handler(&data);
		clear_term();
	}
}
