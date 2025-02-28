/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:16:54 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/08 17:55:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **plst, void (*del)(void *))
{
	t_list	*next;

	while (*plst)
	{
		next = (*plst)->next;
		ft_lstdelone(*plst, del);
		*plst = next;
	}
}
