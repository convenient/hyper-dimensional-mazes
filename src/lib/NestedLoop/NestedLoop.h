#ifndef NESTEDLOOP_HPP
#define NESTEDLOOP_HPP
#include <vector>

namespace nestedLoop{

    class nestedLoop {
    public:
        //Variables
        std::vector<int> maxes;
        std::vector<int> idxes; //The last element is used for boundary control
        int N=0;
        int nestLevel=0;

        nestedLoop();
        nestedLoop(int,int);
        nestedLoop(int,std::vector<int>);

        void reset(int numberOfNests, int Max);
        void reset(int numberOfNests, std::vector<int> theMaxes);

        bool next();
        void jumpNest(int theNest);

    private:
        void clear();
    };

    //Initialisations
    nestedLoop::nestedLoop(){}

    nestedLoop::nestedLoop(int numberOfNests, int Max) {
        reset(numberOfNests, Max);
    }

    nestedLoop::nestedLoop(int numberOfNests, std::vector<int> theMaxes) {
        reset(numberOfNests,  theMaxes);
    }

    void nestedLoop::clear(){
        maxes.clear();
        idxes.clear();
        N = 0;
        nestLevel = 0;
    }

    //Reset the scene
    void nestedLoop::reset(int numberOfNests, int Max){
        std::vector<int> theMaxes;
        for(int i =0; i < numberOfNests; i++) theMaxes.push_back(Max);
        reset(numberOfNests, theMaxes);
    }

    void nestedLoop::reset(int numberOfNests, std::vector<int> theMaxes){
        clear();
        N = numberOfNests;

        maxes=theMaxes;

        idxes.push_back(-1);
        for(int i=1; i<N; i++) idxes.push_back(theMaxes[i]-1);
    }

    bool nestedLoop::next(){
        idxes[N-1]+=1;

        for(int i=N-1; i>=0; i--){
            if(idxes[i]>=maxes[i]) {
                idxes[i] = 0;

                if(i){ //actually, if i > 0 is needed
                    idxes[i-1] += 1;
                }else{
                    return false;
                }
            }else{
                nestLevel = i;
                break;
            }
        }
        return true;
    }

    void nestedLoop::jumpNest(int theNest){
        for(int i = N-1; i>theNest; i--) {
            idxes[i] = maxes[i]-1;
        }
    }
}
#endif // NESTEDLOOP_HPP