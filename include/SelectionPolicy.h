#pragma once

class SelectionPolicy { 
    public:
     int select();
        virtual void sortParties(vector<Party> , Simulation &) = 0;
};

class MandatesSelectionPolicy: public SelectionPolicy{ 
    
    public:
        
        int select();
        void sortParties  (vector<Party> , Simulation &);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ public:
    public:
        
        int select();
        void sortParties(vector<Party> , Simulation &);
    };

