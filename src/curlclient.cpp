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

void thread_get(CURL *c,CURLcode &res)
{
    
    res = curl_easy_perform(c);
}

request::request(std::string url, CURL *c)
    :mUrl(url),
    listfunc(&wr_list),
    watchfunc(&wr_watch),
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
    curl_easy_setopt(mclient, CURLOPT_URL,mUrl.c_str());
    /*register write call back and call back context*/
    curl_easy_setopt(mclient, CURLOPT_WRITEDATA,this);
    curl_easy_setopt(mclient, CURLOPT_WRITEFUNCTION,listfunc);
    curl_easy_setopt(mclient, CURLOPT_ERRORBUFFER, error.c_str());
   
    res = curl_easy_perform(mclient);

    return strResult; 
}

void request::watch()
{
    
    curl_easy_setopt(mclient, CURLOPT_URL,mUrl.c_str());
    /*register write call back and call back context*/
    curl_easy_setopt(mclient, CURLOPT_WRITEDATA,this);
    curl_easy_setopt(mclient, CURLOPT_WRITEFUNCTION,watchfunc);
    curl_easy_setopt(mclient, CURLOPT_ERRORBUFFER, error.c_str());

    worker = std::thread(thread_get, mclient, std::ref(res));
}

size_t wr_list(char *buffer, size_t size, size_t nmemb, void *user_p)
{
    request *req = static_cast<request*>(user_p); 
    size_t realsize = size * nmemb;
    std::string strbuf(buffer, realsize);
    req->strResult = strbuf;
    return realsize;
}
size_t wr_watch(char *buffer, size_t size, size_t nmemb, void *user_p)
{

    request *req = static_cast<request*>(user_p); 
    size_t realsize = size * nmemb;
    std::string strbuf(buffer, realsize);
   
    req->locker.lock();
    req->httpResults.push(strbuf);
    req->locker.unlock();
    
    return realsize;
}
