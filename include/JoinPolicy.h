#pragma once

class JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<int> &, Simulation &) const  =0;
        virtual ~JoinPolicy()=default;
        virtual JoinPolicy* clone()=0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<int> &, Simulation &) const ;
        virtual ~MandatesJoinPolicy()=default;
        virtual MandatesJoinPolicy* clone();

};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<int> &, Simulation &) const ;
        virtual ~LastOfferJoinPolicy()=default;
        virtual LastOfferJoinPolicy* clone();



};