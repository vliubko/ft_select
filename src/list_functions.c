/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:35:48 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:03:34 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_free_select(t_select *data)
{
	int		i;
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

void	remove_node(t_select *data, t_args *node_to_delete, int i)
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

int		get_arg_type(char *value)
{
	char		*fullpath;
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
	else if (lstat(value, &s) == -1)
		return (-1);
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
