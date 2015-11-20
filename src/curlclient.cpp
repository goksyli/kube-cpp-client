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
   return new request(url,this);
}

CURL * curlclient::get_curl()
{
    return this->c;
}

void thread_get(curlclient* client,CURLcode &res)
{
    std::cout << "I am in thread get" << std::endl;
    std::cout << "client is " << client << std::endl;
    res = curl_easy_perform(client->get_curl());
}

request::request(std::string url, curlclient *c)
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
    curl_easy_setopt(mclient->get_curl(), CURLOPT_URL,mUrl.c_str());
    /*register write call back and call back context*/
    curl_easy_setopt(mclient->get_curl(), CURLOPT_WRITEDATA,this);
    curl_easy_setopt(mclient->get_curl(), CURLOPT_WRITEFUNCTION,listfunc);
    curl_easy_setopt(mclient->get_curl(), CURLOPT_ERRORBUFFER, error.c_str());
   
    res = curl_easy_perform(mclient->get_curl());

    return strResult; 
}

void request::watch()
{
    curl_easy_setopt(mclient->get_curl(), CURLOPT_URL,mUrl.c_str());
    /*register write call back and call back context*/
    curl_easy_setopt(mclient->get_curl(), CURLOPT_WRITEDATA,this);
    curl_easy_setopt(mclient->get_curl(), CURLOPT_WRITEFUNCTION,watchfunc);
    curl_easy_setopt(mclient->get_curl(), CURLOPT_ERRORBUFFER, error.c_str());
    std::cout << "mclient curl is " << mclient << std::endl;
    worker = std::thread(thread_get, mclient, std::ref(res));
//    curl_easy_perform(mclient->get_curl());

    std::cout << "start sleep for 10 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

std::string request::read_stream()
{
//    std::cout << "I am in read_stream" << std::endl;
// TODO use conditon variable and lamda for spurious wakeup
    std::string json;
    while( json.empty()){
        locker.lock();
#if 1
        if( !httpResults.empty())
            json = httpResults.front();
#else
            response >> json;
#endif
        locker.unlock();
    }
    httpResults.pop();
//    std::cout << "json is " << json << std::endl;
    return json;
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

//    std::cout << "I am in wr_watch." << std::endl;
    request *req = static_cast<request*>(user_p); 
    size_t realsize = size * nmemb;
    std::string strbuf(buffer, realsize);
  
//    std::cout << "str buf is " << strbuf << std::endl;
    req->locker.lock();
#if 1
    req->httpResults.push(strbuf);

#else
    req->response << strbuf;
#endif
    req->locker.unlock();
    
    return realsize;
}
