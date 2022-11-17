#include "Agent.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Party.h"
#include <vector>
#include <algorithm>    
#include <iostream>

using std::vector;



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
    int currSelection = mSelectionPolicy->select(*this,sim);
    if (currSelection != -1){
        Agent &a = *this;
        sim.setOfferToPartyId(a,currSelection);

    }

    
}

int MandatesSelectionPolicy ::select(const Agent &agent , Simulation &sim){
    const Graph &gr = sim.getGraph();
    const vector<Party> &parties = gr.getAllParties();
    int output = -1; 
    for(int i = 0; i<parties.size();i++){
        switch (parties[i].getState())
        {
        case Joined:
                break;
        case Waiting:
        if (output == -1 && gr.getEdgeWeight(parties[i].getId(),agent.getPartyId()) > 0)
            {
                output = i;
            }
            else if(gr.getEdgeWeight(parties[i].getId(),agent.getPartyId())>0 && 
            parties[output].getMandates()<parties[i].getMandates()){
                output=i;
            }
            break;   
        case CollectingOffers:
        if(output == -1 && gr.getEdgeWeight(parties[i].getId(),agent.getPartyId()) > 0 &&!parties[i].alreadyOffer(agent.getCoalition()))
            {
                output = i;
            }
            else if(gr.getEdgeWeight(parties[i].getId(),agent.getPartyId())>0 && 
                parties[output].getMandates()<parties[i].getMandates() &&
                !parties[i].alreadyOffer(agent.getCoalition())){
                    output=i;
                }
            }
            break;
    }

    return output == -1 ? -1 : parties[output].getId();

}

int EdgeWeightSelectionPolicy ::select(const Agent &agent , Simulation &sim){
    const Graph &gr = sim.getGraph();
    const vector<Party> &parties = gr.getAllParties();
    int output = -1; 
    for(int i = 0; i<parties.size();i++){
        switch (parties[i].getState())
        {
        case Joined:
                break;
        case Waiting:
            if (output == -1 && gr.getEdgeWeight(parties[i].getId(),agent.getPartyId()) > 0)
            {
                output = i;
            }
            else if(gr.getEdgeWeight(parties[i].getId(),agent.getPartyId()) > 
            gr.getEdgeWeight(parties[output].getId(),agent.getPartyId()))
            {
            output=i;
            } 
                
            break;   
        case CollectingOffers:
            if(output == -1 && gr.getEdgeWeight(parties[i].getId(),agent.getPartyId()) > 0 &&!parties[i].alreadyOffer(agent.getCoalition()))
            {
                output = i;
            }
            else if(gr.getEdgeWeight(parties[i].getId(),agent.getPartyId())>0 && 
                parties[output].getMandates()<parties[i].getMandates() &&
                !parties[i].alreadyOffer(agent.getCoalition())){
                    output=i;
                }
            }
            break;
    }

    return output == -1 ? -1 : parties[output].getId();



}




    









