/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 21:14:25 by rfabre            #+#    #+#             */
/*   Updated: 2018/03/12 21:14:26 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/sh.h"

char			**ft_fill_envp(t_env *env)
{
	char		**ret;
	t_env		*tmp;
	int			len;
	int			i;

	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = ft_memalloc(sizeof(char **) * (len + 1));
	i = 0;
	tmp = env;
	while (i < len)
	{
		ret[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

char				*find_cmd(char **apaths, char *cmd)
{
	int	i;
	char	*tmp_path;

	i = 0;
	tmp_path = NULL;
	while (apaths[i])
	{
		tmp_path = ft_strjoin(apaths[i], cmd);
		if (!access(tmp_path, F_OK) && !ft_strstr(BUILTIN, cmd))
		{
			ft_strdel(&tmp_path);
			return(ft_strjoin(apaths[i], cmd));
		}
		ft_strdel(&tmp_path);
		i++;
	}
	return (NULL);
}

void				ft_execute_non_binary(char **cmd, t_env *env, t_lexit *lexdat,
					t_edit *line)
{
	(void)lexdat;
	(void)line;

	if (!ft_strcmp(cmd[0], "env"))
		ft_env(cmd, env);
}

void				ft_execute_binary(t_lexit *tmp, char *path)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		ft_putstr("fork error");
	if (pid == 0)
		execve(path, tmp->args, tmp->env);
	else
		waitpid(pid, NULL, 0);
}

void				ft_execs(t_lexit *lexdat, t_env *env)
{
	char *path;
	char **allpaths;

	allpaths = ft_set_paths(env);

	if (lexdat->input)
	{
			path = find_cmd(allpaths, lexdat->input);
			ft_execute_binary(lexdat, path);
			// ft_strdel(&path);
	}
}
