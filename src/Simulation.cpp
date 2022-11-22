#include "Simulation.h"
#include <vector>
#include <map>
#include <iostream>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    int agentSize = mAgents.size();
   for(int i =0; i<agentSize;i++){
    //push into the vector the amount of mandats per coalition.
    coalitionCounter.push_back(mGraph.getParty(mAgents[i].getPartyId()).getMandates());
    mAgents[i].setCoalition(i);
   } 

}

void Simulation::step()
{
    auto &temp = *this;

    mGraph.partiesStep(temp);
        
    int agentSize = mAgents.size();
    for (int i = 0; i < agentSize; i++)
    {
        mAgents[i].step(temp);
    }
    
}

bool Simulation::shouldTerminate() const
{
    //check every coalition for having more then 60 mandats
    int coalitionNum = coalitionCounter.size();
    for (int i =0; i<coalitionNum;i++){
        if (coalitionCounter[i] > 60)
        return true;
    }
    
    int size1 = mAgents.size();
    int size2 = mGraph.getNumVertices();
    return size1 == size2;
    
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

const int Simulation::getCoalitionSize(const int &coalition) {
    return coalitionCounter[coalition];
}

void Simulation :: setOfferToPartyId(Agent & agent ,int id){
    
    mGraph.setOfferToPartyId(agent, id);
}

const Agent & Simulation ::getAgentById(int id){
    return mAgents[id];
}



/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> coalition (coalitionCounter.size(),vector<int>());

        int agentSize = mAgents.size();
        for(int i = 0; i<agentSize;i++){

        int coalitionNum = mAgents[i].getCoalition();
        int partyId = mAgents[i].getPartyId();
        coalition[coalitionNum].push_back(partyId);
        }

    return coalition;
}

int Simulation::getNumOfAgent(){
    return mAgents.size();
}

void Simulation::addAgent(Agent &agent){
    mAgents.push_back(agent);

    //add mandats to coalition counter
    const Party &party = mGraph.getParty(agent.getPartyId());
    coalitionCounter[agent.getCoalition()] += party.getMandates();
}