#pragma once
struct Network{
    double lr;

    double * hiddenBiais;
    double * outputBiais;

    double * hiddenWeights;
    double * outputWeights;

    double * hiddenActivation;
    double * outputActivation;
};
struct Network initialize(double lr, int nbInput, int nbHidden, int nbOutput);