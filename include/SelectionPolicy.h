#pragma once

class SelectionPolicy { 
    public:
        int step() = 0;
        void sortParties() = 0;

};

class MandatesSelectionPolicy: public SelectionPolicy{ 
    public:
        int select();
        void sortParties(vector<Party> , Simulation &);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ public:
    public:
        int select();
        void sortParties(vector<Party> , Simulation &);
 
    
    };