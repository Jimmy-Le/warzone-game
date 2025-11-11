//
// Created by Keishaun on 2025-11-10.
//

#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include "Orders.h"
#include "GameEngine.h"

void testLoggingObserver()
{

    cout << "\n==== TESTING LOGGING OBSERVER ====\n";

    // Create log observer
    LogObserver* logObs = new LogObserver();

    // Create objects
    CommandProcessor* cp = new CommandProcessor();
    GameEngine* ge = new GameEngine();
    Orderlist* ol = new Orderlist();
    Player* p = new Player();

    // Attach observer
    cp->attach(logObs);
    ge->attach(logObs);
    ol->attach(logObs);
    p->attach(logObs);

    // Simulate command
    Command* cmd = new Command("Alberta.map");
    cp->saveCommand(cmd);
    cmd->saveEffect("Map loaded successfully.");

    // Simulate state change
    ge->setState(new MapLoaded());

    // Create a Deploy order
    auto deploy = std::make_unique<DeployOrder>(5, "Canada", "USA");
    deploy->attach(logObs);

    // Add to list (triggers log)
    p->issueOrder();

    // Execute first order (triggers another log)
    //ol->orderList.front()->execute();

    cout << "\nCheck gamelog.txt for output!\n";

    delete cp;
    delete ge;
    delete ol;
    delete p;
    delete logObs;

}