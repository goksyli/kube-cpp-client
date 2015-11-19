#include <curlclient.h>
#include <iostream>
#include <httpurl.hpp>
int main(int argc, char **argv)
{
    std::string url = "http://127.0.0.1:8080/api/v1/pods";

    curlclient client;
    request * req = client.Get(url);
    std::cout << req->list();
    return 0;
}
