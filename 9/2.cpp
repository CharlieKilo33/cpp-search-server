#include "log_duration.h"

#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<float> ComputeAvgTemp(const vector<vector<float>>& measures) {
  if(measures.empty()){
    return {};
  }

  struct AvgTemp{
    float temp = 0.f;
    int amount = 0;
  };

  vector<AvgTemp>res(measures[0].size());

  for(int i = 0; i < measures.size(); ++i){ //количество
    for(int j = 0; j < measures[0].size(); ++j){
      measures[i][j] > 0 ? res[j].temp += measures[i][j] : res[j].temp += 0;
      measures[i][j] > 0 ? res[j].amount += 1 : res[j].amount += 0;
    }
  }

  vector<float> temp_res;
  temp_res.reserve(res.size());

  for(auto [temp, amount] : res){
    temp > 0 ? temp_res.push_back(temp / amount) : temp_res.push_back(0);
  }

  return temp_res;
}

vector<float> GetRandomVector(int size) {
  static mt19937 engine;
  uniform_real_distribution<float> d(-100, 100);

  vector<float> res(size);
  for (int i = 0; i < size; ++i) {
    res[i] = d(engine);
  }

  return res;
}

int main() {
  vector<vector<float>> data;
  data.reserve(5000);

  for (int i = 0; i < 5000; ++i) {
    data.push_back(GetRandomVector(5000));
  }

  vector<float> avg;
  {
    LOG_DURATION("ComputeAvgTemp"s);
    avg = ComputeAvgTemp(data);
  }

  cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl;

}