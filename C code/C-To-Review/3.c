/*This program uses a binary tree structure for displaying
	a tournament of tennis. The main function shows information
	about the winner, the structure of the tournament, the 
	matches played, etc. It reads this information from a textfile
	with this format: [player][num_of_sets]

    Example: "Tournament.txt"
    Jose;0
    Daniel;3
    Peter;1
    Diogo;2
*/

// Bugs can be of the following types:
// 1. Logical bug
// 2. Performance bug
// 3. Variable type bug
// 4. Memory managment bug
// 5. Documentation bug

// The review should take no longer than 15 minutes.
// Review starts on Line 81 and ends in line 150

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 20
#define STAGES 15
#define EMPTY NULL
#define NO_LINK NULL

// Define Structs
typedef struct _PLAYER{
    char name[MAX_NAME];
    int sets;
}PLAYER;

typedef struct _BTREE_NODE{
    void *data;
    struct _BTREE_NODE* left; 
    struct _BTREE_NODE* right;
}BTREE_NODE;

// Define Macros
typedef BTREE_NODE* BTREE;
typedef enum _BTREE_LOCATION{BTREE_LEFT, BTREE_RIGHT} BTREE_LOCATION;
typedef enum _BOOLEAN {FALSE = 0, TRUE = 1} BOOLEAN;
typedef enum _STATUS {ERROR = 0, OK = 1} STATUS;

// REVIEW STARTS HERE

int main(){
	BTREE Btree;
	void* players [STAGES];
	char file_name [MAX_NAME];

	printf("Nome do ficheiro: ");
	scanf("%s", file_name);

	if (readPlayersFromFile(players, file_name))
	{
        Btree = createBtree(players, 0, STAGES);
        
		printf("\nGames played by the Tournament Winner: %d\n");
		printWinnerGames(Btree);

		printf("\nSets won by the Tournament Winner: %d\n", countWinnerSets(Btree));
	}
	else
		printf("Error Reading File\n");
    return 0;
}
/****************************************************************
* Function: Read players from file
*
* Parameters: double pointer to player type structure; pointer to filename
* Comments:  scans from a file with the structure mentioned above. Allocates the player, and fills the player with correct data. inserts player in a players structure.
* Out: ERROR if Problem ocorred in function. File pointer if OK
***************************************************************/

// REVIEW STARTS HERE

STATUS readPlayersFromFile(void** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%d[^;];", ((PLAYER*)ptr_data)->name);
				fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}
/****************************************************************
* Function: Count winner sets
* Comments: Uses a function "btreeLeaf" to know if a node is a Leaf (this function returns TRUE if node is a leaf, and FALSE if node is not a Leaf)
* Parameters: Binary tree
* Out: the number of winner sets
***************************************************************/
int countWinnerSets(BTREE btree)
{
    int count = 0;
    BTREE BT=btree;
    count += ((PLAYER*)BT->data)->sets;
    if (btree != NULL && !bTreeLeaf(btree)) {
        if (!strcmp(((PLAYER*)btree->left->data)->name, ((PLAYER*)btree->data)->name)){
            count +=  countWinnerSets(BT->left);
        }
        else
        {
            count += countWinnerSets(BT->right); 
        }
    }
    return (count);
}

/****************************************************************
* Function: Print winner games
* Parameters: A binary Tree
* Comments: prints the game. To continue this logic, compares which player name is the same (one tier down vs current node), to know who won that game.
Uses a function "btreeLeaf" to know if a node is a Leaf (this function returns TRUE if node is a leaf, and FALSE if node is not a Leaf)
* Out: void
***************************************************************/
void printWinnerGames(BTREE btree)
{
    if (btree != NULL && !bTreeLeaf(btree)) {
        printf("%s sets -> %d : %s sets -> % d => Winner : %s \n", ((PLAYER*)btree->left->data)->name, ((PLAYER*)btree->left->data)->sets,((PLAYER*)btree->right->data)->name, ((PLAYER*)btree->right->data)->sets, ((PLAYER*)btree->data)->name);

        if (!strcmp(((PLAYER*)btree->left->data)->name, ((PLAYER*)btree->data)->name))
            printWinnerGames(btree->left);
        else
            printWinnerGames(btree->right);
    }
	return;
}

// REVIEW ENDS HERE