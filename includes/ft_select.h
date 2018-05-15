/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:40:30 by vliubko           #+#    #+#             */
/*   Updated: 2018/05/15 12:08:14 by vliubko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <sys/stat.h>
# include <sys/param.h>


typedef struct		s_args
{
	char			*value;
	int 			select;
	int 			underline;
	int 			type;
	int 			row;
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
	int 			cols;
}					t_select;

# define 	BLUE_FONT "\e[38;5;69m"
# define 	RED_FONT "\033[1;31m"
# define 	CYAN_FONT "\e[1;36m"
# define 	GREEN_FONT "\e[38;5;46m"
# define 	PURPLE_FONT "\e[1;35m"
# define 	YELLOW_FONT "\e[38;5;226m"
# define 	COLOR_OFF "\e[0m"
# define 	CLEAR "\033[H\033[2J"
# define 	ESC 		32539
# define 	ESC_ALTERN	27
# define	BACKSPACE	127
# define 	BACKSPACE_1 32639
# define	DEL			2117294875
# define	ENTER		10
# define 	ENTER_1		32522
# define	SPACE		32544
# define	SPACE_1		32
# define	UP_ARROW	4283163
# define	DOWN_ARROW	4348699
# define 	LEFT_ARROW	4479771
# define 	RIGHT_ARROW	4414235

void	ft_list_pushback(t_args **alst, t_args *new_node);
void 	ft_list_remove_node(t_select *data, t_args *node, int i);
void	execution(t_select data);
void	set_default_mode(t_select *data);
void	set_raw_mode(t_select *data);
int		term_putchar(int c);
void	term_print_args(t_select *data);
int 	ft_error(char *str);
int 	count_max_cols(t_select *data);
int		count_max_size(t_select *data);
void	get_winsize(struct winsize *win);
int		check_win_size(t_select *data, int cur_width, int max_width);
void	clear_term(void);
void	ft_free_select(t_select *data);
void	handle_winch(void);
void	signals(void);
void	sig_callback(int signo);


#endif
