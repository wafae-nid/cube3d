/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:18:14 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/07 06:10:25 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return(-1);
    while(str[i])
    {
        i++;
    }
    return(i); 
}

int is_valid_char(char c)
{
    if(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
        return (1);
    else
        return (0);
}

int valid_map_chars(char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        if(!is_valid_char(line[i]))
            return(0);
        i++;
    }
    return(1);
}

int parse_frame(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(line[i] != '1' && line[i] != ' ')
        {
            return(0);
        }
        i++;
    }
    return(1);
}

int max_len(char *prev_line, char *next, char *line)
{
    int plen;
    int nlen;
    int llen;

    plen = ft_strlen(prev_line);
    nlen = ft_strlen(next);
    llen = ft_strlen(line);
    
    if(plen >= nlen && plen >= llen)
        return(plen);
    else if(nlen >= llen)
        return(nlen);
    return(llen);
}

char *pad_line(int max, char *line)
{
    int len;
    int diff;
    char  *padded;

    len = ft_strlen(line);
    diff = max - len;
    padded = gcmalloc(max, 1);
    if(!padded)
        return(NULL);
    while(diff < max)
    {
        padded[diff]=' ';
        diff++;
    }
    padded[diff] = '\0';
    return(padded);
}

t_plines *padding(char *prev_line, char *next, char *line)
{
   int max;
   t_plines *res;
   
   
   max = max_len(prev_line, next, line);
   res = gcmalloc(sizeof(t_plines),1);
   if(!res)
        return(NULL);
    if(max == ft_strlen(prev_line))
    {
        res->prev = prev_line;
        res->line = pad_line(max, line);
        res->next = pad_line(max, next);
    }
    else if(max == ft_strlen(line))
    {
        res->prev = pad_line(max, prev_line);
        res->line = line;
        res->next = pad_line(max, next);
    }
    else if(max == ft_strlen(next))
    {
        res->prev = pad_line(max,prev_line);
        res->line = pad_line(max,line);
        res->next = next;   
    }
   return(res);  
}

// int parse_inside(char *line, char *next)
// {
//     int i;
//     size_t len;
//     static char *prev_line;
//     t_plines *res;
    
//     i = 0;
//     // res = padding(prev_line, next, line);
//     prev_line = line;
//     len = ft_strlen(res->line);
    
//     if(!valid_map_chars(res->line))
//         return(0);
//     if(res->line[0] || res->line[len - 1] != 1)
//         return(0);
//     else
//     {
//         i = 1;
//         return(1);
//     }
    
// }

int lineparssing(char *line, char *next, int first)
{
    char            *trimmed;
    char            *next_;
    static char     *prev_line;
    t_plines        *res;
    
    (void)first;
    trimmed = ft_strtrim(line, " \t\n\v\f\r\n");
    next_ = ft_strtrim(next," \t\n\v\f\r\n");
    res = padding(prev_line, next_, trimmed);
    prev_line = trimmed;
    if(!trimmed)
        return(0);
    // if(!next || ft_strlen(next) == 0 || first == 1)
    // {
    //     return(parse_frame(trimmed));
    // }
    // else
    // {
    //     return(parse_inside(trimmed, next));
    // }
    return(1);
}
 
    
int parssing(int fd)
{
    char *line;
    char *next;
    int  flag;
    
    line = get_next_line(fd);
    if (!line)
        return(0);
    flag = 0;
    while(line)
    {
        next = get_next_line(fd);
        if(!next)
            break;
        flag++;
        lineparssing(line, next, flag);
        line = next;
        // if(!lineparssing(line, next, flag))
        //     return(0);
    }
    return(1);
}

int main(int argc, char **argv)
{
    int fd;

    if(argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if(fd >= 0)
        {
            printf("%d\n",parssing(fd));
        
        }
        else
        {
           printf("enter a valid map/config file\n");
           return(1);
        }
    }
    else
    {
        printf("enter a valid map/config file\n");
        return(1);
    }
}