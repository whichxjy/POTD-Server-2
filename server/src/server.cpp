#include "PotdService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class PotdServiceHandler : virtual public PotdServiceIf {
    private:
        std::vector<Poem> poems;

    public:
        PotdServiceHandler();

        // Get a random poem from server
        void getRandomPoem(Poem& _return);    
};

PotdServiceHandler::PotdServiceHandler() {
    ::std::ifstream file;
    file.open("../poems.txt");

    if (file.is_open()) {
        ::std::string line;
        ::std::string reading;
        int32_t count = 0;

        while (::std::getline(file, line)) {
            if (line != "%") {
                reading += (line + "\n");
            }
            else {
                count += 1;
                poems.emplace_back(count, reading);
                reading = "";
            }
        }
    }
}

void PotdServiceHandler::getRandomPoem(Poem& _return) {
    srand(time(NULL));
    _return = poems[rand() % poems.size()];
}

int main(int argc, char **argv) {
    int port = 9090;
    ::std::shared_ptr<PotdServiceHandler> handler(new PotdServiceHandler());
    ::std::shared_ptr<TProcessor> processor(new PotdServiceProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}

