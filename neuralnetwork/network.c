#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Network{
    double lr;

    double * hiddenBiais;
    double * outputBiais;

    double * hiddenWeights;
    double * outputWeights;

    double * hiddenActivation;
    double * outputActivation;
};

struct Network initialize(double lr, int nbInput, int nbHidden, int nbOutput){
    struct Network net;
    net.lr = lr;

    net.hiddenBiais = calloc(nbHidden,sizeof(double));
    net.outputBiais = calloc(nbOutput,sizeof(double));

    net.hiddenWeights = calloc(nbInput*nbHidden,sizeof(double));
    net.outputWeights = calloc(nbHidden*nbOutput,sizeof(double));

    net.hiddenActivation = calloc(nbHidden,sizeof(double));
    net.outputActivation = calloc(nbOutput,sizeof(double));

    return net;
}

