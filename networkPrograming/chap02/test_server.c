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

	bind();		// 주소 설정...

	listen();		// 서버 준비 완료

	accept();		// 연결 수신 

	recv();

	send();

	closesocket(serverSocket);

	WSACleanup();

	return 0;
}