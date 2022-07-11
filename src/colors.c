/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:11:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/07/11 17:13:08 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

static int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

static int	get_b(int color)
{
	return (color & 0xFF);
}

int	blend_colors(int c1, int c2)
{
	int cnew;

	cnew = 0;
	cnew = ((get_r(c1) + get_r(c2)) / 2) << 8;
	cnew = (cnew + ((get_g(c1) + get_g(c2)) / 2)) << 8;
	cnew += (get_b(c1) + get_b(c2)) / 2;
	return (cnew);
}
