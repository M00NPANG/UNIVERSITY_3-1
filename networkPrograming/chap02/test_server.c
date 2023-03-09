#include <stdio.h>
#include <WinSock2.h>

int main(void)
{
	WSADATA wsaData;
	int ret, errorCode;				// 리턴값 확인용 변수

	ret = WSAStartup( MAKEWORD(2,2), &wsaData);
	if (ret = 0)	{	//성공
		printf("> 원속 라이브러리 초기화 성공.\n ");
	}
	else {
		errorCode = WSAGetLastError();			// 에러 값 확인
		printf("<ERROR> WSAStartup 오류 발생(code=%d)\n", errorCode);
		return 1;	//exit(1);
	}


	//				IVv4 , 연결지향형 : 손실없는 전송지원, 전송계층->TCP 사용
	SOCKET serverSocket;
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	// TCP
	if (serverSocket == INVALID_SOCKET) { // 오류상황 ...
		errorCode = WSAGetLastError();
		printf("<ERROR> socket  오류 발생(code=%d)\n", errorCode);
	}

	// 서버의 주소와 포트를 할당
	SOCKADDR_IN severAddr;		//IPv4 주소 체계
	memset(&severAddr, 0, sizeof(severAddr));		// 0으로 채워주기 위한 코드
	severAddr.sin_family = AF_INET;		// IPv4 주소 체계
	severAddr.sin_port = htons(9000);	// big endian
	severAddr.sin_addr.S_un.S_addr = inet_addr("1.2.3.4");

	/*
	#define s_addr  S_un.S_addr
	#define s_host  S_un.S_un_b.s_b2    // host on imp
	#define s_net   S_un.S_un_b.s_b1    // network
	#define s_imp   S_un.S_un_w.s_w2    // imp
	#define s_impno S_un.S_un_b.s_b4    // imp #
	#define s_lh    S_un.S_un_b.s_b3    // logical host
	*/

	bind(serverSocket, (SOCKADDR*)&severAddr, sizeof(severAddr));
	// severAddr가 bind에서는 제네럴 타입이어야 하기 떄문에 SOCKADDR*로 캐스팅해주어야 함.  (타입 맞추기)
	// SOCKADDR_IN port와 addr 구조체가 들어있기 떄문에 얘로 선언하고 후 바꿔주는것이 편함

	unsigned long host_addr = 0x12345678;			//32bits
	unsigned long net_addr = htonl(host_addr);		// network byte ordeering = BIG ENDIAN (상위 바이트를 하이 번지에 저장)
	// htonl() -> 본인이 어떤 엔디안인지 확인
	printf("> host byte ordering = 0x%x : \n", host_addr);
	printf("> network byte ordering = 0x%x (Big Endian) : \n", net_addr)

	listen();		// 서버 준비 완료

	accept();		// 연결 수신 

	recv();

	send();

	closesocket(serverSocket);

	WSACleanup();

	return 0;
}