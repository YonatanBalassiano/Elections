#pragma once

class JoinPolicy {
    public:
        virtual Agent selectCoalition(Agent offers[3]) =0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
         Agent selectCoalition(Agent offers[3]);
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
         Agent selectCoalition(Agent offers[3]);
};