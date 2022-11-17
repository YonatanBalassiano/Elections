// // if heavent done it yet, sort the parties accoding to selection policy
//     if (parties.size()==0){
//         //copy the parties to the agent DB
//         const Graph &tempGraph = sim.getGraph();
//         const vector<Party> &tempVector = tempGraph.getAllParties();
//         for(int i = 0; i<tempVector.size();i++){
//             parties.push_back(&tempVector[i]);
//         }
        
//         //delete all of the non-partnership able parties
//         for(int i = 0; i<parties.size();i++){
//             if(tempGraph.getEdgeWeight(parties[i].getId(),mPartyId)==0){
//                 parties.erase(parties.begin() + i);
//             }
//         }

//         //sort the parties
//         mSelectionPolicy->sortParties(parties,sim);

//         }
//     bool madeOffer = false;

//     //select the next Party to make offer

//     while(!madeOffer & parties.size()>0){

//         //get hands on the first Party in the vector
//         Party currParty = parties[0];
//         parties.erase(parties.begin());
//         // Agent &tempAgent = *this;
//         switch (currParty.getState())
//         {
//             case Joined:
//                 break;
//             case Waiting:
//                 currParty.setOffer(*this);
//                 madeOffer = true;
//                 break;
//             case CollectingOffers:
//                 if (currParty.setOffer(*this))
//                 {
//                     madeOffer = true;
//                 }
//                 break;
       
//         }
//     }