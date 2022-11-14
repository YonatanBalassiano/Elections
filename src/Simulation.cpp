#include "Simulation.h"
#include <vector>
#include <map>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
   for(int i =0; i<mAgents.size();i++){
    //push into the vector the amount of mandats per coalition.
    coalitionCounter.push_back(mGraph.getParty(mAgents[i].getPartyId()).getMandates());
   } 
}

void Simulation::step()
{
    // TODO: implement this method
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
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return vector<vector<int>>();
}
