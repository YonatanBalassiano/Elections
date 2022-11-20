#pragma once

class JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<int> &, Simulation &) const  =0;
        virtual int whoAmI()=0;
        virtual ~JoinPolicy()=default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<int> &, Simulation &) const ;
        virtual int whoAmI();
        virtual ~MandatesJoinPolicy()=default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual Agent selectCoalition(const vector<int> &, Simulation &) const ;
        virtual int whoAmI();
        virtual ~LastOfferJoinPolicy()=default;


};