#include "Agent.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include <vector>
#include <algorithm>    



Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
        
}

Agent::Agent(const Agent &Agent){
    mAgentId = Agent.mAgentId;
    mPartyId = Agent.mPartyId;
    mSelectionPolicy = Agent.mSelectionPolicy;
    coalition = Agent.coalition;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent :: setCoalition(int a){
    coalition = a;
}

int Agent :: getCoalition() const {
    return coalition;
}

void Agent :: setAfterCopy(int selfId, int partyId){
    mAgentId = selfId;
    mPartyId = partyId;
}



void Agent::step(Simulation &sim)
{  
    // if heavent done it yet, sort the parties accoding to selection policy
    if (parties.size()==0){
        //copy the parties to the agent DB
        const Graph &tempGraph = sim.getGraph();
        const vector<Party> tempVector = tempGraph.getAllParties();
        vector<Party> partiesTemp(tempVector);

        //delete all of the non-partnership able parties
        for(int i = 0; i<partiesTemp.size();i++){
            if(tempGraph.getEdgeWeight(partiesTemp[i].getId(),mPartyId)==0){
                partiesTemp.erase(partiesTemp.begin()+i);
            }
        }

        //sort the parties
        mSelectionPolicy->sortParties(partiesTemp,sim);

        parties = partiesTemp;
    }
    bool madeOffer = false;

    //select the next Party to make offer

    while(!madeOffer & parties.size()>0){

        //get hands on the first Party in the vector
        Party currParty = parties[0];
        parties.erase(parties.begin());
        auto &tempAgent = *this;
        switch (currParty.getState())
        {
            case Joined:
                break;
            case Waiting:
                currParty.setOffer(tempAgent);
                madeOffer = true;
                break;
            case CollectingOffers:
                if (currParty.setOffer(tempAgent))
                {
                    madeOffer = true;
                }
                break;
       
        }
    }
    

}

void MandatesSelectionPolicy :: sortParties(vector<Party> parties , Simulation &sim)  {
    sort(parties.begin(), parties.end(),[](Party party1, Party party2){return party1.getMandates()>=party2.getMandates();});
}
void EdgeWeightSelectionPolicy :: sortParties(vector<Party> parties , Simulation &sim)  {
    const Graph &tempGraph = sim.getGraph();
    sort(parties.begin(), parties.end(),[](Party party1, Party party2,int mPartyId,Graph &tempGraph){ 
        int a = tempGraph.getEdgeWeight(party1.getId(),mPartyId);
        int b = tempGraph.getEdgeWeight(party2.getId(), mPartyId);
        return a>=b;
     });
}






