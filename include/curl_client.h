#include "http_client.h"


class curl_client : public http_client
{
public:
    virtual std::string Do(http_request) override;
private:
    static size_t write_cb(char *ptr, size_t size,size_t nmemb,void *userp);
}
