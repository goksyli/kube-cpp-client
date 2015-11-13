#include <restless.hpp>
#include <json.hpp>
#include <iostream>
using Http = asoni::Handle;
using json = nlohmann::json;
int main(int argc, char **argv)
{
    auto result = Http().get("http://127.0.0.1:8080/api/v1/pods")
        .exec();

    auto response = json::parse(result.body);

    std::cout << response << std::endl;



    return 0;
}
