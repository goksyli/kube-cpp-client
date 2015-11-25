#include <curlclient.h>
using namespace std;

int main()
{
    curlclient client;
    request *req = client.Delete("http://127.0.0.1:8080/api/v1/namespaces/default/pods/counter");
    string resq = req->list();
    cout << resq << endl;
    return 0;
}
