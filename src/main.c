/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:38:18 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/27 19:49:00 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void 	handle_winch(int sig)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	if (sig == SIGWINCH)
	{
		printf ("lines %d\n", w.ws_row);
		printf ("columns %d\n", w.ws_col);
	}
}

int		term_putchar(int c)
{
	write(2, &c, 1);
	return (1);
}

int 	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (1);
}

t_args	*create_node(char *name, int first)
{
	t_args	*tmp;

	tmp = (t_args*)malloc(sizeof(t_args));
	tmp->value = ft_strdup(name);
	tmp->underline = (first == 1) ? 1 : 0;
	tmp->select = 0;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_args	*get_args(int ac, char **av)
{
	int 	i;
	t_args	*node;
	t_args	*head;

	i = 1;
	node = create_node(av[i], i);
	head = node;
	while(++i < ac)
	{
		node->next = create_node(av[i], i);
		node->next->prev = node;
		node = node->next;
	}
	node->next = head;
	head->prev = node;
	return (head);
}

void 	select_underline_print(t_args *node)
{
	if (node->select)
		tputs(tgetstr("so", NULL), 1, &term_putchar);
	if (node->underline)
		tputs(tgetstr("us", NULL), 1, &term_putchar);
	ft_putendl(node->value);
	if (node->select)
		tputs(tgetstr("se", NULL), 1, &term_putchar);
	if (node->underline)
		tputs(tgetstr("ue", NULL), 1, &term_putchar);
}

void	term_print_output(t_select data)
{
	t_args	*node;
	int 	i;

	node = data.args;
	i = 0;
	while (i < data.length)
	{
		select_underline_print(node);
		node = node->next;
		i++;
	}
}

int 	main(int ac, char **av)
{
	t_select	data;

	if (ac < 2)
		ft_error("Usage: ./ft_select file_name...\n");
	data.args = get_args(ac, av);
	data.length = ac - 1;
	execution(data);

	return (0);
}