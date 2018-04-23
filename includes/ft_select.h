/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:40:30 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/23 13:35:42 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
//# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>
//# include <sys/param.h>
# include <term.h>
# include <curses.h>

typedef struct		s_select
{
	struct termios	tty;
	struct termios	savetty;
	struct winsize	win;
}					t_select;

# define CLEAR "\033[H\033[2J"

void	set_default_mode(t_select *data);
void	set_raw_mode(t_select *data);
int		term_putchar(int c);
int 	ft_error(char *str);


#endif
