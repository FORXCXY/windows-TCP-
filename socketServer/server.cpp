#include <iostream>

#include <WinSock2.h>

#include <WS2tcpip.h>

#pragma comment(lib,"WS2_32.Lib") //ָ����̬��lib�ļ�

using namespace std;

//�����׽���
//�׽��ְ�
//�����׽���
//���տͻ�����������acceept ����
//���ͺͽ��տͻ�������
//�ر��׽���

int main() {

	WSADATA wd; //��ȡsocket�����Ϣ����

	if ((WSAStartup(MAKEWORD(2, 2), &wd)) != 0) { //��ʼ������
		cout << "Failed to create WSA" << endl;
		return 0;
	}

	// 1.�����׽���TCP
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		cout << "Failed to create socket" << endl;
		return 0;
	}

	// 2.����������׽���ʵ����һ��IP������˿�
	sockaddr_in addr;
	
	// �����ֽ���
	// ��ȷ���ڲ�ͬ�����֮��������ݴ���ʱ���ܹ�ʹ��ͳһ�������ֽ������ͨ��
	// host to network short��һ���޷��Ŷ����ͣ�16λ���������ֽ���ֵת��Ϊ�����ֽ���ֵ
	addr.sin_port = htons(8000);
	// ��IPv4 ��ַ���ַ�����ʾת��Ϊ��������ʽ����������洢�� addr.sin_addr.s_addr ��
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	// ָ����ַ��
	addr.sin_family = AF_INET;

	int len = sizeof(sockaddr_in);
	if (bind(s, (sockaddr*)&addr, len) == SOCKET_ERROR) {
		cout << "socket error" << endl;
		return 0;
	}

	// 3.���� 
	if (listen(s, 5) == SOCKET_ERROR) {
		cout << "listen error" << endl;

	}

	// 4.������������,�����غͷ�����ͨѶ���׽���
	sockaddr_in addrClient; // ����ͻ���ip�Ͷ˿�
	memset(&addrClient, 0, sizeof(sockaddr_in)); // ��ʼ��
	len = sizeof(sockaddr_in);
	SOCKET c = accept(s, (sockaddr*)&addrClient, &len);

	if (c == INVALID_SOCKET) {
		cout << "accept error" << WSAGetLastError() << endl;
	}

	// 5.���ͽ�����Ϣ
	int ret = 0;
	do {
		// ��ͻ��˷�����Ϣ
		ret = send(c, "I am server", strlen("I am server"), 0);
		// ���տͻ�����Ϣ
		char buffer[64] = { '\0' };
		// memset(&buffer, '\0', sizeof(buffer));
		ret = recv(c, buffer, 64, 0);
		cout << "recv:" << buffer << endl;
	} while (ret != SOCKET_ERROR && ret != 0);

	// 6.�ر��׽���
	closesocket(s);
	WSACleanup();
	return 0;



}