#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
    struct sockaddr_in6	servaddr;       // IPv6 socket数据对象
    char				recvline[MAXLINE + 1];      // 存储信息的缓冲区

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)       // 打开socket并返回文件描述符
		err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));     // 清0
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port   = htons(13);	/* daytime server */
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)    // 将sockfd和servaddr建立连接
		err_sys("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {    // 将sockfd中的信息读入缓冲区recvline中
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	exit(0);
}
