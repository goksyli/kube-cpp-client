#include <httpurl.hpp>
using namespace std;
int main(int argc, char **argv)
{
    httpurl u("http://127.0.0.1:8080/api/v1/pods");
    cout << "protocol: " << u.protocol << endl;
    cout << "domain: " << u.domain << endl;
    cout << "port: " << u.port << endl;
    cout << "path: " << u.path << endl;
    cout << "query: " << u.query << endl;
    return 0;

}

