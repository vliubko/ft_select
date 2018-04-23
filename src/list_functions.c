/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:35:48 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/23 17:35:48 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_list_pushback(t_args **alst, t_args *new_node)
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