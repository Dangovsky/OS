#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define SOCK_PATH "/var/run/collectd-unixsock"
#define BUF_SIZE 12
#define HOST_NAME "this-host"

char buf[64];
char message[] = "PUTVAL ";//запрос на сервер
char * sock_path = "/var/run/collectd-unixsock";
int main(int argc, char *argv[])
{
	int sock;//сокет
	FILE * received_file;
	ssize_t len;
	struct sockaddr_un addr;//адрес сервера
		
	sock =socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock<0)//если сокет инфицализируется с ошибкой
	{
		perror("socket");
		exit(1);
	}
	unlink(SOCK_PATH);
	addr.sun_family = AF_UNIX;//использвуем unix сокет (от collectd)
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr))<0)//если коннект с ошибкой
	{
		perror("connect");
		exit(2);
	}
	strcat(message, HOST_NAME); // hostname из colletd.conf
	strcat(message, "/stdout/load-");//Путь csv файлов
	strcat(message, argv[1]);//Сообщение первый аргумент		
	strcat(message, " ");//Копируем ' ' в переменную сообщения
        strcat(message, argv[2]);//Копируем второй аргумент в переменную сообщения
        strcat(message, "\r\n");//Копируем '\r\n' в переменную сообщения
        printf(message);
        send(sock, message, strlen(message), 0);//Отправляем  сообщение в сокет
        close(sock);
	
	return 0;
}
