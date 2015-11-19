#include <curlclient.h>
#include <iostream>

int main(int argc, char **argv)
{
    curlclient client;
    request * req = client.Get("http://127.0.0.1:8080/api/v1/pods");
    std::cout << req->list();
    return 0;
}
