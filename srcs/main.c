#include "../includes/sh.h"

int 			ft_errors(int code, char *cmd, char *arg)
{
	if (!cmd)
		(void)cmd;
	if (!arg)
		(void)arg;
	if (code == 1)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `<'", 2);
		return (0);
	}
	if (code == 2)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `>'", 2);
		return (0);
	}
	if (code == 3)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;;'", 2);
		return (0);
	}
	if (code == 4)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `newline'", 2);
		return (0);
	}
	if (code == 5)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;|'", 2);
		return (0);
	}
	if (code == 6)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;'", 2);
		return (0);
	}
	return (1);
}

void			ft_line_reset(t_edit *line)
{
	ft_strdel(&line->line);
	free(line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
	line->curr = NULL;
}

int 				ft_what_op_value_to_know_how_to_execute(char *str, int *i)
{
	if (str[*i] == ';')
		return (SEMICOLON);
	else if (str[*i] == '|')
	{
		if (str[*i+1] == '|')
		{
			*i += 1;
			return (DOUBLEPIPE);
		}
		return (PIPE);
	}
	else if (str[*i] == '>')
	{
		if (str[*i+1] == '>')
		{
			*i += 1;
			return(DOUBLECHEVRONRIGHT);
		}
		return (CHEVRONRIGHT);
	}
	else if (str[*i] == '<')
	{
		if (str[*i+1] == '<')
		{
			*i += 1;
			return(DOUBLECHEVRONLEFT);
		}
		return (CHEVRONLEFT);
	}
	else if (str[*i] == '&')
	{
		if (str[*i+1] == '&')
		{
			*i += 1;
			return (DOUBLESPER);
		}
		return (ESPER);
	}
	else
		return (-1);
}

int 				ft_isstrprint(char *str)
{
	int i;

	i = 0;
	while (str[++i])
		return (ft_isprint(str[i]));
	return (0);
}

t_lexit 			*ft_add_token(t_edit *line, int *i, int *j)
{
	t_lexit *tmp;

	if (!(tmp = ft_memalloc(sizeof(t_edit))))
		return (NULL);
	tmp->next = NULL;
	tmp->input = ft_strsub(line->line, *j, *i - *j);
	if (!ft_isstrprint(tmp->input))
		tmp->input = NULL;
	tmp->lexem = ft_what_op_value_to_know_how_to_execute(line->line, i);
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
		if (ft_strchr(OPERATOR, line->line[i]))
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, &i, &j);
				tmp = *lexdat;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ft_add_token(line, &i, &j);
			}
			j = i + 1;
		}
		i++;
		if (line->line[i] == '\0')
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, &i, &j);
				tmp = *lexdat;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ft_add_token(line, &i, &j);
			}
		}
		while (ft_isspace(line->line[i]))
			i++;
	}
}

void ft_print_lexdat(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (tmp)
	{
		if (tmp->input)
		{
			ft_putstr(tmp->input);
			ft_putchar('\n');
		}
		ft_putstr("LEXEM TO COME HAS VALUE : ");
		ft_putnbr(tmp->lexem);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void 				ft_free_lexdat(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (lexdat)
	{
		tmp = lexdat;
		lexdat = lexdat->next;
		ft_strdel(&tmp->input);
		free(tmp);
	}
}

int 				ft_pre_parser(t_edit *line)
{
	int i;

	i = 0;
	while (line->line[i])
	{
		if (ft_strchr(OPERATOR, line->line[i]))
		{
			if (line->line[i] == '>')
			{
				if (line->line[i+1] == '<')
					return (1);
				if (line->line[i+1] == ';')
					return (6);
			}
			if (line->line[i] == '<')
			{
				if (line->line[i+1] == '>')
					return (2);
				if (line->line[i+1] == ';')
					return (6);
			}
			if (line->line[i] == ';')
			{
				if (line->line[i+1] == ';')
					return (3);
				if (line->line[i+1] == '|')
					return (5);
			}
		}
		i++;
	}
	return (0);
}

int 				ft_parser(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (tmp)
	{
		if (tmp->lexem == 3 || tmp->lexem == 4 || tmp->lexem == 1)
		{
			if (!tmp->next->input)
				return (4);
		}
		tmp = tmp->next;
	}
	return (0);
}


// static void try_redirect(t_edit *line)
// {
// 	char **commands;
// 	pid_t pid;
//
// 	commands = ft_strsplit(line->line, ' ');
//
// 	if ((pid = fork()) == -1)
// 		ft_putstr("error forking");
// 	if (!pid)
// 	{
//
// 		execve("/bin/ls", commands, NULL);
// 	}
// 	else
// 	{
// 		waitpid(pid, NULL, 0);
// 	}
// 	ft_freearraystr(commands);
// }

int				main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;

	int buf;
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
		while ((ret = read(0, &buf, sizeof(int))) && buf != 10)
		{
			// ft_putnbr(buf);
			handle_key(buf, line);
			buf = 0;
		}
		if (ft_errors(ft_pre_parser(line), NULL, NULL))
		{
			ft_tokenize_it(line, &lexdat);
			if (ft_errors(ft_parser(lexdat), NULL, NULL))
			{
				ft_putchar('\n');
				ft_putchar('\n');
				// ft_print_lexdat(lexdat);
			}
		}
		try_redirect(line);
		ft_add_history(line); //add line to history
		ft_putchar('\n');
		ft_putstr("-------");
		ft_putstr(line->line);
		ft_putstr("-------");
		if (line->curr)
			printf("curr = %s, line = %s\n", line->curr->cmd, line->line);
		ft_putchar('\n');
		ft_putchar('\n');
		ft_free_lexdat(lexdat);
		lexdat = NULL;
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
