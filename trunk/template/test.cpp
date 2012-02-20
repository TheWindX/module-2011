
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
    *    windows��ʹ��socket������WSAStartup��ʼ���������ܵ���
    */
    if(WSAStartup(MAKEWORD(2,2), &WSAData))
    {
        printf("WSA failed\n");
        return;
    }
    
    /*
    *    ����url�е�������ַ�����·��
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
    *    �趨socket����,��δ������ʼ��
    */
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    pURL = gethostbyname(host);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
    addr.sin_port = htons(80);

    /*
    *    ��֯���͵�web����������Ϣ
    *    Ϊ��Ҫ�����������Ϣ��ο�HTTPЭ���Լ��
    */
    strcat(header, "GET ");
    strcat(header, GET);
    strcat(header, " HTTP/1.1\r\n");
    strcat(header, "HOST: ");
    strcat(header, host);
    strcat(header, "\r\nConnection: Close\r\n\r\n");
    
    /*
    *    ���ӵ�����������������header�������ܷ���������ҳԴ���룩
    */
    connect(sockfd,(SOCKADDR *)&addr,sizeof(addr));
	SOCKADDR_IN   sockAddr; 
	int   iLen=sizeof(sockAddr); 
	getpeername(sockfd,(struct   sockaddr   *)&sockAddr,&iLen);//�õ�Զ��IP��ַ�Ͷ˿ں� 
	char strAddr[256];
	sprintf(strAddr, "%s", inet_ntoa(sockAddr.sin_addr) );//IP 

	short uIPPort   =   sockAddr.sin_port;//�˿ں�

	getsockname(sockfd,(struct   sockaddr   *)&sockAddr,&iLen);//�õ����ص�IP��ַ�Ͷ˿ں�
	char* strAddr1   =   inet_ntoa(sockAddr.sin_addr);//IP 
	short uIPPort2   =   sockAddr.sin_port;//�˿ں�

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
