#include "TournamentDriver.h"
#include "CommandProcessing.h"
#include "GameEngine.h"

extern GameEngine *theGameEngine;

void testTournament()
{
    cout << "=== Running Tournament Test ===\n";

    CommandProcessor cp;

    // Example tournament command
    string tournamentCmd = "tournament -M Short.map, Shorter.map -P Aggressive,Benevolent -G 3 -D 20";

    // Validate and save command
    if (cp.validate(tournamentCmd))
    {
        Command *cmd = new Command(tournamentCmd);
        cp.saveCommand(cmd);

        // Execute tournament
        theGameEngine->executeTournament(tournamentCmd);

        delete cmd;
    }
}