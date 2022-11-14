#include "Agent.h"
#include "SelectionPolicy.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    
    //add parties the sorted parties.
    
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{  
    if (parties.size()==0){
        mSelectionPolicy -> sortParties(parties, sim);
    }

    //every step choose the next one 

    // copy the agent to the simulation agent vector

    //delete the party from the parties vector


    

    
}

int MandatesSelectionPolicy :: select(){
    return 1;
}
int EdgeWeightSelectionPolicy :: select(){
    return 2;
}

void MandatesSelectionPolicy :: sortParties(vector<Party> parties , Simulation &sim){
    //to implement --> sort by mandats
}
void EdgeWeightSelectionPolicy :: sortParties(vector<Party> parties , Simulation &sim){
    //to implement --> sort by weight
}





