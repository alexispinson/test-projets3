#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"

#define tailleMax 20

struct Network txt_to_network(char* path){
    FILE *file;
    file = fopen(path,"r");
    char chaine[tailleMax]="";

    fgets(chaine,tailleMax,file);
    int nbInput = atoi(chaine);

    fgets(chaine,tailleMax,file);
    int nbHidden = atoi(chaine);

    fgets(chaine,tailleMax,file);
    int nbOutputs = atoi(chaine);

    fgets(chaine,tailleMax,file);
    int learning_rate = atof(chaine);

    struct Network net1 = initialize(learning_rate,nbInput,nbHidden,nbOutputs);
    struct Network* net = &net1;

    for (int i = 0;i<nbHidden;i++){
        fgets(chaine,tailleMax,file);
        *((*net).hiddenBiais+i) = atof(chaine);
    }

    for (int i = 0;i<nbOutputs;i++){
        fgets(chaine,tailleMax,file);
        *((*net).outputBiais+i) = atof(chaine);
    }

    for (int i = 0;i<nbHidden*nbInput;i++){
        fgets(chaine,tailleMax,file);
        *((*net).hiddenWeights+i) = atof(chaine);
    }
    for (int i = 0;i<nbHidden*nbOutputs;i++){
        fgets(chaine,tailleMax,file);
        *((*net).outputWeights+i) = atof(chaine);
    }
    
    return *net;
}