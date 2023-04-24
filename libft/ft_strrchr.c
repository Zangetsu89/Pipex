/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:58 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:36:59 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		sl;
	char	*pr;

	sl = ft_strlen(s);
	pr = (char *)s + sl;
	i = 0;
	while (*s)
	{
		if (*pr == (char)c)
			return (pr);
		pr--;
		s++;
	}
	if (*pr == (char)c)
		return (pr);
	return (0);
}
