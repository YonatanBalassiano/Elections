#include "Graph.h"
#include "Simulation.h"


Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

void Graph:: partiesStep(Simulation &s){
    int verticesSize = mVertices.size();
    for(int i = 0; i<verticesSize;i++){
        mVertices[i].step(s);
    }
}

const vector<Party> &Graph :: getAllParties() const{
    return mVertices;
}

void Graph:: setOfferToPartyId(Agent &agent, int id) {
    mVertices[id].setOffer(agent);
}


