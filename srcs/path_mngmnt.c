/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_mngmnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:02 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/11 17:22:50 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_init_all_paths(char **paths)
{
	int			i;
	char		*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
}

char				**ft_set_paths(t_env *env)
{
	t_env *tmp;
	char *tmp1;
	char **apaths;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp("PATH=", tmp->var, 5))
		{
			tmp1 = ft_strdup(tmp->var + 5);
			apaths = ft_strsplit(tmp1, ':');
			ft_strdel(&tmp1);
			ft_init_all_paths(apaths);
			return (apaths);
		}
		tmp = tmp->next;
	}
	return (NULL);
}


char		**t_env_to_array(t_env **venv)
{
	int		i;
	char	**result;
	t_env	*tmp;
	int		j;

	j = 0;
	tmp = *venv;
	while (*venv)
	{
		j++;
		venv = &(*venv)->next;
	}
	if (tmp != NULL)
	{
		if (!(result = ft_memalloc(sizeof(char**) * (j + 1))))
			return (NULL);
		i = -1;
		while (tmp)
		{
			result[++i] = ft_strdup(tmp->var);
			tmp = tmp->next;
		}
		return (result);
	}
	return (NULL);
}
