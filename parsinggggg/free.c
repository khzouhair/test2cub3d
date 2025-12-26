/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:00:48 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:27:31 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_c.h"

void    ft_clear_list(t_clean **lst)
{
    t_clean    *current;

    if (!lst || !*lst)
        return ;
    current = *lst;
    while (current)
    {
        *lst = current->next;
        free(current->ptr);
        free(current);
        current = *lst;
    }
}

void    *ft_alloc(size_t size, int flag)
{
    static t_clean    *head;
    t_clean            *allocation;
    void                *s;

    if (flag == 0)
        return (ft_clear_list(&head), NULL);
    s = malloc(size);
    if (!s)
    {
        write(2, "failed allocation\n", 19);
        exit(1);
    }
    allocation = ft_creat_list(s);
    if (!allocation)
    {
        free(s);
        write(2, "failed allocation\n", 19);
        exit(1);
    }
    ft_add_front(&head, allocation);
    return (s);
}

t_clean    *ft_creat_list(void *mem)
{
    t_clean    *new;

    new = malloc(sizeof(t_clean));
    if (!new)
        return (NULL);
    new->ptr = mem;
    new->next = NULL;
    return (new);
}

void	ft_add_front(t_clean **list, t_clean *to_add)
{
	if (!to_add)
		return ;
	to_add->next = *list;
	*list = to_add;
}
