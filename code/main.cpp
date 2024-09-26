#include <iostream>
#include "header.h"
#include <time.h>
using namespace std;

int main(int argc, char* argv[]){

    srand((unsigned int)time(NULL));

    //Checks first argument
    int n = atoi(argv[1]);
    if ( (n > 10) || (n < 1) ){
        cout << "Your first argument was invalid please pick a number between 1 and 10 inclusive" << endl;
        return 1;
    }

    int electoratesTotal = n;

    int m = atoi(argv[2]);
    if ( (m > 30) || (m < 1) ){
        cout << "Your Second argument was invalid please pick a number between 1 and 30 inclusive" << endl;
        return 1;
    }

    Election TheElection(n ,m);
    TheElection.loadParties();

    TheElection.loadElectortes(n);
    TheElection.loadIssues();
    TheElection.generateElectorateStance();
    TheElection.loadCandidates();
    TheElection.generatePartyStance();

    TheElection.partiesReport();
    TheElection.electoratesReport();
    TheElection.issueReport();

    Campaign currentCampaign;
    currentCampaign.runCampaign(TheElection.returnParties(), TheElection.returnElectorates(), TheElection.returnIssueVector(), TheElection.returnCampaignLength());

    return 0;

}
