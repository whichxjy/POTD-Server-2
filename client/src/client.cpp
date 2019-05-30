#include "PotdService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <iostream>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

int main(int argc, char **argv) {
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    PotdServiceClient client(protocol);

    try {
        transport->open();

        Poem poem;
        client.getRandomPoem(poem);

        std::cout << "[ID]: " << poem.id << std::endl;
        std::cout << "[Content]:\n" << poem.content << std::endl;

        transport->close();
    } catch (TException& tx) {
        std::cout << "ERROR: " << tx.what() << std::endl;
    }

    return 0;
}

