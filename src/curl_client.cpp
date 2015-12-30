#include <curl_client.h>
#include <curl/curl.h>
#include <iostream>
std::string curl_client::Do(http_request req)
{
    std::string result;
    CURL *easyhandle;
    CURLcode res;
    easyhandle = curl_easy_init();

    if(easyhandle){

   //     curl_easy_setopt(easyhandle,CURLOPT_WRITEFUNCTION,write_cb);
    //    curl_easy_setopt(easyhandle,CURLOPT_WRITEDATA,this);

        curl_easy_setopt(easyhandle,CURLOPT_URL,req.url.c_str());
        if( req.verb == "POST" )
        {
            curl_easy_setopt(easyhandle,CURLOPT_POSTFIELDS,req.body.c_str());
        }
        else if( req.verb == "DELETE" )
        {
            curl_easy_setopt(easyhandle,CURLOPT_CUSTOMREQUEST,"DELETE");
        }

        res = curl_easy_perform(easyhandle);

        if( res != CURLE_OK ){
            std::cerr << req.verb <<" failed"<< std::endl;
        }

        curl_easy_cleanup(easyhandle);
    }
    return result;
}

size_t curl_client::write_cb(char *ptr,size_t size, size_t nmemb,void *userp)
{

}
