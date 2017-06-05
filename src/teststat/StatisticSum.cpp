#include <StatisticSum.h>
#include <ContainerTools.hpp>

StatisticSum::StatisticSum(TestStatistic& s1_, TestStatistic& s2_){
    AddStat(s1_);
    AddStat(s2_);
}

double
StatisticSum::Evaluate(){
    double sum = 0;
    for(size_t i = 0; i < fStats.size(); i++)
        sum += fStats.at(i) -> Evaluate();
    return sum;
}

void
StatisticSum::SetParameters(const ParameterDict& params_){
    for(size_t i = 0; i < fStats.size(); i++)
        fStats.at(i) -> SetParameters(params_);
}

ParameterDict
StatisticSum::GetParameters() const{
    ParameterDict combinedParams;
    for(size_t i = 0; i < fStats.size(); i++){
        ParameterDict params = fStats.at(i) -> GetParameters();
        combinedParams.insert(params.begin(), params.end());
    }
    return combinedParams;
}

std::vector<std::string> 
StatisticSum::GetParameterNames() const{
    return ContainerTools::GetKeys(GetParameters());
}

void
StatisticSum::RegisterFitComponents(){
    for(size_t i = 0; i < fStats.size(); i++)
        fStats.at(i)->RegisterFitComponents();
}

void 
StatisticSum::AddStat(TestStatistic& st_){
    fStats.push_back(&st_);
}

StatisticSum operator + (TestStatistic& t1_, TestStatistic& t2_){
    return StatisticSum(t1_, t2_);
}

StatisticSum operator + (StatisticSum& sum_, TestStatistic& t2_){
    StatisticSum newSum = sum_;
    newSum.AddStat(t2_);
    return newSum;
}

StatisticSum Sum(const std::vector<TestStatistic*>& stats_){
    StatisticSum newSum;
    for(size_t i = 0; i < stats_.size(); i++)
        newSum.AddStat(stats_.at(i));
    return newSum;
}
