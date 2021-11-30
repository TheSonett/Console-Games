////////////// ---------------- AI Based Tic Tac Toe Game in C -------------------------////////////////////

#include <stdio.h>

#define COMPUTER 1
#define HUMAN 2

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

#define SIZE 3


void printBoard(char board[SIZE][SIZE])
{
    printf("\n::: Game Board :::\n\n");

	printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
	printf("-----------\n");
	printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
	printf("-----------\n");
	printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void boardLayout()
{
	printf("\n::: Board Layout :::\n\n");

	printf(" 1 | 2 | 3 \n");
	printf("-----------\n");
	printf(" 4 | 5 | 6 \n");
	printf("-----------\n");
	printf(" 7 | 8 | 9 \n\n");
}

void boardInit(char board[SIZE][SIZE])
{
	for (int i=0; i<SIZE; i++)
	{
		for (int j=0; j<SIZE; j++) {
			board[i][j] = ' ';
		}
	}
}

void printWinner(int player)
{
	if (player == COMPUTER)
		printf("COMPUTER has won!\n");
	else
		printf("HUMAN has won!\n");
}

bool rowCrossed(char board[SIZE][SIZE])
{
	for (int i=0; i<SIZE; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
			return true;
	}
	return false;
}

bool columnCrossed(char board[SIZE][SIZE])
{
	for (int i=0; i<SIZE; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
			return true;
	}
	return false;
}

bool diagonalCrossed(char board[SIZE][SIZE])
{
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		return true;

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
		return true;

	return false;
}

bool isGameOver(char board[SIZE][SIZE])
{
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

int minimax(char board[SIZE][SIZE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (isGameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -10000;
				for(int i=0; i<SIZE; i++)
				{
					for(int j=0; j<SIZE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 10000;
				for (int i = 0; i < SIZE; i++)
				{
					for (int j = 0; j < SIZE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

int bestMove(char board[SIZE][SIZE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -10000;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

void AiPlayTicTacToe(int player)
{
	char board[SIZE][SIZE];
	int moveIndex = 0, x = 0, y = 0;

	boardInit(board);
	boardLayout();

	// Game Loop
	while (isGameOver(board) == false && moveIndex != SIZE * SIZE)
	{
		int n;
		if (player == COMPUTER)
		{
			n = bestMove(board, moveIndex);
			x = n / SIZE;
			y = n % SIZE;

			board[x][y] = COMPUTERMOVE;
			printBoard(board);

			moveIndex ++;
			player = HUMAN;
		}

		else if (player == HUMAN)
		{
			printf("\n\nEnter the position = ");
			scanf("%d",&n);

			n--;
			x = n / SIZE;
			y = n % SIZE;

			if(board[x][y] == ' ' && n < SIZE * SIZE && n>=0)
			{
				board[x][y] = HUMANMOVE;
				moveIndex ++;
				player = COMPUTER;
			}
			else if(board[x][y] != ' ' && n < SIZE * SIZE && n >= 0)
			{
				printf("\nPosition is occupied! Select another position!\n\n");
			}
			else if(n < 0 || n > 8)
			{
				printf("Invalid position!!\n");
			}
		}
	}

	if (isGameOver(board) == false && moveIndex == SIZE * SIZE)
		printf("Match Draw!!\n");
	else
	{
		if (player == COMPUTER)
			player = HUMAN;
		else if (player == HUMAN)
			player = COMPUTER;

		printWinner(player);
	}
}


int main()
{
	printf("\t:::: Tic-Tac-Toe Game :::: \n\n");
	char quit;

    do {
        char choice;
        printf("Do you want to start the game first ? (y/n) : ");
        scanf(" %c", &choice);

        if(choice =='n')
            AiPlayTicTacToe(COMPUTER);
        else if(choice =='y')
            AiPlayTicTacToe(HUMAN);
        else
            printf("Invalid choice\n");

        printf("\nDo you want to quit the game(y/n) : ");
            scanf(" %c", &quit);
    }
    while(quit =='n');
}
