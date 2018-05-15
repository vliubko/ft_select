/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:38:18 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:06:00 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		exit_signal(t_select *data)
{
	ft_free_select(data);
	set_default_mode(data);
	exit(0);
}

t_select	*data_keeper(t_select *dt)
{
	static t_select *data;

	if (dt)
		data = dt;
	return (data);
}

t_args		*get_args(int ac, char **av)
{
	int		i;
	t_args	*node;
	t_args	*head;

	i = 1;
	node = create_node(av[i], i);
	head = node;
	while (++i < ac)
	{
		node->next = create_node(av[i], i);
		node->next->prev = node;
		node = node->next;
	}
	node->next = head;
	head->prev = node;
	return (head);
}

int			main(int ac, char **av)
{
	t_select	data;

	if (ac < 2)
		ft_error("Usage: ./ft_select file_name...\n");
	data.length = ac - 1;
	data.args = get_args(ac, av);
	execution(data);
	return (0);
}
