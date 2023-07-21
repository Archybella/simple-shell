#include "shell.h"

/**
* check_cmd - Determines if a file is an executable command.
* @info: The info struct.
* @path: Path to the file.
*
* Return: 1 if true, 0 otherwise.
*/
int check_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* duplicate_chars - Duplicates characters.
* @pathstr: The PATH string.
* @start: Starting index.
* @stop: Stopping index.
*
* Return: Pointer to the new buffer.
*/
char *duplicate_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
* find_executable - Finds the command in the PATH string.
* @info: The info struct.
* @pathstr: The PATH string.
* @cmd: The command to find.
*
* Return: Full path of the command if found, or NULL.
*/
char *find_executable(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((str_len(cmd) > 2) && starts_with(cmd, "./"))
{
if (check_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = duplicate_chars(pathstr, curr_pos, i);
if (!*path)
str_cat(path, cmd);
else
{
str_cat(path, "/");
str_cat(path, cmd);
}
if (check_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
