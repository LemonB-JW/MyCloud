//
// Created by Xuan Wang on 12/3/19.
//
#include <../grpc/MasterClient.h>
#include <iostream>
#include <memory>
#include <string>

void get_servers(std::string username) {
    MasterClient masterClient(
            grpc::CreateChannel(
                    "127.0.0.1:8001",
                    grpc::InsecureChannelCredentials()
            )
    );

    std::string user = "Alice";
    std::vector<std::string> response = masterClient.getServerList(user);
    std::cout << "size: " << response.size() << "Servers: " << response[0] << std::endl;
}

int main(int argc, char** argv) {
    get_servers("Alice");
}
