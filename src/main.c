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

void	get_winsize(struct winsize *win)
{
	ioctl(0, TIOCGWINSZ, win);
}

int 	count_max_size(t_select *data)
{
	t_args			*list;
	int 			current_node_size;
	int				max_size;
	int 		i;

	i = 0;
	list = data->args;
	max_size = 0;
	while (i < data->win.ws_row)
	{
		current_node_size = ft_strlen(list->value);
		if (current_node_size > max_size)
			max_size = current_node_size;
		i++;
		list = list->next;
	}
	return (max_size);
}

int 	count_max_cols(t_select *data)
{
	int		cols;

	cols = data->length / (data->win.ws_col - 1);
	if (!cols)
		cols = 1;
	return(cols);
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
	ft_putstr(node->value);
	if (node->select)
		tputs(tgetstr("se", NULL), 1, &term_putchar);
	if (node->underline)
		tputs(tgetstr("ue", NULL), 1, &term_putchar);
}

void	term_print_output(t_select *data)
{
	t_args	*node;
	int 	i;
	int 	row;
	int 	cur_width;
	int 	max_width;

	node = data->args;
	i = 0;
	cur_width = 0;
	max_width = count_max_size(data);
	write(2, tgetstr("cl", 0), strlen(tgetstr("cl", 0)));
	while (i < data->length)
	{
		row = 0;
		while (row < data->win.ws_row && i++ < data->length)
		{
			select_underline_print(node);
			tputs(tgoto(tgetstr("cm", NULL), cur_width, ++row), 1, &term_putchar);
			node = node->next;
		}
		cur_width += max_width + 1;
		tputs(tgoto(tgetstr("cm", NULL), cur_width, 0), 1, &term_putchar);
	}
//	ft_putstr("ws_col: ");
//	ft_putnbr(data->win.ws_col);
//	ft_putendl("");
//	ft_putstr("ws_row: ");
//	ft_putnbr(data->win.ws_row);
//	ft_putendl("");
}

int 	main(int ac, char **av)
{
	t_select	data;

	if (ac < 2)
		ft_error("Usage: ./ft_select file_name...\n");
	data.args = get_args(ac, av);
	data.length = ac - 1;
	get_winsize(&data.win);
	data.cols = count_max_cols(&data);
	execution(data);

	return (0);
}