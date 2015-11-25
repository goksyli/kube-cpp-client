#pragma once
#include <curl/curl.h>
#include <string>
#include <mutex>
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <sstream>
class curlclient;
class request
{
public:
//    friend void thread_get(CURL *c,request& req);
    friend size_t wr_list(char *buffer, size_t size, size_t nmemb, void * user_p);
    friend size_t wr_watch(char *buffer, size_t size, size_t nmemb, void * user_p);
    request(std::string verb, 
            std::string url,std::string body,curlclient *c);
    virtual ~request();
    std::string list();
    void watch();
    std::string read_stream(); 
private:
    std::string mUrl;
    std::string mVerb;
    std::thread worker;
    std::string post_body;
    std::mutex locker;
    std::string strResult;
    std::string error;
    std::queue<std::string> httpResults;
    std::stringstream response;
    typedef size_t (*writecb)(char *buffer, size_t size, size_t nmemb, void *user_p);
    writecb listfunc;
    writecb watchfunc;
    CURLcode res;
    curlclient * mclient;
};

class curlclient
{
public:
    curlclient();

    virtual ~curlclient();

    request* Get(std::string url);
    //TODO add post body parameter
    request* Post(std::string url,std::string body);
    request* Delete(std::string url);

    CURL * get_curl();
private:
    CURL *c;
};

extern void thread_get(curlclient* client, CURLcode& res);
extern size_t wr_list(char *buffer, size_t size, size_t nmemb, void * user_p);
extern size_t wr_watch(char *buffer, size_t size, size_t nmemb, void * user_p);
