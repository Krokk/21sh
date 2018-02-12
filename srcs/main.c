/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:44 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/26 08:07:25 by rfabre           ###   ########.fr       */
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
	line->curr = NULL;
}

t_lexit 			*ft_add_token(t_edit *line, int i)
{
	t_lexit *tmp;

	if (!(tmp = ft_memalloc(sizeof(t_edit))))
		return (NULL);
	tmp->next = NULL;
	if (!line->line)
		tmp->input = NULL;
	else
	{
		tmp->input = ft_strndup(line->line, i);
		tmp->lex = 0;
	}
	return (tmp);
}

void 				ft_tokenize_it(t_edit *line, t_lexit **lexdat)
{
	int i;
	int j;
	t_lexit *tmp;

	i = 0;
	j = 0;
	tmp = *lexdat;
	while (line->line[i])
	{
		if (line->line[i] == ';' || line->line[i] == '|' || line->line[i] == '>' || line->line[i] == '<' || line->line[i] == '\0')
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, i);
				// ft_putstr((*lexdat)->input);
				ft_putnbr(j);
				j++;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				ft_putstr("cocou");
				tmp->next = ft_add_token(line, i);
			}
		}
		i++;
	}
}

void ft_print_lexdat(t_lexit *lexdat)
{
	// while (lexdat)
	// {
		ft_putstr(lexdat->input);
		// ft_putchar('\n');
		// ft_putchar('\n');
		// ft_putchar('\n');
		// ft_putchar('\n');
		// lexdat = lexdat->next;
	// }
}

int				main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;

	char buf[3];
	t_edit *line;
	t_lexit *lexdat;
	int ret;
	int i;
	t_env		*env;
	i = 0;
	ret = 0;
	env = NULL;
	lexdat = NULL;
	line = ft_memalloc(sizeof(t_edit));
	line->hstr = NULL;
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
		ft_tokenize_it(line, &lexdat);
		ft_add_history(line); //add line to history
		ft_putchar('\n');
		ft_putchar('\n');
		ft_putchar('\n');
		ft_putstr("-------");
		ft_putstr(line->line);
		ft_putstr("-------");
		if (line->curr)
			printf("curr = %s, line = %s\n", line->curr->cmd, line->line);
		ft_putchar('\n');
		ft_putchar('\n');
		ft_print_lexdat(lexdat);
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
