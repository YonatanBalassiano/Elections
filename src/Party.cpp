#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"
#include "Agent.h"
#include <vector>

using std::vector;

//implement Rule of 5

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) 
{
    // You can change the implementation of the constructor, but not the signature!

}

Party:: Party(const Party &party):mId(party.mId), mName( party.mName), mMandates(party.mMandates), mJoinPolicy(party.mJoinPolicy), mState(party.mState){
    iter = party.iter;
    int offersSize = party.offers.size();
    for(int i = 0; i<offersSize;i++){
        offers.push_back(party.offers[i]);
    }
    mJoinPolicy = party.mJoinPolicy->clone();
}

Party:: Party(Party &&other):mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState){
    iter = other.iter;
    offers = other.offers;
    other.mJoinPolicy = nullptr;
}

Party &Party :: operator=(Party &&other){
    if(mJoinPolicy){delete mJoinPolicy;}
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    *mJoinPolicy = *other.mJoinPolicy;
    mState = other.mState;
    iter = other.iter;
    offers = other.offers;
    other.mJoinPolicy=nullptr;
    return*this;

}

Party &Party :: operator=(const Party &other){
    if(this!=&other){
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy->clone();
        mState = other.mState;
        iter = other.iter;

        int offersSize = other.offers.size();
        for(int i = 0; i<offersSize;i++){
            offers.push_back(other.offers[i]);   
        }
    }
    return *this;
}

Party ::~Party()
{
    if(mJoinPolicy){delete mJoinPolicy;}
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
            Agent selectedCoalition = mJoinPolicy->selectCoalition(offers, s);

            //copy agent
            Agent newAgent(selectedCoalition);
            int agentId = s.getNumOfAgent();
            newAgent.setAfterCopy(agentId,mId);
            s.addAgent(newAgent);
            setState(Joined);
        }
    }
}

int Party:: getId() const {
    return mId;
}

void Party :: setOffer(const Agent &agent){
    if (iter == -1){
        setState(CollectingOffers);
        iter = 0;
    }
    offers.push_back(agent.getId());
}

bool Party :: alreadyOffer(int coalition, Simulation &sim)const{
    bool isExist = false;

    int offersSize = offers.size();
    for(int i = 0; i<offersSize && !isExist; i++){
        const Agent &agent = sim.getAgentById(offers[i]);
        if(agent.getCoalition() == coalition){return true;}
    }
    return false;
}



// --------- JoinPolicy ----------//
Agent  MandatesJoinPolicy :: selectCoalition(const vector<int> &offers, Simulation &sim) const{
    int max = 0;
    
    int offersSize = offers.size();
    for(int i = 0; i<offersSize-1;i++){
        if (sim.getCoalitionSize(sim.getAgentById(offers[i]).getCoalition())< 
        sim.getCoalitionSize(sim.getAgentById(offers[i+1]).getCoalition())){
            max = i+1;
        }
    }
    const Agent &maxAgent = sim.getAgentById(offers[max]);
    return maxAgent;

}

Agent  LastOfferJoinPolicy :: selectCoalition(const vector<int> &offers, Simulation &sim) const {
    const Agent &lastAgent = sim.getAgentById(offers[offers.size()-1]);
    return lastAgent;
}

MandatesJoinPolicy* MandatesJoinPolicy ::clone(){
    return new MandatesJoinPolicy(*this);
}

LastOfferJoinPolicy * LastOfferJoinPolicy ::clone(){
        return new LastOfferJoinPolicy(*this);
}