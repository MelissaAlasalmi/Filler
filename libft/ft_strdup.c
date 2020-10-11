/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Melissa <Melissa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:20:32 by malasalm          #+#    #+#             */
/*   Updated: 2020/10/11 16:47:58 by Melissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** allocates sufficient memory for a copy of the string “s1”, does the copy,
** and returns a pointer to it. The pointer may subsequently be used as an
** argument to the function free(3). If insufficient memory is available, NULL
** is returned and errno is set to ENOMEM. Uses ft_strcpy.
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*nstr;

	i = 0;
	while (s1[i] != '\0')
		i++;
	if (!(nstr = (char *)malloc((i + 1) * sizeof(char))))
		return (NULL);
	else
		nstr = ft_strcpy(nstr, s1);
	return (nstr);
}
