#include <curl/curl.h>
#include <string>
#include <mutex>
#include <functional>
#include <vector>
#include <queue>
#include <thread>
class request
{
public:
//    friend void thread_get(CURL *c,request& req);
    friend size_t wr_list(char *buffer, size_t size, size_t nmemb, void * user_p);
    friend size_t wr_watch(char *buffer, size_t size, size_t nmemb, void * user_p);
    request(std::string url,CURL *c);
    virtual ~request();
    std::string list();
    void watch();
    void list_and_watch();
private:
    std::string mUrl;
    std::thread worker;
    std::mutex locker;
    std::string strResult;
    std::string error;
    std::queue<std::string> httpResults;
    typedef size_t (*writecb)(char *buffer, size_t size, size_t nmemb, void *user_p);
    writecb listfunc;
    writecb watchfunc;
    CURLcode res;
    CURL * mclient;
};

class curlclient
{
public:
    curlclient();

    virtual ~curlclient();

    request* Get(std::string url);

    CURL * get_curl();
private:
    CURL *c;
};

extern void thread_get(CURL *c, CURLcode& res);
extern size_t wr_list(char *buffer, size_t size, size_t nmemb, void * user_p);
extern size_t wr_watch(char *buffer, size_t size, size_t nmemb, void * user_p);
