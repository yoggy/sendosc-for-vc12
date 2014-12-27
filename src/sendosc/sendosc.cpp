//
//  sendosc.cpp : 
//      Open Sound Control packet sending program.
//
#ifdef WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <windows.h>
#endif 

// oscpack
// http://www.audiomulch.com/~rossb/code/oscpack/
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "liboscpack_vc12x64D.lib")
#else
#pragma comment(lib, "liboscpack_vc12x64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "liboscpack_vc12x86D.lib")
#else
#pragma comment(lib, "liboscpack_vc12x86.lib")
#endif
#endif
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#include <string>

#define BUF_SIZE 1024

void usage()
{
	fprintf(stderr, "usage : sendosc dst_host dst_port path [[type] [param]] ...\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  type\n");
	fprintf(stderr, "    i : int\n");
	fprintf(stderr, "    f : float\n");
	fprintf(stderr, "    b : boolean (true/false)\n");
	fprintf(stderr, "    s : string\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  example\n");
	fprintf(stderr, "    ./sendosc 127.0.0.1 5678 /test1 i 123\n");
	fprintf(stderr, "    ./sendosc 127.0.0.1 5678 /test2 f 123.45\n");
	fprintf(stderr, "    ./sendosc 127.0.0.1 5678 /test3 s teststring\n");
	fprintf(stderr, "    ./sendosc 127.0.0.1 5678 /test4 b true\n");
	fprintf(stderr, "    ./sendosc 127.0.0.1 5678 /test5 s teststring i 123 f 123.4 b false\n");
	fprintf(stderr, "\n");

	exit(0);
}

int
main(int argc, char* argv[])
{
	if (argc < 4 || (argc - 4) % 2 == 1) usage();

	// setup udp socket
	char *host = argv[1];
	unsigned short port = atoi(argv[2]);
	UdpTransmitSocket transmitSocket(IpEndpointName(host, port));

	// setup packet
	char buf[BUF_SIZE];
	memset(buf, 0, BUF_SIZE);
	osc::OutboundPacketStream p(buf, BUF_SIZE);

	//p << osc::BeginBundleImmediate;

	char *path = argv[3];
	p << osc::BeginMessage(path);

	int idx = 4;
	while (idx + 1 < argc) {
		std::string type = std::string(argv[idx]);
		std::string val = std::string(argv[idx + 1]);

		if (type == "s") {
			p << val.c_str();
		}
		else if (type == "i") {
			p << atoi(val.c_str());
		}
		else if (type == "f") {
			p << (float)(atof(val.c_str()));
		}
		else if (type == "b") {
			if (val == "true") p << true;
			else p << false;
		}
		else {
			usage();
		}

		idx += 2;
	}

	p << osc::EndMessage;
	//p << osc::EndBundle;

	transmitSocket.Send(p.Data(), p.Size());

	return 0;
}