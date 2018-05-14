/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:38:18 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/14 19:00:19 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	get_winsize(struct winsize *win)
{
	ioctl(0, TIOCGWINSZ, win);
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

int		count_max_cols(t_select *data)
{
	int		cols;

	cols = data->length / (data->win.ws_col - 1);
	if (!cols)
		cols = 1;
	return (cols);
}

int		term_putchar(int c)
{
	write(2, &c, 1);
	return (1);
}

int		ft_error(char *str)
{
	ft_putstr_fd(RED_FONT, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(COLOR_OFF, 2);
	exit(1);
}



int 	get_arg_type(char *value)
{
	char 		*fullpath;
	char		cur_dir[MAXPATHLEN];
	struct stat	s;
	if (value[0] != '/')
	{
		fullpath = ft_pathjoin(getcwd(cur_dir, MAXPATHLEN), value);
		if (lstat(fullpath, &s) == -1)
		{
			ft_strdel(&fullpath);
			return (-1);
		}
		ft_strdel(&fullpath);
	}
	else
	{
		if (lstat(value, &s) == -1)
			return (-1);
	}
	if (S_ISDIR(s.st_mode))
		return (1);
	if (S_ISLNK(s.st_mode))
		return (3);
	if (s.st_mode & S_IXUSR)
		return (2);
	return (0);
}

t_args	*create_node(char *name, int first)
{
	t_args	*tmp;

	tmp = (t_args*)malloc(sizeof(t_args));
	tmp->value = ft_strdup(name);
	tmp->underline = (first == 1) ? 1 : 0;
	tmp->select = 0;
	tmp->type = get_arg_type(tmp->value);
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_args	*get_args(int ac, char **av)
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

void	put_color_arg_type(t_args *node)
{
	if (node->type == -1)
		ft_putstr_fd(YELLOW_FONT, 2);
	else if (node->type == 1)
		ft_putstr_fd(CYAN_FONT, 2);
	else if (node->type == 2)
		ft_putstr_fd(RED_FONT, 2);
	else if (node->type == 3)
		ft_putstr_fd(PURPLE_FONT, 2);
}

void	select_underline_print(t_args *node)
{
	put_color_arg_type(node);
	if (node->select)
		tputs(tgetstr("so", NULL), 1, &term_putchar);
	if (node->underline)
		tputs(tgetstr("us", NULL), 1, &term_putchar);
	ft_putstr_fd(node->value, 2);
	ft_putstr_fd(COLOR_OFF, 2);
	if (node->select)
		tputs(tgetstr("se", NULL), 1, &term_putchar);
	if (node->underline)
		tputs(tgetstr("ue", NULL), 1, &term_putchar);
}

void	term_print_args(t_select *data)
{
	t_args	*node;
	int		i;
	int		row;
	int		cur_width;
	int		max_width;

	node = data->args;
	i = 0;
	cur_width = 0;
	max_width = count_max_size(data);
	write(2, tgetstr("cl", 0), strlen(tgetstr("cl", 0)));
	while (i < data->length)
	{
		row = 0;
		if (check_win_size(data, cur_width, max_width))
			break ;
		while (row < data->win.ws_row && i++ < data->length)
		{
			select_underline_print(node);
			node->row = row;
			tputs(tgoto(tgetstr("cm", NULL), cur_width, ++row), 1, &term_putchar);
			node = node->next;
		}
		cur_width += max_width + 1;
		tputs(tgoto(tgetstr("cm", NULL), cur_width, 0), 1, &term_putchar);
	}
}

t_select	*data_keeper(t_select *dt)
{
	static t_select *data;

	if (dt)
		data = dt;
	return (data);
}

void	exit_signal(t_select *data)
{
	set_default_mode(data);
	ft_free_select(data);
	exit(0);
}

void	sig_callback(int signo)
{
	t_select 	*data;

	data = data_keeper(NULL);
	clear_term();
	ft_putnbr(signo);
	sleep(2);
	if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP ||
		signo == SIGKILL || signo == SIGQUIT)
	{
//		clear_term();
//		ft_putendl("EXIT NOW!");
//		sleep(2);
		exit_signal(data);
	}

	else if (signo == SIGWINCH)
		handle_winch();
}

void	signals(void)
{
	signal(SIGINT, sig_callback);
	signal(SIGABRT, sig_callback);
	signal(SIGSTOP, sig_callback);
	signal(SIGKILL, sig_callback);
	signal(SIGQUIT, sig_callback);
	signal(SIGWINCH, sig_callback);
	signal(SIGTSTP, sig_callback);
	signal(SIGCONT, sig_callback);
}

int		main(int ac, char **av)
{
	t_select	data;

	if (ac < 2)
		ft_error("Usage: ./ft_select file_name...\n");
	data_keeper(&data);
	signals();
	data.length = ac - 1;
	data.args = get_args(ac, av);
	execution(data);
	return (0);
}
