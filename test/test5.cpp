#include <curlclient.h>
#include <json.hpp>

using json = nlohmann::json;

int main()
{

    const std::string url = "http://127.0.0.1:8080/api/v1/namespaces/default/pods";


    auto j = R"(
        {
            "apiVersion": "v1",
            "kind": "Pod",
            "metadata": {
                "name": "counter",
                "labels": {
                    "app": "counter"
                }
            },
            "spec": {
                "containers": [
                    {
                    "name": "counter",
                    "image": "nginx",
                    "ports": [
                        {
                        "containerPort": 80,
                        "hostPort": 8081
                        }
                    ]
                    }
                 ],
            "restartPolicy": "Never"
            }
        }
    )"_json;

    std::string post_body = j.dump();
    curlclient client;

    request * req = client.Post(url,post_body);
    std::string result = req->list();

    std::cout << result << std::endl;

    return 0;
}
