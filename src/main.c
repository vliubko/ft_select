/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vliubko <vliubko@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:38:18 by vliubko           #+#    #+#             */
/*   Updated: 2018/04/23 16:26:58 by vliubko          ###   ########.fr       */
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

int 	main(int ac, char **av)
{
	t_select	data;

	(void)av;
	if (ac < 2)
		ft_error("Usage: ./ft_select file_name...\n");

//	printf("%s\n", ttyname(STDIN_FILENO));
//
//	if (isatty(5))
//		printf("File Descriptor is a tty\n");
//	else
//		printf("File Descriptor is NOT a tty\n");
//	struct winsize w;
//	ioctl(0, TIOCGWINSZ, &w);
//
//	printf ("lines %d\n", w.ws_row);
//	printf ("columns %d\n", w.ws_col);
//
//	for (int i = 0; i< 1000000; i++)
//	{
//		continue ;
//	}
//

//	ft_putstr(CLEAR);
	set_raw_mode(&data);
	ft_putendl("wait 5 sec");
	sleep(5);
	ft_putendl("5 sec gone");
	set_default_mode(&data);

//	tputs(, 0, &tc_putchar);

	return (0);
}