#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/* считывать вывод конвейера будем в такие структуры */
typedef struct item_s
{
  char url[512];
  int count;
} item_t;

item_t top_results[10];

/* awk ... log.txt | head -10 */
/* нужно привести к (в зависимости от варианта): awk ... log.txt | sort -k2,2 | head -10 */
void run_first_pipeline(int out_fd)
{
  int fd[2];
  pid_t pid;
  pipe(fd);
  pid = fork();

  if (pid == 0)
  {
    /* child */
    dup2(fd[1], 1);
    close(fd[1]);

    char* command[] = {"awk", "-F\"",
"{"
"  split($2, url, \" \");"
"  split($3, data, \" \");"
"  if (data[1] != \"-\")"
"  {"
"     sum[url[2]] += data[1]"
"  }"
"}"
"END { "
"  for(i in sum) { "
"    print i, sum[i]"
"  }"
"}", "log.txt", 0};
    execvp(command[0], command);
  }
  else if (pid > 0)
  {
    dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	int fd1[2];
	pipe(fd1);
	pid = fork();
	if(pid == 0){
		/* child */
		dup2(fd1[1], 1);
		close(fd1[1]);
		char* command[] = { "sort", "-k", "2,2nr", 0 };
		execvp(command[0], command);		
	}
	else if (pid > 0){
		/* parent */
		dup2(fd1[0], 0);		
		close(fd1[0]);
		close(fd1[1]);
		/* иначе можем так и висеть ждать ввода */
		dup2(out_fd, 1);
		close(out_fd);
		char *command[] = { "head", "-10", 0 };
		execvp(command[0], command);
		}
		else {
			printf("Error!");
		}
  }
  else
  {
    printf("Error!");
  }
}

int main(void)
{
  int fd[2];
  pipe(fd); /* запись в fd[1], читать из fd[0] */

  pid_t pid = fork();
  if (pid == -1)
  {
    printf("First fork failed");
    return 1;
  }
  else if (pid == 0)
  {
    /* дочерний процесс */
	/* запустить конвейер, выводить в pipe */
    run_first_pipeline(fd[1]);
  }

  /* родительский процесс */
  /* stdin привязываем к pipe */
  dup2(fd[0], 0);
  close(fd[1]);

  /* считываем вывод в формате строка число */
  int res_count = 0;
  int totalCount = 0;
  while (res_count < 10)
  {
    int items_read;
    items_read = scanf(" %s %d ", (char*)&top_results[res_count].url, &top_results[res_count].count);
    totalCount += top_results[res_count].count;
    if (items_read != 2)
    {
      break;
    }

    res_count++;
  }

  int i = 0;
  for (i = 0; i < res_count; i++)
    printf("%d - %s - %d - %.2f%%\n", i+1, top_results[i].url, top_results[i].count, (double)top_results[i].count * 100/ totalCount);
  /* здесь нужно правильно вывести полученные результаты */

  return 0;
}
