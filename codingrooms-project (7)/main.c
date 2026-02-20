// DAVINA TITUS
// PROJECT 2 
// CS 211 - FOOD WEB DEV
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Org_struct {
    char name[20];
    int* prey; //dynamic array of indices  
    int numPrey;
} Org;


void addOrgToWeb(Org** pWeb, int* pNumOrgs, char* newOrgName) {
    
    // TODO (Task 3): add a new organism to the food web.
    //      Inputs: 
    //          pWeb - a pointer to a dynamically allocated array of Orgs; i.e. a pointer to a pointer
    //          pNumOrgs - a passed-by-pointer parameter for the number of organisms = size of web[]
    //          newOrgName - a character array (i.e. string) for the name of the new organism 
    //      Outputs:
    //          pWeb - the Org array must be reallocated on the heap to allow space for the new organism
    //          pNumOrgs - the number of organisms should increase by one to account for the new organism
    //        
    //      Note...
    //      (1) web may be an empty Org array if there are no organisms in the food web yet; 
    //          in this case, the input *pWeb should be NULL;
    //      (2) otherwise, a new heap allocation must be made to store all the Orgs in the web 
    //          PLUS one additional Org space for the new organism; this reallocation step must 
    //          be done with only a call to malloc (i.e. not realloc()); make sure to free the 
    //          memory associated with the original web once the Orgs have been copied over to 
    //          the new memory allocation;
    //      (3) the string copy function must be used to copy newOrgName to the web
    //          ex: strcpy((*pWeb)[0].name, newOrgName) // copies newOrgName to the name subitem of the Org at index 0
    //      (4) set default initial values for the prey subitem and numPrey for the new Org.
    //      (5) append the new organism to the back of the web array.
    
    // ALLOCATE NEW ARRAY WITH SIZE CURRENT NUM ORGS +1
    Org* newWeb = (Org*)malloc((*pNumOrgs+1)* sizeof(Org)); // this is a sample malloc() call; update/remove this line
    
    // copy newOrgName to the name subitem of the Org at index 0
    for (int i=0; i< *pNumOrgs;i++){

        strcpy(newWeb[i].name, (*pWeb)[i].name); // this is a sample strcpy() call; update/remove this line
        newWeb[i].prey= (*pWeb)[i].prey;
        newWeb[i].numPrey = (*pWeb)[i].numPrey;

    }

    strcpy(newWeb[*pNumOrgs].name, newOrgName);
    newWeb[*pNumOrgs].prey = NULL;
    newWeb[*pNumOrgs].numPrey =0;

    if (*pWeb != NULL){
        free(*pWeb);
    }
    // UPDATE POINTER TO POINT TO NEWLY ALLOCATED ARRAY
    *pWeb = newWeb;
    // INCREMENT NUMBER OF ORGANISMS
    (*pNumOrgs)++;
    
    return; // this void return statement is optional

}


bool addRelationToWeb(Org* web, int numOrgs, int predInd, int preyInd) {
    
    // TODO (Task 4): add a predator-prey relation to the food web.
    //      Inputs: 
    //          web - a dynamically allocated array of Orgs, i.e. a pointer to an Org
    //          numOrgs - number of organisms = size of web[], passed-by-value
    //          predInd - predator index in web[]; an entry to its prey[] subitem will be added
    //          preyInd - prey index in web[]; will be added to predator's prey[] subitem
    //      Outputs:
    //          web - array is updated and implicitly returned (previously allocated on heap)
    //          bool return true if the new relation was successfully added to the web; 
    //               return false if any issue occurs that prevents the new relation from being added
    //                  ex: if either the predator or prey index argument is not a valid index of web[],
    //                      then print "Invalid predator and/or prey index. No relation added to the food web."
    //                      and immediately leave the function with a false return.
    //                  ex: if the relation is already a part of the web, 
    //                      then print "Duplicate predator/prey relation. No relation added to the food web."
    //                      and immediately leave the function with a false return.
    //        
    //      For the predator-prey relation...
    //      (1) if the predator's prey[] array is empty, the prey subitem will be NULL; 
    //          in this case, allocate memory for one index; 
    //      (2) otherwise, reallocate predator's prey[] array to allow one additional index; 
    //          this reallocation step must be done with only a call to malloc (i.e. not realloc());
    //          make sure to free the memory associated with the original prey[] array once the prey 
    //          indices have been copied over to the new memory allocation;
    //      (3) append the prey index as the last element of the predator's prey[] array;
    //      (4) update the numPrey subitem for the predator appropriately.

    if (predInd<0 || predInd>= numOrgs || preyInd<0 || preyInd >= numOrgs || predInd == preyInd){
        printf("Invalid predator and/or prey index. No relation added to the food web.\n");
        return false;
    }

    // CHECK FOR DUPLICATE RELATION (PREDATOR ALREADY EATS THIS PREY)
    for (int i =0;i < web[predInd].numPrey;i++){
        if (web[predInd].prey[i]==preyInd){
            printf("Duplicate predator/prey relation. No relation added to the food web.\n");
            return false;
        
        }
    }

    // ALLOCATE NEW PREY ARRAY WITH ONE EXTRA SLOT
    int *newPreyarr = (int*)malloc((web[predInd].numPrey+1)*sizeof(int));

    // COPY EXISTING PREY INDICES INTO NEW ARRAY
    for (int i =0; i < web[predInd].numPrey;i++){
        newPreyarr[i] = web[predInd].prey[i];
    }

    // APPEND NEW PREY INDEX AT END
    newPreyarr[web[predInd].numPrey] = preyInd;

    if (web[predInd].prey != NULL ){
        free(web[predInd].prey);
    }

    // POINT PREDATOR'S PREY POINTER TO NEW ARRAY
    web[predInd].prey = newPreyarr;

    // INCREMENT NUMPREY FOR PREDATOR
    web[predInd].numPrey++;

    return true; // update this return statement

}

    
bool removeOrgFromWeb(Org** pWeb, int* pNumOrgs, int index) {

    // TODO (Task 7): remove the organism associated with [index] from web.
    //      Inputs: 
    //          pWeb - a pointer to a dynamically allocated array of Orgs; i.e. a pointer to a pointer
    //          pNumOrgs - a passed-by-pointer parameter for the number of organisms = size of web[]
    //          index - organism index in the (*pWeb)[] array to remove
    //      Outputs:
    //          pWeb - the Org array must be reallocated with less memory once the organism is removed
    //          pNumOrgs - the number of organisms may decrease by one to account for the removed organism
    //          bool return true if the organism was successfully removed from the web; 
    //               return false if any issue occurs that prevents the organism from being removed
    //                  ex: if the index argument is not a valid index of (*pWeb)[],
    //                      then print "Invalid extinction index. No organism removed from the food web."
    //                      and immediately leave the function with a false return.
    //
    //      Remember to do the following:
    //      1. remove organism at index from (*pWeb)[] - DO NOT use realloc(), instead...
    //          (a) free any malloc'd memory associated with organism at index; i.e. its prey[] subitem
    //          (b) malloc new space for the array with the new number of Orgs
    //          (c) copy all but one of the old array elements to the new array, 
    //              some require shifting forward to overwrite the organism at index
    //          (d) free the old array
    //          (e) update the array pointer to the new array
    //          (f) update pNumOrgs
    //      2. remove index from all organisms' prey[] array subitems - DO NOT use realloc(), instead...
    //          (a) search for index in all organisms' prey[] arrays; when index is found:
    //                [i] malloc new space for the array with the new number of ints
    //               [ii] copy all but one of the old array elements to the new array, 
    //                    keeping the same order some require shifting forward
    //              [iii] free the old array
    //               [iv] update the array pointer to the new array
    //                [v] update the numPrey subitem accordingly
    //          (b) update all organisms' prey[] elements that are greater than index, 
    //              which have been shifted forward in the web array
    //
    //          Edge case: check the size array being malloc'ed; 
    //                     for a web with only one organism and 
    //                     that orgranism goes extinct, 
    //                     instead of malloc'ing an empty array, 
    //                     explicitly set the pointer to NULL;
    //                     see web allocation in main() as an example;
    //                     similarly, if a prey[] array becomes empty 
    //                     due to extinction, explicitly set the pointer 
    //                     to NULL, instead of malloc'ing an empty array


    // VALIDATE INDEX
    if (index < 0|| index >= *pNumOrgs){
        printf ("Invalid");
        return false;
    }

    // FREE THE PREY ARRAY OF ORGANISMS BEING REMOVED 
    if ((*pWeb)[index].prey != NULL){
        free ((*pWeb)[index].prey);
    }

    // MALLOC NEW WEB ARRAY WITH ONE LESS ORGANISM
    Org* newWeb = NULL;
    if (*pNumOrgs -1 > 0){
        newWeb = (Org*)malloc((*pNumOrgs-1)*sizeof(Org));
    }

    // COPY ALL ORGANISMS EXCEPT THE ONE AT INDEX
    int newIdx = 0;
    for (int i = 0; i < *pNumOrgs;i++){
        if (i != index){
            // COPY NAME 
            strcpy(newWeb[newIdx].name, (*pWeb)[i].name);
            // COPY PREY POINTER 
            newWeb[newIdx].prey = (*pWeb)[i].prey;
            newWeb[newIdx].numPrey = (*pWeb)[i].numPrey;
            newIdx++;
        }
    }

    // FREE OLD WEB ARRAY
    free(*pWeb);

    // UPDATE WEB POINTER TO NEW ARRAY
    *pWeb = newWeb;

    // UPDATE NUM OF ORGANISMS
    (*pNumOrgs)--;

    // REMOVE INDEX FROM ALL PREY ARRAYS 
    for (int i =0;i < *pNumOrgs; i++){

        // CHECK IF ORGANISM PREY ARRAY CONTAINS EXTINCT INDEX
        bool foundIdx = false;
        for (int j=0; j < (*pWeb)[i].numPrey;j++){
            if ((*pWeb)[i].prey[j]== index){
                foundIdx = true;
                break;
            }
        }

        // IF FOUND REALLOCATE ARRAY W/O THAT INDEX
        if (foundIdx){
            int newprey = (*pWeb)[i].numPrey-1;
            int* newPreyarr = NULL;

            // SET TO NULL IF NEW PREY ARRAY IS EMPTY
            if (newprey > 0){
                newPreyarr = (int*)malloc(newprey*sizeof(int));
                int newpreyIdx =0;
                for (int j = 0; j < (*pWeb)[i].numPrey; j++) {
                    if ((*pWeb)[i].prey[j] != index){
                        newPreyarr[newpreyIdx] = (*pWeb)[i].prey[j];
                        newpreyIdx++;
                    }
                }
            }

            // FREE OLD PREY ARRAY N UPDATE 
            free((*pWeb)[i].prey);
            (*pWeb)[i].prey = newPreyarr;
            (*pWeb)[i].numPrey = newprey;
        }
    }

    // DECREMENT ALL PREY INDICES GREATER THAN INDEX
    for (int i = 0; i < *pNumOrgs; i++) {
        for (int j = 0; j < (*pWeb)[i].numPrey; j++) {
            if ((*pWeb)[i].prey[j] > index) {
                (*pWeb)[i].prey[j]--;
            }
        }
    }
    return true; // update this return statement
}

void freeWeb(Org* web, int numOrgs) {

    // TODO (Task 5): free all malloc'd memory associated with web, 
    //               to prevent potential leaks before program terminates
    
    //  FIRST FREE EACH ORGANISM'S PREY ARRAY
    for (int i = 0; i < numOrgs;i++){
        if (web[i].prey != NULL){
            free(web[i].prey);
        }
    }

    // THEN FREE ARRAY OF ORGS ITSELF
    if (web != NULL){
        free(web);
    }

}

void printWeb(Org* web, int numOrgs) {
    // TODO (Task 6): print the Food Web Organisms with what they eat (i.e. prey)

    // PRINT EACH ORGANISM AND THE ORGANISMS IT EATS  
    for (int i = 0; i < numOrgs; i++){
        printf("  (%d) %s", i, web[i].name);

         // PRINT INDEX AND NAME
        if (web[i].numPrey > 0){
            printf(" eats ");

            // IF ORGANISM HAS PREY, PRINT "EATS" LIST
            for (int j = 0; j < web[i].numPrey; j++){
                printf("%s",web[web[i].prey[j]].name);

                if (j< web[i].numPrey -1 ){
                    printf(", ");
                }
            }
        }
        printf("\n"); 
    }

}

void printFlexible (Org* web, int numOrgs){
    int maxPrey = 0;
    for (int i=0; i< numOrgs;i++){
        if (web[i].numPrey > maxPrey){
            maxPrey = web[i].numPrey;
        }
    }
    for (int i = 0; i < numOrgs; i++){
        if (web[i].numPrey == maxPrey){
            printf("  %s\n", web[i].name);
        }
    }
}

int Count(Org* web, int numOrgs, int index){

    // COUNT HOW MANY ORGANISMS EAT THE ORGANISM AT GIVEN INDEX
    int count=0;
    for (int i =0; i < numOrgs;i++){
        for (int j=0; j<web[i].numPrey;j++){
            if (web[i].prey[j]==index){
                count++;
            }
        }
    }
    return count;
}
void printApex(Org* web, int numOrgs){

    // PRINT ORGANISMS THAT ARE NOT EATEN BY ANY OTHERS (APEX PREDATORS)
    for (int i =0; i < numOrgs;i++){
        if (Count(web,numOrgs, i)==0 ){
            printf("  %s\n", web[i].name);
        }
    }
}

void printProducers(Org* web, int numOrgs){

    // PRINT ORGANISMS THAT EAT NOBODY (PRODUCERS)
    for (int i = 0; i < numOrgs; i++) {
        if (web[i].numPrey == 0) {
            printf("  %s\n", web[i].name);
        }
    }
}

void printTastiest(Org* web, int numOrgs){

    // FIND ORGANISM(S) EATEN BY THE MOST OTHER ORGANISMS
    int maxPred =0;

    // FIND MAX COUNT OF PREDATORS FOR ANY ONE ORGANISM
    for (int i = 0; i < numOrgs; i++) {
        int count = Count(web, numOrgs, i);
        if (count > maxPred) {
            maxPred = count;
        }
    }
    
    // PRINT ALL ORGANISMS WITH THAT MAXIMUM COUNT
    for (int i =0; i < numOrgs;i++){
        if (Count(web, numOrgs,i)== maxPred){
            printf("  %s\n", web[i].name);
        }
    }
}

void printHeight(Org* web, int numOrgs){

    // ALLOCATE ARRAY OF HEIGHTS, INITIALIZED TO 0
    int* height = (int*)malloc(numOrgs*sizeof(int));
    for (int i =0; i < numOrgs; i++){
        height[i] =0;
    }

    // ITERATIVELY RELAX HEIGHTS UNTIL NO CHANGE OCCURS
    bool changed = true;
    while (changed){
        changed = false;
        for (int i = 0; i < numOrgs; i++) {
            for (int j = 0; j < web[i].numPrey; j++) {
                int preyIdx = web[i].prey[j];
                if (height[preyIdx]+1> height[i]){
                    height[i]=height[preyIdx]+1;
                    changed= true;
                }
            }  
        }      
    }

    // PRINT HEIGHT FOR EACH ORGANISM
    for (int i = 0; i < numOrgs; i++) {
        printf("  %s: %d\n", web[i].name, height[i]);
    }

    // FREE HEIGHT ARRAY
    free(height);
}

void VoreType(Org* web, int numOrgs){
    printf("  Producers:\n");

    // PRODUCERS = ORGANISMS THAT EAT NOBODY
    for (int i = 0; i < numOrgs; i++) {
        if (web[i].numPrey == 0) {
            printf("    %s\n", web[i].name);
        }
    }

    printf("  Herbivores:\n");

    // HERBIVORES = EAT ONLY PRODUCERS (ALL PREY HAVE NUMPREY == 0)
    for (int i = 0; i < numOrgs; i++) {
        if (web[i].numPrey == 0) continue;
        bool eatSum = false;
        bool eatSumNon = false;
        for (int j = 0; j < web[i].numPrey;j++){
            if (web[web[i].prey[j]].numPrey==0){
                eatSum = true;
            } else {
                eatSumNon = true;
            }
        }
        if (eatSum && !eatSumNon){
            printf("   %s\n", web[i].name);
        }
    }

    printf("  Omnivores:\n");

    // OMNIVORES = EAT BOTH PRODUCERS AND NON-PRODUCERS
    for (int i = 0; i < numOrgs; i++) {
        if (web[i].numPrey == 0) continue;
        bool eatSum = false;
        bool eatSumNon = false;
        for (int j = 0; j < web[i].numPrey; j++) {
            if (web[web[i].prey[j]].numPrey == 0) {
                eatSum = true;
            } else {
                eatSumNon = true;
            }
        }
        if (eatSum && eatSumNon){
            printf("  %s\n", web[i].name);
        }
    }

    printf("  Carnivores:\n");

    // CARNIVORES = EAT ONLY NON-PRODUCERS
    for (int i = 0; i < numOrgs; i ++){
        if (web[i].numPrey==0) continue;
        bool eatSum = false;
        bool eatSumNon = false;
        for (int j=0; j < web[i].numPrey; j ++){
            if (web[web[i].prey[j]].numPrey == 0) {
                eatSum = true;
            } else {
                eatSumNon = true;
            }
        }
        if (!eatSum && eatSumNon){
            printf("   %s\n", web[i].name);
        }
    }
}

void displayAll(Org* web, int numOrgs, bool modified) {

    if (modified) printf("UPDATED ");
    printf("Food Web Predators & Prey:\n");
    printWeb(web,numOrgs); 
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Apex Predators:\n");
    // TODO (Task 6): identify and print the organisms not eaten by any others
    printApex(web, numOrgs);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Producers:\n");
    // TODO (Task 6): identify and print the organisms that eat no other organisms
    printProducers(web, numOrgs);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Most Flexible Eaters:\n");
    // TODO (Task 6): identity and print the organism(s) with the most prey
    printFlexible(web, numOrgs);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Tastiest Food:\n");
    // TODO (Task 6): identity and print organism(s) eaten by the most other organisms
    printTastiest(web, numOrgs);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Food Web Heights:\n");
    // TODO (Task 6): calculate and print the length of the longest chain from any 
    //                producer to each organism
    printHeight(web, numOrgs);
    printf("\n");

    if (modified) printf("UPDATED ");
    printf("Vore Types:\n");
    // TODO (Task 6): classify all organisms and print each group
    //                (producers, herbivores, omnivores, & carnivores)
    VoreType(web, numOrgs);
    printf("\n");

}

bool setModes(int argc, char* argv[], bool* pBasicMode, bool* pDebugMode, bool* pQuietMode) {

    // TODO (Task 2): process command-line arguments & update basicMode, debugMode, and quietMode
    //                using the passed-by-pointer parameters pBasicMode, pDebugMode, and pQuietMode
    //
    //      - default values: basicMode = FALSE, debugMode = FALSE, quietMode = FALSE
    //      - if basicMode = TRUE, then only build the initial web and analyze it; no modifications
    //      - if debugMode = TRUE, then print out full web as it is built & modified at each step
    //      - if quietMode = TRUE, then suppress printed user-input prompt messages        
    //      
    //      valid command-line arguments are "-b", "-d", and "-q" (and can only appear once);
    //      ALSO, allow full-word command-line arguments "-basic", "-debug", and "-quiet" by simply 
    //      checking if the first two characters are "-b", "-d", and "-q", respectively.
    //      - set basicMode = TRUE if "-b" or "-basic" (or "-bas" or "-basicmode" etc. ) is present
    //      - set debugMode = TRUE if "-d" or "-debug" (or "-deb" or "-debugmode" etc. ) is present
    //      - set quietMode = TRUE if "-q" or "-quiet" (or "-qui" or "-quietmode" etc. ) is present
    //      - if an invalid OR duplicate command-line argument is present, return false from the 
    //        function, which results in the program terminating immediately after the following 
    //        print statment in main():
    //              "Invalid command-line argument. Terminating program..."
    //        otherwise, return true after updating the relevant passed-by-pointer mode parameters
    //
    //      once command-line arguments are processed, the program settings are printed in main()
    //      - Ex: if the program is run as "./a.out -q -b", then print
    //              Program Settings:
    //                basic mode = ON
    //                debug mode = OFF
    //                quiet mode = ON
    //      - Ex: if the program is run as "./a.out", then print
    //              Program Settings:
    //                basic mode = OFF
    //                debug mode = OFF
    //                quiet mode = OFF
    //

    for (int i =1; i< argc;i++){

        // EACH ARG MUST START WITH '-' AND HAVE AT LEAST ONE MORE CHARACTER
        if (argv[i][0]!= '-' || argv[i][1]=='\0'){
            return false;
        }

        char secChar = argv[i][1];

        if (secChar=='b'){
            // DUPLICATES ARE INVALID
            if (*pBasicMode==true){
                return false;
            }
            *pBasicMode = true;

        } else if ( secChar=='d'){
            if (*pDebugMode==true){
                return false;
            }
            *pDebugMode=true;

        } else if (secChar=='q'){
            if (*pQuietMode==true){
                return false;
            }
            *pQuietMode=true;

        } else {
            return false;
        }
    }
    
    return true; // update this return statement

}


void printONorOFF(bool mode) {
    if (mode) {
        printf("ON\n");
    } else {
        printf("OFF\n");
    }
}


int main(int argc, char* argv[]) {  

    // -----------------------------------------------------------------------------------------------------
    // TODO (Task 1): add comments to the main application to show understanding
    //  DO NOT MODIFY THE CODE BENEATH THIS COMMENT (except for debugging purposes and adding comments).
    //  The code in main() represents the primary application, which has been provided for you.
    //  There are many calls to functions that you must write above. Read through the code below, understand  
    //  how it works, check how functions are called, and add relevant comments to show your understanding.
    //  However, no changes should be made to the code in main(). You can put in debugging print statements, 
    //  but those should be removed or commented out prior to submitting to the autograder.
    // -----------------------------------------------------------------------------------------------------
    

    bool basicMode = false;
    bool debugMode = false;
    bool quietMode = false;

    if (!setModes(argc, argv, &basicMode, &debugMode, &quietMode)) {
        printf("Invalid command-line argument. Terminating program...\n");
        return 1;
    }

    printf("Program Settings:\n");
    printf("  basic mode = ");
    printONorOFF(basicMode);
    printf("  debug mode = ");
    printONorOFF(debugMode);
    printf("  quiet mode = ");
    printONorOFF(quietMode);
    printf("\n");

    
    int numOrgs = 0;
    printf("Welcome to the Food Web Application\n\n");
    printf("--------------------------------\n\n");

    Org* web = NULL;

    printf("Building the initial food web...\n");
    
    if (!quietMode) printf("Enter the name for an organism in the web (or enter DONE): ");
    char tempName[20] = "";
    scanf("%s",tempName); 
    if (!quietMode) printf("\n");
    while (strcmp(tempName,"DONE") != 0) {
        addOrgToWeb(&web,&numOrgs,tempName);
        if (debugMode) {
            printf("DEBUG MODE - added an organism:\n");
            printWeb(web,numOrgs);
            printf("\n");
        }
        if (!quietMode) printf("Enter the name for an organism in the web (or enter DONE): ");
        scanf("%s",tempName); 
        if (!quietMode) printf("\n");
    }
    if (!quietMode) printf("\n");

    if (!quietMode) printf("Enter the pair of indices for a predator/prey relation.\n");
    if (!quietMode) printf("Enter any invalid index when done (-1 2, 0 -9, 3 3, etc.).\n");
    if (!quietMode) printf("The format is <predator index> <prey index>: ");
        
    int predInd, preyInd;
    scanf("%d %d",&predInd, &preyInd);
    if (!quietMode) printf("\n");

    while (predInd >= 0 && preyInd >= 0 && predInd < numOrgs &&  preyInd < numOrgs && predInd != preyInd) {
        addRelationToWeb(web,numOrgs,predInd,preyInd);
        if (debugMode) {
            printf("DEBUG MODE - added a relation:\n");
            printWeb(web,numOrgs);
            printf("\n");
        }
        if (!quietMode) printf("Enter the pair of indices for a predator/prey relation.\n");
        if (!quietMode) printf("Enter any invalid index when done (-1 2, 0 -9, 3 3, etc.).\n");
        if (!quietMode) printf("The format is <predator index> <prey index>: ");
        
        scanf("%d %d",&predInd, &preyInd);  
        if (!quietMode) printf("\n");
    }
    printf("\n");

    printf("--------------------------------\n\n");
    printf("Initial food web complete.\n");
    printf("Displaying characteristics for the initial food web...\n");
    
    displayAll(web,numOrgs,false);

    if (!basicMode) {
        printf("--------------------------------\n\n");
        printf("Modifying the food web...\n\n");
        char opt = '?';

        while (opt != 'q') {
            if (!quietMode) {
                printf("Web modification options:\n");
                printf("   o = add a new organism (expansion)\n");
                printf("   r = add a new predator/prey relation (supplementation)\n");
                printf("   x = remove an organism (extinction)\n");
                printf("   p = print the updated food web\n");
                printf("   d = display ALL characteristics for the updated food web\n");
                printf("   q = quit\n");
                printf("Enter a character (o, r, x, p, d, or q): ");
            }
            scanf(" %c", &opt);
            if (!quietMode) printf("\n\n");

            if (opt == 'o') {
                char newName[20];
                if (!quietMode) printf("EXPANSION - enter the name for the new organism: ");
                scanf("%s",newName);
                if (!quietMode) printf("\n");
                printf("Species Expansion: %s\n", newName);
                addOrgToWeb(&web,&numOrgs,newName);
                printf("\n");

                if (debugMode) {
                    printf("DEBUG MODE - added an organism:\n");
                    printWeb(web,numOrgs);
                    printf("\n");
                }

            } else if (opt == 'x') {
                int extInd;
                if (!quietMode) printf("EXTINCTION - enter the index for the extinct organism: ");
                scanf("%d",&extInd);
                if (!quietMode) printf("\n");
                if (extInd >= 0 && extInd < numOrgs) {
                    printf("Species Extinction: %s\n", web[extInd].name);
                    removeOrgFromWeb(&web,&numOrgs,extInd);
                } else {
                    printf("Invalid index for species extinction\n");
                }
                printf("\n");
                
                if (debugMode) {
                    printf("DEBUG MODE - removed an organism:\n");
                    printWeb(web,numOrgs);
                    printf("\n");
                }

            } else if (opt == 'r') {
                if (!quietMode) printf("SUPPLEMENTATION - enter the pair of indices for the new predator/prey relation.\n");
                if (!quietMode) printf("The format is <predator index> <prey index>: ");
                scanf("%d %d",&predInd, &preyInd);
                if (!quietMode) printf("\n");

                if (addRelationToWeb(web,numOrgs,predInd,preyInd)) {
                    printf("New Food Source: %s eats %s\n", web[predInd].name, web[preyInd].name);
                };
                printf("\n");
                if (debugMode) {
                    printf("DEBUG MODE - added a relation:\n");
                    printWeb(web,numOrgs);
                    printf("\n");
                }

            } else if (opt == 'p') {
                printf("UPDATED Food Web Predators & Prey:\n");
                printWeb(web,numOrgs);
                printf("\n");
                
            } else if (opt == 'd') {
                printf("Displaying characteristics for the UPDATED food web...\n\n");
                displayAll(web,numOrgs,true);

            }
            printf("--------------------------------\n\n");
        
        }
        
    }

    freeWeb(web,numOrgs);

    return 0;
}

