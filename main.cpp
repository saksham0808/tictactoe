#include <bits/stdc++.h>

using namespace std;

class Move {
	public:
		int i;
		int j;
		Move(int a, int b) {
			i = a;
			j = b;
		}
};

class Game {
	public:
		int toPlay;
		int winner;
		bool isDone;
		void humanTurn();
		void aiTurn();
		void printState();
		Game();
		Game(int current[3][3], int CurToPlay);

	private:
		int state[3][3];
		void checkIfDone(int i, int j);
		Move simulate();
		bool toPrint;
};

// State 1 is a human placed counter, -1 is computer placed, 0 is empty
void Game::humanTurn() {
	int i,j;
	while(true) {
		cout << "Enter your move: ";
		cin >> i >> j;
		if(state[i][j])
			cout << "Invalid move. Try again.\n";
		else
			break;
	}
	state[i][j] = 1;
	toPlay = -toPlay;
	checkIfDone(i, j);
}

void Game::aiTurn() {
	Game sim(state, toPlay);
	Move best = sim.simulate();
	state[best.i][best.j] = toPlay;
	toPlay = -toPlay;
	checkIfDone(best.i, best.j);
}

Move Game::simulate() {
	int imax=-1, jmax=-1, scoremax=-100;
	int temp[3][3];
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			temp[i][j]=state[i][j];
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			if(!state[i][j]) {
				state[i][j] = toPlay;
				int whoPlayed=toPlay;
				checkIfDone(i, j);
				toPlay = -toPlay;
				while(!isDone) {
					aiTurn();
				}
				if(winner != whoPlayed) {
					if(scoremax<-10) {
						imax=i;
						jmax=j;
						scoremax=-10;
					}
				} else if (winner == whoPlayed) {
					if(scoremax<10) {
						imax=i;
						jmax=j;
						scoremax=10;
					}
				} else {
					if(scoremax<0) {
						imax=i;
						jmax=j;
						scoremax=0;
					}
				}
				for(int a=0;a<3;a++)
					for(int b=0;b<3;b++)
						state[a][b]=temp[a][b];
			}
		}
	}

	return Move(imax, jmax);
}

void Game::checkIfDone(int i, int j) {
	if(state[i][0] == state[i][1] && state[i][1] == state[i][2] && state[i][0]) {
		winner=state[i][0];
		isDone=1;
		//cout << "m1\n";
		return;
	}
	if(state[0][j] == state[1][j] && state[1][j] == state[2][j] && state[0][j]) {
		winner=state[0][j];
		isDone=1;
		//cout << "m2\n";
		return;
	}
	if(i==j && state[0][0] == state[1][1] && state[1][1] == state[2][2] && state[0][0]) {
		winner=state[0][0];
		isDone=1;
		//cout << "m3\n";
		return;
	}
	if(i+j==2 && state[0][2] == state[1][1] && state[1][1] == state[2][0] && state[0][2]) {
		winner=state[0][2];
		isDone=1;
		//cout << "m4\n";
		return;
	}
	
	bool allFull = 1;
	for(int a=0;a<3;a++)
		for(int b=0;b<3;b++)
			if(state[a][b] == 0)
				allFull = 0;

	if(allFull) {
		if(toPrint)
			cout << "full\n";
		winner = 0;
		isDone = 1;
		return;
	}
	return;
}

void Game::printState() {
	cout << "###########################\n";
	for(int i=0;i<3;i++) {
		cout << " | ";
		for(int j=0;j<3;j++)
			cout << state[i][j] << " | ";
		cout << "\n---------------\n";
	}
	cout << "###########################\n";
}

Game::Game() {
	toPlay=1;
	isDone=0;
	winner=0;
	toPrint=1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			state[i][j]=0;
}

Game::Game(int current[3][3], int CurToPlay) {
	toPlay=CurToPlay;
	isDone=0;
	winner=0;
	toPrint=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			state[i][j]=current[i][j];
}

// toPlay == 1 means knot's turn, toPlay == -1 means cross's turn
int main() {
	Game game;
	game.printState();
	while(!game.isDone) {
		(game.toPlay==1) ? game.humanTurn() : game.aiTurn();
		game.printState();
	}
	cout << "And the winner is........... " << game.winner << endl;
}
