#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"
#include "usefull.h"
#include "load_network.h"

//all variable usefull
#define learning_rate 0.1f
#define nbInputs 2
#define nbHidden 3
#define nbOutputs 1
#define nbTrainingSet 4
#define nbEpochs 10000
double training_inputs[nbTrainingSet][nbInputs]={{0.0f,0.0f},
                                         {0.0f,1.0f},
                                         {1.0f,0.0f},
                                         {1.0f,1.0f}};
double training_outputs[nbTrainingSet][nbOutputs] = {{0.0f},
                                            {1.0f},
                                            {1.0f},
                                            {0.0f}};

void ForwardPass(struct Network* net, int i){

    // Compute hidden layer activation
    for (int j = 0;j<nbHidden;j++){
        double activation = *((*net).hiddenBiais+j);
        for (int k = 0;k<nbInputs;k++){
            activation += training_inputs[i][k] * (*((*net).hiddenWeights+k*nbHidden+j));
        }
        *((*net).hiddenActivation+j)=sigmoid(activation);
    }

    // Compute output layer activation
    for (int j = 0;j<nbOutputs;j++){
        double activation = *((*net).outputBiais+j);
        for (int k =0;k<nbHidden;k++){
            activation += *((*net).hiddenActivation+k) * (*((*net).outputWeights+k*nbOutputs+j));
        }
        *((*net).outputActivation+j)=sigmoid(activation);
    }
}

void BackProp(struct Network* net,int i){
    // Compute change in output weights
    double deltaOutput[nbOutputs];

    for (int j =0;j<nbOutputs;j++){
        double error = (training_outputs[i][j] - *((*net).outputActivation+j));
        deltaOutput[j]=error * dSigmoid(*((*net).outputActivation+j));
    }

    //Compute change in hidden weights
    double deltaHidden[nbHidden];
    for (int j = 0;j<nbHidden;j++){
        double error = 0.0f;
        for (int k = 0;k<nbOutputs;k++){
            error += deltaOutput[k]* (*((*net).outputWeights+j*nbOutputs+k));
        }
        deltaHidden[j]=error* dSigmoid(*((*net).hiddenActivation+j));
    }

    //Apply chang in output weights
    for(int j = 0;j<nbOutputs;j++){
        *((*net).outputBiais+j)+=deltaOutput[j]*(*net).lr;
        for (int k = 0;k<nbHidden;k++){
            *((*net).outputWeights+k*nbOutputs+j) += *((*net).hiddenActivation+k) *deltaOutput[j]*(*net).lr;
        }
    }

    // Apply change in hidden weights
    for(int j = 0;j<nbHidden;j++){
        *((*net).hiddenBiais+j)+=deltaHidden[j]*(*net).lr;
        for (int k = 0;k<nbInputs;k++){
            *((*net).hiddenWeights+k*nbHidden+j) += training_inputs[i][k]*deltaHidden[j]*(*net).lr;
        }
    }
}


int main(int argc, char **argv){
    char* path;
    if (argc==2){
        path = argv[1];
    }
    else{
        path = "backup.txt";
    }
    struct Network net1 = initialize(learning_rate,nbInputs,nbHidden,nbOutputs);
    struct Network * net = &net1;
    
    //Initializing everything to random numbers
    for (int i = 0; i<nbInputs*nbHidden;i++){
        *((*net).hiddenWeights+i)=init_weights();  
    }
    for (int i = 0; i<nbOutputs*nbHidden;i++){
        *((*net).outputWeights+i)=init_weights();  
    }
    for (int i = 0;i<nbHidden;i++){
        *((*net).hiddenBiais+i) = init_weights();
    }
    for (int i = 0;i<nbOutputs;i++){
        *((*net).outputBiais+i) = init_weights();
    }
    ///////

    //Let's now train our network
    int trainingSetOrder[]={0,1,2,3};

    for (int epoch = 0;epoch<nbEpochs;epoch++){
        shuffle(trainingSetOrder,nbTrainingSet);
        for (int x = 0;x<nbTrainingSet;x++){

            int i = trainingSetOrder[x];
        
            ForwardPass(net,i);
            BackProp(net,i);
        }
    }

    //Just to print the outputs
    for (int i = 0;i<nbTrainingSet;i++){
        ForwardPass(net,i);
        printf("Input : %f %f Ouput : %f Expected : %f \n",
                training_inputs[i][0],training_inputs[i][1],
                *((*net).outputActivation),training_outputs[i][0]);
    }

    //Writing the bias and the weights in a file
    FILE *file;
    file = fopen(path,"w");
    if (file != NULL){
        
        fprintf(file,"%d\n",nbInputs);
        fprintf(file,"%d\n",nbHidden);
        fprintf(file,"%d\n",nbOutputs);
        fprintf(file,"%f\n",learning_rate);
        for (int i = 0 ; i<nbHidden;i++){
            fprintf(file, "%f\n",*((*net).hiddenBiais+i));
        }
        for (int i = 0;i<nbOutputs;i++){
            fprintf(file, "%f\n",*((*net).outputBiais+i));
        }
        for (int i = 0;i<nbInputs*nbHidden;i++){
            fprintf(file,"%f\n",*((*net).hiddenWeights+i));
        }
        for (int i = 0;i<nbHidden*nbOutputs;i++){
            fprintf(file,"%f\n",*((*net).outputWeights+i));
        }

        fclose(file);
    }
    

    printf("------------------------------\n");
    struct Network created1 = txt_to_network(path);
    struct Network* created = &created1;
    for (int i = 0;i<nbTrainingSet;i++){
        ForwardPass(created,i);
        printf("Input : %f %f Ouput : %f Expected : %f \n",
                training_inputs[i][0],training_inputs[i][1],
                *((*created).outputActivation),training_outputs[i][0]);
    }

    return 0;
}
