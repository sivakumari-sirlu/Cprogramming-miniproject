#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 10

// Structure for a voter
typedef struct {
    int id;
    int hasVoted;
} Voter;

// Structure for a candidate
typedef struct {
    char name[50];
    int votes;
} Candidate;

Voter voters[MAX_VOTERS];
Candidate candidates[MAX_CANDIDATES];

int totalVoters = 0, totalCandidates = 0;

// Function to register a voter
void registerVoter(int id) {
    for (int i = 0; i < totalVoters; i++) {
        if (voters[i].id == id) {
            printf("Voter with ID %d is already registered.\n", id);
            return;
        }
    }
    voters[totalVoters].id = id;
    voters[totalVoters].hasVoted = 0;
    totalVoters++;
    printf("Voter with ID %d registered successfully.\n", id);
}

// Function to register a candidate
void registerCandidate(char *name) {
    strcpy(candidates[totalCandidates].name, name);
    candidates[totalCandidates].votes = 0;
    totalCandidates++;
    printf("Candidate '%s' registered successfully.\n", name);
}

// Function to cast a vote
void castVote(int voterID, char *candidateName) {
    // Check if the voter exists and hasn't voted yet
    int voterIndex = -1;
    for (int i = 0; i < totalVoters; i++) {
        if (voters[i].id == voterID) {
            voterIndex = i;
            break;
        }
    }

    if (voterIndex == -1) {
        printf("Voter with ID %d is not registered.\n", voterID);
        return;
    }
    if (voters[voterIndex].hasVoted) {
        printf("Voter with ID %d has already voted.\n", voterID);
        return;
    }

    // Find the candidate and cast the vote
    for (int i = 0; i < totalCandidates; i++) {
        if (strcmp(candidates[i].name, candidateName) == 0) {
            candidates[i].votes++;
            voters[voterIndex].hasVoted = 1;
            printf("Vote cast successfully for '%s'.\n", candidateName);
            return;
        }
    }

    printf("Candidate '%s' not found.\n", candidateName);
}

// Function to display live vote counts
void displayLiveVoteCounts() {
    printf("\nLive Vote Counts:\n");
    for (int i = 0; i < totalCandidates; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
}

// Function to announce the winner
void announceWinner() {
    int maxVotes = 0;
    char winner[50];
    int tie = 0;

    for (int i = 0; i < totalCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            strcpy(winner, candidates[i].name);
            tie = 0;
        } else if (candidates[i].votes == maxVotes) {
            tie = 1;
        }
    }

    if (tie) {
        printf("\nIt's a tie! No clear winner.\n");
    } else {
        printf("\nThe winner is '%s' with %d votes.\n", winner, maxVotes);
    }
}

int main() {
    int choice, voterID;
    char name[50];

    while (1) {
        printf("\nOnline Voting System\n");
        printf("1. Register Voter\n");
        printf("2. Register Candidate\n");
        printf("3. Cast Vote\n");
        printf("4. Display Live Vote Counts\n");
        printf("5. Announce Winner\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Voter ID: ");
                scanf("%d", &voterID);
                registerVoter(voterID);
                break;
            case 2:
                printf("Enter Candidate Name: ");
                scanf(" %[^\n]s", name); // Read string with spaces
                registerCandidate(name);
                break;
            case 3:
                printf("Enter Voter ID: ");
                scanf("%d", &voterID);
                printf("Enter Candidate Name: ");
                scanf(" %[^\n]s", name);
                castVote(voterID, name);
                break;
            case 4:
                displayLiveVoteCounts();
                break;
            case 5:
                announceWinner();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}