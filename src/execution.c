	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:00:08 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/14 13:38:45 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void 	moves_up_down (t_args *node, int key)
{
	if (key == DOWN_ARROW)
		node->next->underline = 1;
	if (key == UP_ARROW)
		node->prev->underline = 1;
}

void	moves_right_left(t_args *node, int key)
{
	t_args	*list;
	int 	row_to_find;

	list = node;
	row_to_find = list->row;
	if (key == RIGHT_ARROW)
	{
		list = list->next;
		while (list->row != row_to_find)
			list = list->next;
	}
	if (key == LEFT_ARROW)
	{
		list = list->prev;
		while (list->row != row_to_find)
			list = list->prev;
	}
	if (key == LEFT_ARROW || key == RIGHT_ARROW)
		list->underline = 1;
}

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
			moves_up_down(list, key);
			moves_right_left(list, key);
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

void	handle_winch(void)
{
	char	buf[4];

	buf[0] = -55;
	ioctl(STDERR_FILENO, TIOCSTI, buf);
}

void	return_selected(t_select *data)
{
	int 	i;
	int 	first;

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

	read(0, &key, 4);
//	printf("key: %d\n", key);
//	sleep(1);
	if (key == ESC || key == ESC_ALTERN)
	{
		ft_free_select(data);
		set_default_mode(data);
		exit(0);
	}
	if (key == UP_ARROW || key == DOWN_ARROW || key == SPACE ||
			key == SPACE_1 || key == LEFT_ARROW || key == RIGHT_ARROW)
		underline_space_change(data, key);
	if (key == BACKSPACE || key == BACKSPACE_1 || key == DEL)
		remove_arg(data);
	if (key == ENTER || key == ENTER_1)
		return_selected(data);
}

void	clear_term(void)
{
	tputs(tgetstr("cl", NULL), 1, &term_putchar);
}

int		check_win_size(t_select *data, int cur_width, int max_width)
{
	if (cur_width + max_width > data->win.ws_col)
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
	while (42)
	{
		get_winsize(&data.win);
		data.cols = count_max_cols(&data);
		term_print_args(&data);
		key_handler(&data);
		clear_term();
	}
}
