# include "../../include/header.h"

void default_env(t_env *env)
{
    env->value = NULL;
    env->next = NULL;
    env->key = NULL;
}

void free_case(t_env *b, int head)
{
    free(b->key);
    free(b->value);
    if (!head)
        free(b);
}

int add_env(t_env *env, char *key, char *value)
{
    t_env *new;
    
    new = malloc(sizeof(t_env));
    if (env->key == NULL)
    {
        env->key = ft_strdup(key);
        env->value = ft_strdup(value);
        return (0);
    }
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    while (env && env->next)
        env = env->next;
    if (!env)
        return (1);
    env->next = new;
    return (0);
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

