#pragma once

class JoinPolicy {
    public:
        virtual Agent selectCoalition(Agent offers[3]) =0;

        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
         Agent selectCoalition(Agent offers[3]);

         ~MandatesJoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
         Agent selectCoalition(Agent offers[3]);
        
         ~LastOfferJoinPolicy() = default;

};