/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:59:11 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/15 10:52:34 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"

void	*ft_ternary(void *output1, void *output2, int condition)
{
	if (condition)
		return (output1);
	return (output2);
}
// could use it this way to compare ints
/*
int *test = ft_ternary(&int1, &int2, int1 > int2);
	ft_printf("%d\n", *test);
*/