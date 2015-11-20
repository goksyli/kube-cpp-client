#include <iostream>
#include <curlclient.h>
using namespace std;

int main()
{
    curlclient client;
    request * req = client.Get("http://127.0.0.1:8080/api/v1/watch/pods");
    req->watch();
    while(true)
        cout << req->read_stream();
    return 0;
}
