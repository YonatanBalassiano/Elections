#include "Simulation.h"
#include <vector>
#include <map>
#include <iostream>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
   for(int i =0; i<mAgents.size();i++){
    //push into the vector the amount of mandats per coalition.
    coalitionCounter.push_back(mGraph.getParty(mAgents[i].getPartyId()).getMandates());
    mAgents[i].setCoalition(i);
   } 
}

void Simulation::step()
{
    auto &temp = *this;

    mGraph.partiesStep(temp);

    for (int i = 0; i < mAgents.size(); i++)
    {
        mAgents[i].step(temp);
    }
    
}

bool Simulation::shouldTerminate() const
{
    //check every coalition for having more then 60 mandats
    for (int i =0; i<coalitionCounter.size();i++){
        if (coalitionCounter[i] > 60)
        return true;
    }

    //check if every Party has an agent -> all parties is joined
    return mAgents.size() == mGraph.getNumVertices();
      
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



/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> coalition = vector<vector<int>>();

    int index = 0; 
    while (index<mAgents.size()){
        if (index<coalitionCounter.size()){
            int partyId = mAgents[index].getPartyId();
            coalition.push_back(vector<int>(partyId));
            index++;
        }
        else{
        int coalitionNum = mAgents[index].getCoalition();
        int partyId = mAgents[index].getPartyId();
        coalition[coalitionNum].push_back(partyId);
        }
    }
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    std::cout << "return" << std::endl;

    return coalition;
}

int Simulation::getNumOfAgent(){
    return mAgents.size();
}

void Simulation::addAgent(Agent &agent){
    mAgents.push_back(agent);
}