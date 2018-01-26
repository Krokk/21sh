/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:44 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 23:25:04 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_line_reset(t_edit *line)
{
	free (line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
}

int				main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;

	char buf[3];
	t_edit *line;
	int ret;
	int i;
	t_env		*env;

	i = 0;
	ret = 0;
	env = NULL;
	line = ft_memalloc(sizeof(t_edit));
	ft_line_reset(line);
	line->sz = ft_init(line);
	while (envp[i])
		ft_push_env(&env, envp[i++]);
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
		ft_putchar('\n');
		ft_putchar('\n');
		ft_putstr("-------");
		ft_putstr(line->line);
		ft_putstr("-------");
		ft_putchar('\n');
		ft_putchar('\n');
		ft_putchar('\n');
		ft_putchar('\n');
		// ft_putstr("--------------------");
		// ft_putchar('\n');
		// ft_putstr(line->is_highlight);
		// while (line->start_select < line->end_select)
		// {
		// 	ft_putchar(line->line[line->start_select]);
		// 	line->start_select++;
		// }
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "env"))
			ft_print_env(env);
		if (ft_strequ(line->line, "exit"))
			exit(0);

		ft_line_reset(line);
	}
	return 0;
}
