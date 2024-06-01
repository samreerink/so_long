/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   free_animation.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/06/01 21:54:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/06/01 21:59:24 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_anim(t_animation *a)
{
	t_frame	*current;
	t_frame	*temp;

	if (!a)
		return ;
	current = a->frame;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	free(a);
}
