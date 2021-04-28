#include <vector>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"


using json = nlohmann::json;


std::vector <std::pair<float, float>> GetVector()
{
    std::vector <std::pair<float, float>> vec;
    std::ifstream ifs{"data_file.json"};
    auto from_json = json::parse(ifs);

    for (auto v : from_json)
    {
        auto tmp = v.get<std::vector<float>>();        
        vec.push_back({tmp[0], tmp[1]});
    }

    return vec;
}


std::pair<float, float> GetFirstPoint(const std::vector <std::pair<float, float>> vec)
{
    std::pair<float, float> fp = {-1, -1};
    for (auto i : vec)
    {        
        if (i.first <= 0 && i.first > fp.first)
            fp = i;
    }
    return fp;
}



int main()
{
    auto vec = GetVector();

    std::vector<std::pair<float,float>> result = {vec[0]};    

    return 0;
}