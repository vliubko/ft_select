/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:35:48 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/14 13:03:04 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_list_pushback(t_args **alst, t_args *new_node)
{
	t_args	*tmp;

	if (!new_node || !alst)
		return ;
	while (*alst && (*alst)->next)
		alst = &(*alst)->next;
	tmp = *alst;
	if (*alst)
		(*alst)->next = new_node;
	else
		*alst = new_node;
	new_node->prev = tmp;
}

void	ft_free_select(t_select *data)
{
	int 	i;
	t_args	*delete;

	i = 0;
	while (i < data->length)
	{
		delete = data->args;
		data->args = data->args->next;
		ft_strdel(&delete->value);
		free(delete);
		i++;
	}
}

void 	ft_list_remove_node(t_select *data, t_args *node_to_delete, int i)
{
	t_args *next;

	next = node_to_delete->next;
	data->length--;
	if (data->length == 0)
	{
		ft_strdel(&node_to_delete->value);
		free(node_to_delete);
		clear_term();
		ft_putstr_fd(RED_FONT, 2);
		ft_putendl_fd("You have deleted all files. Bye-bye", 2);
		sleep(1);
		set_default_mode(data);
		exit(0);
	}
	node_to_delete->prev->next = node_to_delete->next;
	node_to_delete->next->prev = node_to_delete->prev;
	node_to_delete->next->underline = 1;
	data->args = (i == 0) ? next : data->args;
	ft_strdel(&node_to_delete->value);
	free(node_to_delete);
}