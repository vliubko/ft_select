/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:38:18 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/27 18:02:31 by vliubko          ###   ########.fr       */
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
	t_args	*args;
	t_args	*node;

	i = 1;
	while(i < ac)
	{
		node = create_node(av[i], i);
		ft_list_pushback(&args, node);
		i++;
	}
	return (args);
}

void	term_print_output(t_select data)
{
	t_args	*tmp;

	tmp = data.args;
	while (tmp)
	{
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}

int 	main(int ac, char **av)
{
	t_select	data;

	if (ac < 2)
		ft_error("Usage: ./ft_select file_name...\n");
	data.args = get_args(ac, av);
	execution(data);

	return (0);
}