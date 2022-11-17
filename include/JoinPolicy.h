#pragma once

class JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<Agent> &, Simulation &) const  =0;

        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
         virtual Agent selectCoalition(const vector<Agent> &, Simulation &) const ;

         virtual ~MandatesJoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
         virtual Agent selectCoalition(const vector<Agent> &, Simulation &) const ;
        
         virtual ~LastOfferJoinPolicy() = default;

};