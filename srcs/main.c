/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:44 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 01:34:45 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void			ft_prompt(void)
{
	ft_putstr(TURQUOISE);
	ft_putstr("$>");
	ft_putstr(DEFAULT);
}

struct winsize		ft_init(void)
{
	struct winsize sz;
	struct termios attributes;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		ft_putendl("<TERM> VARIABLE NOT FOUND");
	if (tgetent(NULL, name_term) == ERR)
		ft_putendl("VARIABLE NOT VALID");
	ioctl(STDERR_FILENO, TIOCGWINSZ, &sz);
	tcgetattr(0, &attributes);
	attributes.c_lflag &= ~(ICANON);
	attributes.c_lflag &= ~(ECHO);
	attributes.c_cc[VMIN] = 1;
	attributes.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attributes);
	return (sz);
}


void ft_wordleft(char *buf, t_edit *line)
{
	int i;

	i = line->cursor_pos - 3;
	if (ft_isascii(line->line[i]))
	{
		if (line->line[i] == ' ')
			while(line->line[i] == ' ')
			{
				buf[0] = 27;
				buf[1] = 91;
				buf[2] = 68;
				i--;
				ft_left_arrow(buf, line);
			}
		while (line->line[i] != ' ')
		{
			buf[0] = 27;
			buf[1] = 91;
			buf[2] = 68;
			i--;
			ft_left_arrow(buf, line);
		}
	}
}

void ft_wordright(char *buf, t_edit *line)
{
	int i;

	i = line->cursor_pos - 2;
	if (ft_isascii(line->line[i]))
	{
		if (line->line[i] == ' ')
			while(line->line[i] == ' ')
			{
				buf[0] = 27;
				buf[1] = 91;
				buf[2] = 67;
				i++;
				ft_right_arrow(buf, line);
			}
		while (line->line[i] != ' ')
		{
			buf[0] = 27;
			buf[1] = 91;
			buf[2] = 67;
			i++;
			ft_right_arrow(buf, line);
		}
	}
}

// static void ft_select_mode(t_edit *line)
// {
// 	int ret;
// 	char buf[3];
//
// 	ft_putstr("select_mode");
// 	ret = 0;
// 	line->select_mode = 1;
//
// 	while ((ret = read(0, &buf, 3)) && (buf[0] != 11 && buf[1] != 0 && buf[2] != 0))
// 	{
// 		buf[ret] = '\0';
// 		if (buf[0] == 27 && buf[1] == 91 && ((buf[2] == 67) || (buf[2] == 68)))
// 			ft_isarrow(buf, line);
// 		ft_bzero(buf, sizeof(buf));
// 	}
// 	ft_bzero(buf, sizeof(buf));
// }

static void select_on_off(t_edit *line)
{
	if (!line->select_mode)
	{
		line->select_mode = 1;
		line->start_select = line->cursor_pos - 2;
	}
}

void handle_key(char *buf, t_edit *line)
{
	if (!line->select_mode)
	{
		if (ft_isprint(buf[0]))
		{
			line->cursor_pos++;
			line->max_size++;
		}
		if ((line->cursor_pos == line->max_size) && (ft_isprint(buf[0])))
		{
			line->line = ft_freejoinstr(line->line, buf);
			ft_putchar(buf[0]);
		}
		else if ((line->cursor_pos != line->max_size) && (ft_isprint(buf[0])))
			ft_insert(buf, line);
		else if (buf[0] == 127)
			ft_delete(buf, line);
		else if (buf[0] == 5 && buf[1] == 0 && buf[2] == 0)
			ft_wordleft(buf, line);
		else if (buf[0] == 18 && buf[1] == 0 && buf[2] == 0)
			ft_wordright(buf, line);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
			ft_homekey(buf, line);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
			ft_endkey(buf, line);
	}
	if (buf[0] == 27 && buf[1] == 91 && ((buf[2] == 67) || (buf[2] == 68)))
		ft_isarrow(buf, line);
	else if (buf[0] == 11 && buf[1] == 0 && buf[2] == 0)
		select_on_off(line);
}

int				main(int ac, char **av, char **envp)
{
	char buf[3];
	(void)ac;
	(void)av;
	(void)envp;
	t_edit *line;
	int ret;
	// int tmp;

	ret = 0;
	line = ft_memalloc(sizeof(t_edit));
	ft_line_reset(line);
	line->sz = ft_init();
	line->select_mode = 0;
	line->start_select = 0;
	line->end_select = 0;
	line->is_highlight = ft_strnew(0);
	while (42)
	{
		ft_prompt();
		while ((ret = read(0, &buf, 3)) && ft_strcmp(buf, "\n"))
		{
			// ft_putnbr(buf[0]);
			// ft_putchar('\n');
			// ft_putnbr(buf[1]);
			// ft_putchar('\n');
			// ft_putnbr(buf[2]);
			// ft_putchar('\n');
			buf[ret] = '\0';
			handle_key(buf, line);
			ft_bzero(buf, sizeof(buf));
		}
		ft_putchar('\n');
		ft_putstr(line->line);
		ft_putchar('\n');
		ft_putstr("--------------------");
		ft_putchar('\n');
		ft_putstr(line->is_highlight);
		// while (line->start_select < line->end_select)
		// {
		// 	ft_putchar(line->line[line->start_select]);
		// 	line->start_select++;
		// }
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "exit"))
			exit(0);

		ft_line_reset(line);
	}
	return 0;
}
