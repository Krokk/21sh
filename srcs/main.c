/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/12 21:13:34 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void					ft_setvalues(t_edit *line, t_norm *values)
{
	line->hstr = NULL;
	ft_line_reset(line);
	line->sz = ft_init(line);
	values->buf = 0;
	values->i = 0;
	values->ret = 0;
}

void				ft_print_tree(t_lexit *lexdat)
{
	int			i;

	i = 1;
	if (lexdat)
	{
		if (lexdat->left)
			ft_print_tree(lexdat->left);
		if (lexdat->right)
			ft_print_tree(lexdat->right);
			// PRINT SELON ORDER
	}
}


//
// int main()
// {
//     int ls_pid; /* The new process id for ls*/
//     char *const ls_params[] = {"/bin/ls", NULL}; /* for ls */
//     int file; /* file for writing */
//
//     /* Open file check user permissions */
//     if (file = open("outfile", O_WRONLY|O_CREAT) == -1) /* , S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP */
//     {
//         perror("Failed to open file");
//         _exit(EXIT_FAILURE);
//     }
//
//     ls_pid = fork(); /* Create new process for ls */
//
//     if (ls_pid == -1) /* error check */
//     {
//         perror("Error forking ls (pid == -1)");
//         _exit(EXIT_FAILURE);
//     }
//     else if (ls_pid == 0) /* Child of ls */
//     {
//         /* Redirect output to file */
//         if (dup2(file, STDOUT_FILENO) == -1) /* STDOUT_FILENO = 1 */
//         {
//             perror("Error duping to file");
//             _exit(EXIT_FAILURE);
//         }
//         close(file);
//
//         execvp("ls", ls_params); /* create the sort process */
//         /* execlp("ls", "ls", NULL); */
//
//         /* if this does not end the program, something is wrong */
//         perror("Exec failed at sort");
//         _exit(EXIT_FAILURE);
//     }
//     else /* ls parent (1) */
//     {
//         /* wait for child */
//         if (wait(NULL) == -1)
//         {
//             perror("fork failed on parent");
//             _exit(EXIT_FAILURE);
// 	}}}

void handle_redir(char *redirection, t_env *env, t_lexit *lexdat)
{
	int 		file;
	int     in;
	int     save_out;
	int     save_in;

	ft_putstr("left");
	ft_putstr(lexdat->left->input);
	ft_putstr("|right");
	ft_putstr(lexdat->right->input);
	ft_putchar('\n');
	save_out = dup(STDOUT_FILENO);
	save_in = dup(STDIN_FILENO);
	if (ft_strequ(redirection, ">"))
	{

		if ((file = open(lexdat->right->input, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			ft_putstr("OPEN ERROR");
		if (dup2(file, STDOUT_FILENO) == -1) /* STDOUT_FILENO = 1 */
			ft_putstr("ERROR DUP");
		ft_putstr("3");
		close(file);
		ft_putstr("4");
		ft_execs(lexdat->left, env);
		ft_putstr("5");
	}
	else if (ft_strequ(redirection, "<"))
	{
		in = open(lexdat->left->input, O_RDONLY);
		dup2(in, 0);
		close(in);
		ft_execs(lexdat->right, env);
	}
	dup2(save_out, STDOUT_FILENO);
	dup2(save_in, STDIN_FILENO);
}

int check_redir(t_lexit *lexdat)
{
	if (ft_strequ(lexdat->input, ">") || ft_strequ(lexdat->input, "<"))
		return (1);
	return (0);
}

void exec_tree(t_lexit *lexdat, t_env *env)
{

	if (lexdat)
	{
		if (lexdat->left)
		{
			exec_tree(lexdat->left, env);
		}
		if (check_redir(lexdat))
		{
			handle_redir(lexdat->input, env, lexdat);
		}
		// else
		// {
		// 	ft_execs(lexdat);
		// }

		if (lexdat->right)
		{
			exec_tree(lexdat->right, env);
		}
	}
}


int					main(int ac, char **av, char **envp)
{
	t_edit			*line;
	t_lexit			*lexdat;
	t_norm			*values;
	t_lexit			*list;
	int					prio;
	t_env				*env;


	(void)ac;
	(void)av;
	prio = 0;
	lexdat = NULL;
	list = NULL;
	env = NULL;

	line = ft_memalloc(sizeof(t_edit));
	values = ft_memalloc(sizeof(t_norm));
	ft_setvalues(line, values);
	while (envp[values->i])
		ft_push_env(&env, envp[values->i++]);
	while (42)
	{
		ft_prompt();
		while ((values->ret = read(0, &values->buf, sizeof(int))) && values->buf != 10)
		{
			handle_key(values->buf, line);
			values->buf = 0;
		}
		ft_putchar('\n');
		parsing_listing(&list, line->line, env);
		// while (list)
		// {
		// 	ft_putstr("THIS IS INPUT : ");
		// 	ft_putstr(list->input);
		// 	ft_putchar('\n');
		// 	ft_putstr("THIS IS PRIO : ");
		// 	ft_putnbr(list->prio);
		// 	ft_putchar('\n');
		// 	list = list->next;
		// }
		lexdat = ft_tree_it(list, NULL, prio);
		// ft_print_tree(lexdat);
		exec_tree(lexdat, env);
		ft_add_history(line);
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "exit"))
			exit(0);
		ft_line_reset(line);
	}
	return (0);
}
