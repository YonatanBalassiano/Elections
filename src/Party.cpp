#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) 
{
    // You can change the implementation of the constructor, but not the signature!

}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if (iter != -1){
        iter = iter +1;
        if (iter == 3){
            //choose party
            Agent selectedCoalition = mJoinPolicy->selectCoalition(*offers);

            //copy agent
            Agent newAgent(selectedCoalition);
            int agentId = s.getNumOfAgent();
            newAgent.setAfterCopy(agentId,mId);

            s.addAgent(newAgent);
            //change status
            setState(Joined);

        }
    }
        // TODO: implement this method

    // copy the agent to the simulation agent vector
}


int Party:: getId(){
    return mId;
}

bool Party :: setOffer(Agent &agent){
    if (iter == -1){
        setState(CollectingOffers);
        iter = 0;
    }
    bool isExist = false;
    for(int i = 0; i<iter && !isExist; i++){
        if(offers[i]->getCoalition() == agent.getCoalition()){isExist = true;}
    }
    if (!isExist){offers[iter] = &agent;}

    return isExist ? false : true;

}


Agent MandatesJoinPolicy :: selectCoalition(Agent *offers){
    return offers[0];
    //take the mandats by coalition array
    //from the givven offers, return the one with the most mandats

}

Agent LastOfferJoinPolicy :: selectCoalition(Agent *offers){
    // for (int i = 2; i<=0 ;i++){
    //     if (offers[i] == nullptr) {return offers[i];}
    // }
    return offers[0];
}