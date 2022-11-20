#include "Agent.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Party.h"
#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;


//implement Rule of 5

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
}

Agent::Agent(const Agent &Agent): mAgentId(Agent.mAgentId) , mPartyId(Agent.mPartyId) , mSelectionPolicy(Agent.mSelectionPolicy)
{
    // build the currect class
    int type = Agent.mSelectionPolicy->whoAmI();
    if (type == 0)
    {
        mSelectionPolicy = new MandatesSelectionPolicy();
    }
    else
    {
        mSelectionPolicy = new EdgeWeightSelectionPolicy();
    }
    coalition = Agent.coalition;
}

Agent::Agent(Agent &&other): mAgentId(other.mAgentId) , mPartyId(other.mPartyId) , mSelectionPolicy(other.mSelectionPolicy){
    coalition = other.coalition;
    other.mSelectionPolicy = nullptr;
}

Agent &Agent :: operator=(Agent &&other){
    if(mSelectionPolicy){delete mSelectionPolicy;}
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    *mSelectionPolicy = *other.mSelectionPolicy;
    coalition = other.coalition;
    other.mSelectionPolicy = nullptr;
    return *this;
}

Agent &Agent :: operator=(const Agent &other){
    if(this!=&other){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        *mSelectionPolicy = *other.mSelectionPolicy;
        coalition = other.coalition;
    }
    return *this;
}

Agent :: ~Agent(){
    if(mSelectionPolicy){delete mSelectionPolicy;}
}

//Implement functions

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent ::setCoalition(int a)
{
    coalition = a;
}

int Agent ::getCoalition() const
{
    return coalition;
}

void Agent ::setAfterCopy(int selfId, int partyId)
{
    mAgentId = selfId;
    mPartyId = partyId;
}

void Agent::step(Simulation &sim)
{
    int currSelection = mSelectionPolicy->select(*this, sim);
    if (currSelection != -1)
    {
        Agent &a = *this;
        sim.setOfferToPartyId(a, currSelection);
    }
}


// --------- SelectionPolicy ----------

int MandatesSelectionPolicy ::select(const Agent &agent, Simulation &sim)
{
    const Graph &gr = sim.getGraph();
    const vector<Party> &parties = gr.getAllParties();
    int output = -1;
    int partySize = parties.size();
    for (int i = 0; i < partySize; i++)
    {
        switch (parties[i].getState())
        {
        case Joined:
            break;
        case Waiting:
            if (output == -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0)
            {
                output = i;
            }
            else if (output != -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0 &&
                     parties[output].getMandates() < parties[i].getMandates())
            {
                output = i;
            }
            break;
        case CollectingOffers:
            if (output == -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0 && !parties[i].alreadyOffer(agent.getCoalition(), sim))
            {
                output = i;
            }
            else if (output != -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0 &&
                     parties[output].getMandates() < parties[i].getMandates() &&
                     !parties[i].alreadyOffer(agent.getCoalition(), sim))
            {
                output = i;
            }
            break;
        }
    }

    return output == -1 ? -1 : parties[output].getId();
}

int EdgeWeightSelectionPolicy ::select(const Agent &agent, Simulation &sim)
{
    const Graph &gr = sim.getGraph();
    const vector<Party> &parties = gr.getAllParties();
    int output = -1;
    int partySize = parties.size();
    for (int i = 0; i < partySize; i++)
    {
        switch (parties[i].getState())
        {
        case Joined:
            break;
        case Waiting:
            if (output == -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0)
            {
                output = i;
            }
            else if (output != -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) >
                     gr.getEdgeWeight(parties[output].getId(), agent.getPartyId()))
            {
                output = i;
            }
            break;
        case CollectingOffers:

            if (output == -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0 && !parties[i].alreadyOffer(agent.getCoalition(), sim))
            {
                output = i;
            }
            else if (output != -1 && gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) > 0 &&
                     gr.getEdgeWeight(parties[output].getId(), agent.getPartyId()) < gr.getEdgeWeight(parties[i].getId(), agent.getPartyId()) &&
                     !parties[i].alreadyOffer(agent.getCoalition(), sim))
            {
                output = i;
            }
            break;
        }
    }

    return output == -1 ? -1 : parties[output].getId();
}

int MandatesSelectionPolicy ::whoAmI()
{
    return 0;
}

int EdgeWeightSelectionPolicy ::whoAmI()
{
    return 1;
}

