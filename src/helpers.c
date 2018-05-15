/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:41:36 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:05:11 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	get_winsize(struct winsize *win)
{
	ioctl(0, TIOCGWINSZ, win);
}

void	clear_term(void)
{
	tputs(tgetstr("cl", NULL), 1, &term_putchar);
}

int		count_max_cols(t_select *data)
{
	int		cols;

	cols = data->length / (data->win.ws_col - 1);
	if (!cols)
		cols = 1;
	return (cols);
}

int		count_max_size(t_select *data)
{
	t_args	*list;
	int		current_node_size;
	int		max_size;
	int		i;

	i = 0;
	list = data->args;
	max_size = 0;
	while (i < data->length)
	{
		current_node_size = ft_strlen(list->value);
		if (current_node_size > max_size)
			max_size = current_node_size;
		i++;
		list = list->next;
	}
	return (max_size);
}

int		ft_error(char *str)
{
	ft_putstr_fd(RED_FONT, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(COLOR_OFF, 2);
	exit(1);
}
