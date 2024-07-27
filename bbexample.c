#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "bbexample.h"
#include "host.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void *socket_thread(void *arg) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from server";

    // 소켓 파일 디스크립터 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        pthread_exit(NULL);
    }

    // 소켓 옵션 설정
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        pthread_exit(NULL);
    }

    // 주소 설정
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 소켓을 주소에 바인딩
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        pthread_exit(NULL);
    }

    // 연결 대기
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        pthread_exit(NULL);
    }

    printf("Server listening on port %d\n", PORT);

	while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) 
	{
		printf("Connection accepted\n");

		// 클라이언트로부터 메시지 읽기
		read(new_socket, buffer, BUFFER_SIZE);
		printf("Message from client: %s\n", buffer);

		// 클라이언트에 응답 보내기
		send(new_socket, hello, strlen(hello), 0);		
		printf("Hello message sent\n");
		host_send(new_socket);		

		// 소켓 닫기
		close(new_socket);
	}

    close(server_fd);
    pthread_exit(NULL);
}

int main(void)
{
	printf("RFNSOL Fixed Reader RNS.MX\n");

	pthread_t server_thread;

	// 서버 소켓을 처리할 쓰레드 생성
	if (pthread_create(&server_thread, NULL, socket_thread, NULL) < 0) {
	    perror("could not create thread");
	    return 1;
	}

	// 메인 쓰레드는 서버 쓰레드가 종료될 때까지 대기
//	pthread_join(server_thread, NULL);


	while(1)
	{
		
	}

	return 0;
}





