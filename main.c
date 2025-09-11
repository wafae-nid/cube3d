/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:04:29 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/11 19:07:13 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_it_map(char *line)
{
    char *trimmed;
    
    trimmed = ft_strtrim(line, " ");
    if(!trimmed)
        return(0);
    else if(is_valid_char(trimmed[0], line , 0))
        return(1);
    else
        return(0);
}


int is_identifier(char *str)
{
    if(!ft_strcmp(str,"NO") 
        || !ft_strcmp(str, "SO") 
        || !ft_strcmp(str, "WE") 
        || !ft_strcmp(str, "EA") 
        || !ft_strcmp(str,"F") 
        || !ft_strcmp(str,"C"))
            return(1);
    else
        return(0);
}
int is_texture(char *str, t_identifiers *identifiers)
{
    
    if(!ft_strcmp(str,"NO") 
        || !ft_strcmp(str, "SO") 
        || !ft_strcmp(str, "WE") 
        || !ft_strcmp(str, "EA"))
    {
        if(!ft_strcmp(str, "NO"))
            identifiers->no++;
        else if(!ft_strcmp(str, "SO"))
            identifiers->so++;
        else if(!ft_strcmp(str, "WE"))
            identifiers->we++;
        else if(!ft_strcmp(str, "EA"))
            identifiers->ea++;
        if(identifiers->no > 1 || identifiers->so > 1 ||  identifiers->we > 1 || identifiers->ea > 1)
            return(0);
        return(1);
    }
    else
        return(0);
}
int is_color(char *str, t_identifiers *identifiers)
{
   if(!ft_strcmp(str,"F") || !ft_strcmp(str,"C"))
   {
        if(!ft_strcmp(str,"F"))
            identifiers->f++;
        else if(!ft_strcmp(str,"C"))
            identifiers->c++;
        if(identifiers->f > 1 || identifiers->c > 1)
            return(0);
        return(1);
   }
    return(0);
}
 int valid_texture(const char *path) 
 {
    int len;
    int fd;
    
    if(!path)
    return(0);
    len = ft_strlen(path);
    if (len < 4)
        return (0);
    if(ft_strcmp(path + len -4, ".xpm"))
    {
        return(0);
    }
    else
    {
        fd = open(path, O_RDONLY);
        if(fd < 0)
            return(0);
        else
        {
            return(1);
        }
    }
}

int comma_count(char *color)
{
    int i;
    int count;

    if(!color)
        return(0);
    i = 0;
    count = 0;
    while(color[i])
    {
        if(color[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        return(0);
    else
        return(1);
}
int color_validation(char *color)
{
    char *trimmed;
    int i;
    int numb;
    
    trimmed = ft_strtrim(color, " ");
    i = 0;
    if(!trimmed)
        return(0);
    while(trimmed[i])
    {
        if(!ft_isdigit(trimmed[i]))
            return(0);
        i++;
    }
    numb = ft_atoi(trimmed);
    if(numb <0 || numb >255)
        return(0);
    else
        return(1);
}

int valid_color(char *colors)
{
    char **splitted;
    int i;
    
    i = 0;
    if(!colors)
        return(0);
    if(!comma_count(colors))
        return(0);
    if(count_words(colors,',') != 3)
        return(0);
    splitted = custom_split(colors,',', 1);
    while(splitted[i])
    {
        if(!color_validation(splitted[i]))
            return(0);  
        i++;
    }
    return(1); 
}   

int parse_texture(char **splitted)
{
    int i;

    i = 1;
    if(splitted[2])
        return(0);
    else
        return(valid_texture(splitted[1])); 
}

int parse_color(char **splitted)
{
    
    if(splitted[2])
        return(0);
    else
        return(valid_color(splitted[1]));
    
}

int config_parsser(char *line, t_identifiers *identifiers)
{
    char **splitted;
    char *trimmed;

    if(!line)
        return(0);
    trimmed = ft_strtrim(line,"  \n");
    if(!trimmed)
        return(0);
    else if(!ft_strcmp(trimmed,""))
        return(1);
    splitted = custom_split(trimmed, ' ', 1);
    if(!splitted)
        return(0);
    if(is_identifier(splitted[0]) == 0)
        return(0); 
    else
    {
        if(is_texture(splitted[0], identifiers) == 1)
            return(parse_texture(splitted));
        else if(is_color(splitted[0], identifiers) == 1)
            return(parse_color(splitted));
        else
            return(0);
    }
}

int after_map_parse(char *line)
{
    int i;

    i = 0;
    if(!line)
        return(1);
    while(line[i])
    {
        if(line[i]!= ' ' && line[i] !='\n')
            return(0);
        i++;
    }
    return(1);
}

int parssing(int fd)
{
    char *line;
    t_identifiers *identifiers;
    
    identifiers = gcmalloc(sizeof(t_identifiers),0);
    if(!identifiers)
        return(0);
    identifiers->no = 0;
    identifiers->so = 0;
    identifiers->we = 0;
    identifiers->ea = 0;
    identifiers->f = 0;
    identifiers->c = 0;
    
    line = get_next_line(fd);
    if (!line)
        return(0);
    while(!is_it_map(line))
    {
        if(!config_parsser(line, identifiers))
            return(0);
        printf("[%s\n", line);
        line = get_next_line(fd);
        
    }
    if(!identifiers->no || !identifiers->so 
        || !identifiers->we || !identifiers->ea 
        || !identifiers->f || !identifiers->c)
    {
        return(0);
    }
    if(!map_parssing(fd, line))
        return(0);
    line = get_next_line(fd);
    while(line)
    {
        if(!after_map_parse(line))
            return(0);
        line = get_next_line(fd);
    }
    return(1);
    
}

int  lengh(int len)
{
    static int llen;

    if(len > llen)
    {
        llen = len;
    }
    return(llen); 
}
int width(int i)
{
    static int width;

    if(i< 0)
        return(width);
    else
    {
        width++;
        return(width);
    }
}

t_map  *alloc_map(void)
{
    int     width;
    int     len;
    t_map  *map;
    int     i;
    
    width = width(-1);
    len = lengh(-1);
    map = gcmalloc(sizeof(t_map));
    if(!map)
        return(NULL);
    map->line = gcmalloc((width + 1)*sizeof(char *));
    if(!map->line)
        return(NULL);
    i = 0
    while(i < width + 1)
    {
        map->line[i] = gcmalloc(len -1);
            i++;
    }
    map->line[i] = NULL;
    return(map);
}

t_config *config_struct(char *file)
{
    int fd;
    t_config    *config;
    
    fd = open(argv[1], O_RDONLY);
    config = gcmalloc(sizeof(t_config));
    if (!config)
        return(NULL);
    else
    {
       config->map = alloc_map();
       if(!config->map)
        return(NULL);
        config->texture = gcmalloc(5 *(sizeof(char *)))
        if(!config->texture)
            return(NULL);
        
        
    }  
}

int main(int argc, char **argv)
{
    int fd;
    // t_config    *config;
    
    if(argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if(fd >= 0)
        {
            if(!parssing(fd))
            {
                printf("enter a valid map/config file\n");
                return(1);
            }
            else
            {
               printf("%d\n", longest_m_line(-1));
               printf("%d\n", width(-1));
               return(0);
            }
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