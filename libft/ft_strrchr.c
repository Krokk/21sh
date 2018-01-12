/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:48:06 by jecarol           #+#    #+#             */
/*   Updated: 2018/01/07 20:09:41 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*l;
	int		i;

	l = (char*)s;
	i = ft_strlen(l);
	while (l[i] != c && i > 0)
		i--;
	if (l[i] == c)
		return (&l[i]);
	return (NULL);
}
