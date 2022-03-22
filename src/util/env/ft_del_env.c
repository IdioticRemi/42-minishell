/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:06:46 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 19:21:43 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_case(t_env *b, int head)
{
    free(b->key);
    free(b->value);
    if (!head)
        free(b);
}

t_env *delone_env(t_env *env, char *key)
{
    t_env *tmp;
    t_env *previous;
    
    previous = env;
    if (ft_strncmp(key, previous->key, ft_strlen(env->value)) == 0) // Verifie la tete de liste, cas particulier
    {
        env = previous->next;
        free_case(previous, 1);
        return (env);
    }
    tmp = previous->next; // le cas n est gere on se place donc sur le cas n+1
    while(tmp != NULL) // On Mouline est on supprime si on trouve l'element
    {
        if (ft_strncmp(key, tmp->key, ft_strlen(env->value)) == 0)
        {
            previous->next = tmp->next;
            free_case(tmp, 0);
            return (env);
        }
        previous = tmp; // pour ce souvenir dans la prochaine iteration du precedent
        tmp = tmp->next;
    }
    return (env);
}
