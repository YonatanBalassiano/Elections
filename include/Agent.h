#pragma once

#include <vector>
#include "Graph.h"

using std::vector;



class SelectionPolicy;
class Simulation;
class Party;


class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent &);


    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setCoalition(int);
    int getCoalition() const;
    void setAfterCopy(int, int);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    vector<Party> parties;
    int coalition = 0; 
};
