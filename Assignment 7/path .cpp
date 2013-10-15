/**
 * File: path.cpp
 * --------------
 * This file implements the Path class.
 */


#include "path.h"

//Constructor

Path  :: Path() {
    totalDistance = 0;
    list = NULL;
    end = NULL;
    

}

//Destructor

Path :: ~Path(){
    
    Deallocate(list);
    
    
}

// copy constructor

Path :: Path (const Path& path)
{
    totalDistance = path.totalDistance;
    list = NULL;
    end = NULL;
    if (path.list != NULL)
    {
        
        for(Entry* temp = path.list;temp!=NULL;temp=temp->next)
        {
            Entry* newOne = new Entry;
            newOne -> next = NULL;
            newOne -> value = temp -> value;
            if (list == NULL){
                list = newOne;
                end = newOne;
            }
            else{
                end -> next = newOne;
                end = newOne;
            }
        }
    }
}

// Equals Constructor

Path& Path::operator=(const Path &path)
{
    totalDistance = path.totalDistance;
    list = NULL;
    end = NULL;
    if (path.list != NULL)
    {
        
        for(Entry* temp = path.list;temp!=NULL;temp=temp->next)
        {
            Entry* newOne = new Entry;
            newOne -> next = NULL;
            newOne -> value = temp -> value;
            if (list == NULL){
                list = newOne;
                end = newOne;
            }
            else{
                end -> next = newOne;
                end = newOne;
            }
        }
    }
    
    return *this;
}

// This fucntion returns the value of the end pointer

 distanceT * Path :: endValue(){
    return end -> value;
    
}


// This function adds a distanceT* value to a linked list

void Path :: addStructure(distanceT  *  & amount , int number){
    Entry* newOne = new Entry;
    totalDistance += number;
    newOne -> value = amount;
    if (list ==NULL){
    newOne -> next =NULL;
    list = newOne;
        end = newOne;
    } else {
        newOne  -> next= NULL;  // Adding the new entry to the end
        end -> next =  newOne;
        end = newOne;
    }
    
    
}

// This function returns the value assocaiated with each distanceT (arc)

int Path :: getDistance(){
    return totalDistance;
    
}


void Path :: Deallocate (Entry *  good){
    
    if (good != NULL){
        Deallocate (good -> next);
        delete good;
    }
}

// This function adds the distanctT * to a vector so that they can be highlighted

Vector<distanceT *>  Path :: highLighthPath(){
    Vector <distanceT*> mine;
    
    while (list != NULL){
        mine.add(list -> value);
        list = list -> next;
    }
    
    return mine;
    
}
