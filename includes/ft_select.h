/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:40:30 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/27 18:49:46 by vliubko          ###   ########.fr       */
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

typedef struct		s_args
{
	char			*value;
	int 			select;
	int 			underline;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

typedef struct		s_select
{
	int 			length;
	struct termios	tty;
	struct termios	savetty;
	struct winsize	win;
	struct s_args	*args;
}					t_select;

# define 	CLEAR "\033[H\033[2J"
# define 	ESC 32539
# define 	ESC_ALTERN 27
# define	BACKSPACE	127
# define	ENTER		10
# define	SPACE		32544
# define	DEL		2117294875
# define	UP_ARROW	4283163
# define	DOWN_ARROW	4348699

void	ft_list_pushback(t_args **alst, t_args *new_node);
void	execution(t_select data);
void	set_default_mode(t_select *data);
void	set_raw_mode(t_select *data);
int		term_putchar(int c);
void	term_print_output(t_select *data);
int 	ft_error(char *str);

#endif
