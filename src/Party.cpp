#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"
#include "Agent.h"
#include <vector>

using std::vector;



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
            const vector<Agent> *temp = &offers;
            Agent selectedCoalition = mJoinPolicy->selectCoalition(*temp, s);

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


int Party:: getId() const {
    return mId;
}

void Party :: setOffer(const Agent &agent){
    if (iter == -1){
        setState(CollectingOffers);
        iter = 0;
    }
    offers.push_back(agent);
}


bool Party :: alreadyOffer(int coalition)const{
    bool isExist = false;
    for(int i = 0; i<offers.size() && !isExist; i++){
        if(offers[i].getCoalition() == coalition){return true;}
    }
    return false;
}




Agent MandatesJoinPolicy :: selectCoalition(const vector<Agent> &offers, Simulation &sim) const{
    int max = 0;
    for(int i = 0; i>offers.size()-1;i++){
        if (sim.getCoalitionSize(offers[i].getCoalition())> 
        sim.getCoalitionSize(offers[i+1].getCoalition())){
            max = i+1;
        }
        return offers[i];
    }

}

Agent LastOfferJoinPolicy :: selectCoalition(const vector<Agent> &offers, Simulation &sim) const {
    const Agent &maxAgent = offers[0];
    return maxAgent;
}