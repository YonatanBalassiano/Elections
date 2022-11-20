#pragma once

class SelectionPolicy { 
    public:
        virtual int select(const Agent & , Simulation &)=0;
        virtual int whoAmI()=0;
        virtual ~SelectionPolicy()=default;
};

class MandatesSelectionPolicy: public SelectionPolicy{ 
    
    public:
        
        virtual int select(const Agent & , Simulation &);
        virtual int whoAmI();
        virtual ~MandatesSelectionPolicy()=default;

};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ public:
    public:
        
        virtual int select(const Agent & , Simulation &);
        virtual int whoAmI();
        virtual ~EdgeWeightSelectionPolicy()=default;

    };

