/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:20:41 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 18:24:54 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		switch_in_out(t_sh *sh, int in_out, t_lexit *list)
{
	if (in_out == 1)
	{
		sh->fd.saved_out = dup(1);
		dup2(sh->fd.saved_file, 1);
		close(sh->fd.saved_file);
	}
	if (in_out == 2)
	{
		sh->fd.saved_in = dup(0);
		dup2(sh->fd.saved_file, 0);
		close(sh->fd.saved_file);
		if (sh->hd_state)
			ft_strdel(&sh->hd_state);
	}
	if (in_out == 3)
	{
		if (list->fdclose == 1)
		{
			close(0);
			close(list->fdsrc);
		}
	}
}

int			switch_right(t_lexit *list, t_sh *sh, int *mod)
{
	if (list->redirs && (list->redirs->redir_right == 2))
	{
		if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
			O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (-1);
		else
			switch_in_out(sh, 1, list);
		*mod = 1;
	}
	if (list->redirs && (list->redirs->redir_right == 1))
	{
		if (!(isnumber(list->redirs->right_target)) &&
				list->redirs->right_target[0] != '-')
		{
			if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
			O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
				return (-1);
		}
		else
			switch_in_out(sh, 3, list);
		switch_in_out(sh, 1, list);
		*mod = 1;
	}
	return (0);
}

int			switch_left(t_lexit *l, t_sh *s, int *mod)
{
	if (l->redirs && (l->redirs->redir_left == 1))
	{
		if ((s->fd.saved_file = open(l->redirs->left_target, O_RDONLY)) == -1)
			return (-1);
		else
			switch_in_out(s, 2, l);
		*mod = *mod == 0 ? 2 : 3;
	}
	if (l->redirs && (l->redirs->redir_left == 2))
	{
		if ((s->fd.saved_file = open(s->hd_state, O_RDONLY)) == -1)
			return (-1);
		else
			switch_in_out(s, 2, l);
		*mod = *mod == 0 ? 2 : 3;
	}
	return (0);
}

int			switch_fd(t_lexit *list, t_sh *sh, int *mod)
{
	if ((switch_right(list, sh, mod) == -1))
		ft_errors(5, NULL, list->redirs->right_target);
	if ((switch_left(list, sh, mod) == -1))
		ft_errors(5, NULL, list->redirs->left_target);
	return (*mod);
}

void		reset_fd(t_sh *sh, int mod)
{
	if (mod == 1)
	{
		dup2(sh->fd.saved_out, 1);
		close(sh->fd.saved_out);
	}
	if (mod == 2)
	{
		dup2(sh->fd.saved_in, 0);
		close(sh->fd.saved_in);
	}
	if (mod == 3)
	{
		dup2(sh->fd.saved_out, 1);
		close(sh->fd.saved_out);
		dup2(sh->fd.saved_in, 0);
		close(sh->fd.saved_in);
	}
}
