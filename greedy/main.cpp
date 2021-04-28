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


std::pair<float, float> GetBestSeg(const std::vector<std::pair<float, float>>& vec,
                                    std::pair<float, float> point)
{
    float current_X = point.second;
    for (auto i : vec)
    {        
        if (i.first <= current_X &&
            //i.first > point.first &&
            i.second > point.second)
            point = i;
    }

    return point;
}


int CalcCount(const std::vector<std::pair<float, float>>& vec)
{
    int count = 0;
    std::pair<float, float> current_point = {0,0};

    for (auto i : vec)
    {
        current_point = GetBestSeg(vec, current_point);
        ++count;
        
        if (current_point.second >= 1)
            return count;
    }

    return -1;
}


int main()
{
    auto vec = GetVector(); 

    int count  = CalcCount(vec);

    if (count != -1)
        std::cout << count << std::endl;
    else
        std::cout << "Unsolvable" << std::endl;

    return 0;
}