/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:38:15 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:04:03 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	moves_up_down(t_args *node, int key)
{
	if (key == DOWN_ARROW)
		node->next->underline = 1;
	if (key == UP_ARROW)
		node->prev->underline = 1;
}

void	moves_right_left(t_args *node, int key)
{
	t_args	*list;
	int		row_to_find;

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

void	move_and_select(t_select *data, int key)
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
