#pragma once

class SelectionPolicy { 
    public:
     int select();
        virtual void sortParties(vector<Party> , Simulation &) = 0;

        virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy: public SelectionPolicy{ 
    
    public:
        
        int select();
        void sortParties  (vector<Party> , Simulation &);

        ~ MandatesSelectionPolicy() = default;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ public:
    public:
        
        int select();
        void sortParties(vector<Party> , Simulation &);

        ~ EdgeWeightSelectionPolicy() = default;
    };

