#include <curlclient.h>
#include <thread>
curlclient::curlclient()
    :c(curl_easy_init())
{}

curlclient::~curlclient()
{
    curl_easy_cleanup(c);
}


request* curlclient::Get(std::string url)
{
//   threads.push_back(std::thread(thread_get,c,url));
   /*TODO need to consider where to put join*/
   return new request(url,this->c);
}

CURL * curlclient::get_curl()
{
    return this->c;
}

void thread_get(CURL *c,request& req)
{
    curl_easy_setopt(c, CURLOPT_URL,req.mUrl.c_str());
    /*register write call back and call back context*/
    curl_easy_setopt(c, CURLOPT_WRITEDATA,&req);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION,req.writefunc);
    curl_easy_setopt(c, CURLOPT_ERRORBUFFER, req.error.c_str());
    
    req.res = curl_easy_perform(c);
}

request::request(std::string url, CURL *c)
    :mUrl(url),
    writefunc(&Write_Data),
    mclient(c)
{
    /*don't wory, std::thread is moveable*/
//    worker = std::thread(thread_get, c ,*this);
}
request::~request()
{
    worker.join();
}

std::string request::list()
{
    worker = std::thread(thread_get, mclient,std::ref(*this));
    worker.join();
    return strResult; 
}


size_t Write_Data(char *buffer, size_t size, size_t nmemb, void * user_p)
{
    request *req = static_cast<request*>(user_p); 
    size_t realsize = size * nmemb;
    std::string strbuf(buffer, realsize);
    req->strResult = strbuf;
    req->locker.lock();

    req->httpResults.push(strbuf);
    req->locker.unlock();
    return realsize;
}
