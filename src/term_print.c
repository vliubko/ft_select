/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:43:46 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 17:36:47 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		term_putchar(int c)
{
	write(2, &c, 1);
	return (1);
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

void	term_print_legend(t_select *data)
{
	int		col;

	ft_putstr_fd(BG_COLOR, 2);
	tputs(tgoto(tgetstr("cm", NULL), 0, data->win.ws_row), 1, &term_putchar);
	ft_putstr_fd(BOLD_WHINE_FONT, 2);
	ft_putstr_fd("Welcome to ft_select by vliubko. Nice to meet you, @xlogin", 2);
	col = 58;
	while (col++ < data->win.ws_col)
		ft_putstr_fd(" ", 2);
	ft_putstr_fd(COLOR_OFF, 2);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, &term_putchar);
}

void	term_print_args(t_select *data)
{
	t_args	*node;
	int		i;
	int		row;
	int		width;

	node = data->args;
	i = 0;
	width = 0;
	while (i < data->length)
	{
		row = 0;
		if (check_win_size(data, width))
			break ;
		while (row < data->win.ws_row - 2 && i++ < data->length)
		{
			select_underline_print(node);
			node->row = row;
			tputs(tgoto(tgetstr("cm", NULL), width, ++row), 1, &term_putchar);
			node = node->next;
		}
		width += data->cols + 1;
		tputs(tgoto(tgetstr("cm", NULL), width, 0), 1, &term_putchar);
	}
}
