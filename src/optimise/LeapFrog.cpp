#include <LeapFrog.h>

double
LeapFrog::IntersectionTime(double wall_, double initPos_, double vel_){
    return (wall_ - initPos_)/vel_;    
}


void
LeapFrog::FirstIntersectionTime(const ParameterDict& initPos_,
                                const ParameterDict& momenta_, const ParameterDict& masses_,
                                const ParameterDict& minima_, const ParameterDict& maxima_,
                                double epsilon_,
                                std::string& dim_, double& crossTime_
                                ){
    crossTime_ = -1;
    dim_ = "";

    for(ParameterDict::const_iterator it = initPos_.begin(); it != initPos_.end(); ++it){
        double vel = momenta_.at(it->first)/masses_.at(it->first);
        double mintime = IntersectionTime(minima_.at(it->first), initPos_.at(it->first), vel);
        double maxtime = IntersectionTime(maxima_.at(it->first), initPos_.at(it->first), vel);

        bool mincrossed  = (mintime > 0 && mintime < epsilon_);
        bool maxcrossed  = (maxtime > 0 && maxtime < epsilon_);

        if(!mincrossed && !maxcrossed)
            continue;
        
        double time;
        if(mincrossed)
            time = mintime;
        else if(maxcrossed)
            time = maxtime;


        if(crossTime_ == -1 || time < crossTime_){
            crossTime_ = time;
            dim_ = it->first;
        }

    }
}
