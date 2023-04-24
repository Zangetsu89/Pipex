/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:11 by edawood           #+#    #+#             */
/*   Updated: 2022/02/03 14:36:12 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	int		s1_len;
	int		s2_len;

	if (s1 == 0 && s2 == 0)
		return (NULL);
	else if (s1 == 0)
		return (ft_strdup(s2));
	else if (s2 == 0)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!(concat))
		return (0);
	concat = ft_memcpy(concat, (void *)s1, s1_len);
	ft_memcpy(concat + s1_len, (void *)s2, s2_len);
	return (concat);
}
