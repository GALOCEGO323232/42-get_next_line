#include "get_next_line_utils.h"

size_t gnl_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s && s[i])
        i++;
    return i;
}

char *gnl_strchr(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if (c == '\0')
        return (char *)s;
    return NULL;
}

char *gnl_strdup(const char *s)
{
    size_t len;
    char *dup;
    int i;

    len = gnl_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[len] = '\0';
    return dup;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	len1 = 0;
    if (s1)
	    while (s1[len1])
		    len1++;
	len2 = gnl_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	i = -1;
	while (++i < len2)
		str[len1 + i] = s2[i];
	str[len1 + len2] = '\0';
    if(s1)
        free((char *)s1);
	return (str);
}
