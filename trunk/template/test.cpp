
#include    <stdio.h>
#include    <winsock.h>
#include    <string.h>
#pragma comment(lib, "ws2_32.lib")

void geturl(char *url)
{
    WSADATA WSAData={0};
    SOCKET    sockfd;
    struct sockaddr_in    addr;
    struct hostent    *pURL;
    char    myurl[BUFSIZ];
    char    *pHost = 0, *pGET = 0;
    char    host[BUFSIZ], GET[BUFSIZ];
    char    header[BUFSIZ] = "";
    static char    text[BUFSIZ];
    int i;
    
    /*
    *    windows下使用socket必须用WSAStartup初始化，否则不能调用
    */
    if(WSAStartup(MAKEWORD(2,2), &WSAData))
    {
        printf("WSA failed\n");
        return;
    }
    
    /*
    *    分离url中的主机地址和相对路径
    */
    strcpy(myurl, url);
    for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost);
    if ( (int)(pHost - myurl) == strlen(myurl) )
        strcpy(GET, "/");
    else
        strcpy(GET, pHost);
    *pHost = '\0';
    strcpy(host, myurl);
    printf("%s\n%s\n", host, GET);

    /*
    *    设定socket参数,并未真正初始化
    */
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    pURL = gethostbyname(host);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
    addr.sin_port = htons(80);

    /*
    *    组织发送到web服务器的信息
    *    为何要发送下面的信息请参考HTTP协议的约定
    */
    strcat(header, "GET ");
    strcat(header, GET);
    strcat(header, " HTTP/1.1\r\n");
    strcat(header, "HOST: ");
    strcat(header, host);
    strcat(header, "\r\nConnection: Close\r\n\r\n");
    
    /*
    *    连接到服务器，发送请求header，并接受反馈（即网页源代码）
    */
    connect(sockfd,(SOCKADDR *)&addr,sizeof(addr));
	SOCKADDR_IN   sockAddr; 
	int   iLen=sizeof(sockAddr); 
	getpeername(sockfd,(struct   sockaddr   *)&sockAddr,&iLen);//得到远程IP地址和端口号 
	char strAddr[256];
	sprintf(strAddr, "%s", inet_ntoa(sockAddr.sin_addr) );//IP 

	short uIPPort   =   sockAddr.sin_port;//端口号

	getsockname(sockfd,(struct   sockaddr   *)&sockAddr,&iLen);//得到本地的IP地址和端口号
	char* strAddr1   =   inet_ntoa(sockAddr.sin_addr);//IP 
	short uIPPort2   =   sockAddr.sin_port;//端口号

	char buff[1024];
	sprintf(buff, "local:%s,%d\nremote:%s, %d\n", strAddr, (int)uIPPort, strAddr1, (int)uIPPort2);
	printf(buff);

    send(sockfd, header, strlen(header), 0);
    
    while ( recv(sockfd, text, BUFSIZ, 0) > 0)
    {    
        printf("%s", text);
        strnset(text, '\0', BUFSIZ);
    }

    closesocket(sockfd);
    
    WSACleanup();
}

int main()
{
    char    url[256];
    
    geturl("ifconfig.me");
    return 0;
} 
