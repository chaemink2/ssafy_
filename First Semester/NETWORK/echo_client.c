#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// AWS IP
const char *IP = "127.0.0.1";
const char *PORT = "12345";

int sock; // Client용 Socket

void interrupt(int arg) // Socket 할당 종료 함수
{
	printf("\nYou typped Ctrl + C\n");
	printf("Bye\n");

	close(sock);
	exit(1);
}

int main()
{
	signal(SIGINT, interrupt); // SIGINT 신호를 받아서 interrupt함수를 실행 한다

	sock = socket(PF_INET, SOCK_STREAM, 0); // Socket 생성, IPV4 + 연결지향형 = TCP/IP 밖에 없다
	if (sock == -1) // Socket 생성 실패 방어 코드
	{
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}

	struct sockaddr_in addr = {0}; // Socket 주소 할당
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(atoi(PORT)); // htons : host to net, port

	// Connect
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) // IP 주소로 연결
	{
		printf("ERROR :: 2_Connect Error\n");
		exit(1);
	}

	char buf[100];

	// Client Socket 종료 과정
	// 1. interrupt 발생
	// 2. exit 입력
	// 3. read 했을 때 결과가 0이면 서버 종료
	while (1)
	{
		memset(buf, 0, 100);
		scanf("%s", buf);
		if (!strcmp(buf, "exit")) // exit 요청
		{
			write(sock, buf, strlen(buf));
			break;
		}
		write(sock, buf, strlen(buf)); // 요청 전달
		memset(buf, 0, 100);
		int len = read(sock, buf, 99);
		if (len == 0) // 서버가 종료되면 요청 종료
		{
			printf("INFO :: Server Disconnected\n");
			break;
		}
		printf("%s\n", buf);
	}

	// close sock
	close(sock);
	return 0;
}
