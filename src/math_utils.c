/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:00:29 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/12 16:05:40 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}
