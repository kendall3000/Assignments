#include "trafficSimulator.h"

void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("<Kendall Ramos>\n");
    printf("<\"N/A\">\n");
}

/* trafficSimulator
 * input: char* name of file to read
 * output: N/A
 *
 * Simulate the road network in the given file
 */

void trafficSimulator( char * filename )
{
    /* Read in the traffic data.  You may want to create a separate function to do this. */
    TrafficSimData *simulationData = readTrafficData(filename);
    simulationData->maxStepsToDest = 0;

    int * commandStepTracker = simulationData->printCommandSteps;
    double averageTracker = 0.0;
    int i;
    /* Loop until all events processed and either all cars reached destination or gridlock has occurred */
    for(int cycle = 0; ; cycle++) {
        //pop out of PQ and place in queue of cars to be added to road

        /* Loop on events associated with this time step */
        while(!isEmptyPQ(simulationData->events) && cycle == getFrontPriority(simulationData->events)) {
            //events ahve from/to
            Event * event = dequeuePQ(simulationData->events);
            RoadData * roadData = getEdgeData(simulationData->trafficGraph, event->starting, event->ending);
            Car * car = malloc(sizeof(Car));
            car->starting = event->starting;
            car->ending = event->ending;
            car->destinationVertex = event->destinationVertex;
            car->cycleCarJoined = cycle;
            enqueue(roadData->waitingToEnter, car);
            
            /* have we already enqueued a car this cycle */
            if(roadData->lastTimeCarsEnqueued != cycle) {
                printf("CYCLE %d - ADD_CAR_EVENT - Cars enqueued on road from %d to %d\n", cycle, roadData->from, roadData->to);
                roadData->lastTimeCarsEnqueued = cycle;
            }
        }

        int j;

        /* print road events */
        if(cycle == *commandStepTracker) {
            commandStepTracker++;
            printf("\nCYCLE %d - PRINT_ROADS_EVENT - Current contents of the roads:\n", cycle); 
            for(i = 0; i < simulationData->numRoads; i++) {
                RoadData * currentRoad = simulationData->roads[i];
                printf("Cars on the road from %d to %d:\n", currentRoad->from, currentRoad->to);
                for(j = 0; j < currentRoad->lengthOfRoad; j++) {
                    if(currentRoad->carsOnRoad[j] == NULL) {
                        printf("- ");
                    }
                    else {
                        printf("%d ", currentRoad->carsOnRoad[j]->destinationVertex);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }

        /* First try to move through the intersection */
        bool carReachedDest = false;
        for(i = 0; i < simulationData->numRoads; i++) {
            RoadData * currentRoad = simulationData->roads[i];
            Car * carToMove = currentRoad->carsOnRoad[0];

            if(carToMove == NULL)
                continue;

            //if the light is greeen
            if(currentRoad->currentCycle >= currentRoad->greenOn && currentRoad->currentCycle < currentRoad->greenOff) {
                // check cars destination && check shortest route
                if(currentRoad->to == carToMove->destinationVertex) {
                    currentRoad->carsOnRoad[0] = NULL;
                    int moved = cycle - carToMove->cycleCarJoined;
                    // car reached destination
                    printf("CYCLE %d - Car successfully traveled from %d to %d in %d time steps.\n", cycle, carToMove->starting, carToMove->destinationVertex, moved);

                    simulationData->averageCounter += (double)moved;
                    averageTracker++;
                    if(moved > simulationData->maxStepsToDest)
                        simulationData->maxStepsToDest = moved;
                    simulationData->currentCarsActive--;
                    carReachedDest = true;
                }
                else {
                    int * pNext = malloc(sizeof(int));
                    if(!getNextOnShortestPath(simulationData->trafficGraph, currentRoad->to, carToMove->destinationVertex, pNext)) {
                        break;
                    }

                    RoadData * nextRoad = getEdgeData(simulationData->trafficGraph, currentRoad->to, *pNext);

                    if(nextRoad->carsOnRoad[nextRoad->lengthOfRoad - 1] == NULL) {
                        carToMove->hasMoved = true;
                        nextRoad->carsOnRoad[nextRoad->lengthOfRoad - 1] = carToMove;
                        currentRoad->carsOnRoad[0] = NULL;
                    }
                }
            }
        }
        
        /* Second move cars forward on every road */
        for(i = 0; i < simulationData->numRoads; i++) {
            RoadData * currentRoad = simulationData->roads[i];
            Car ** carsOnRoad = currentRoad->carsOnRoad;

            for(j = currentRoad->lengthOfRoad - 1; j > 0; j--) {
                if(carsOnRoad[j] != NULL && carsOnRoad[j - 1] == NULL) {
                    carsOnRoad[j - 1] = carsOnRoad[j];
                    carsOnRoad[j] = NULL;
                    carsOnRoad[j - 1]->hasMoved = true;
                    j--;
                }
            }
        }

        /* Third move cars onto road if possible */
        for(i = 0; i < simulationData->numRoads; i++) {
            RoadData * currentRoad = simulationData->roads[i];
            Car ** cars = currentRoad->carsOnRoad;
            int lengthOfRoad = currentRoad->lengthOfRoad;

            if(cars[lengthOfRoad - 1] == NULL && !isEmpty(currentRoad->waitingToEnter)) {
                // move waiting car onto road
                Car * car = dequeue(currentRoad->waitingToEnter);
                currentRoad->carsOnRoad[lengthOfRoad - 1] = car;
                car->hasMoved = true;
            }
        }

        /* change light cycles */
        for(i = 0; i < simulationData->numRoads; i++) {
            RoadData * currentRoad = simulationData->roads[i];

            currentRoad->currentCycle++;
            
            if(currentRoad->currentCycle == currentRoad->resetCycle)
                currentRoad->currentCycle = 0;
        }

        /* check if current moving cars are zero */
        if(simulationData->currentCarsActive <= 0) {
            printf("\nAverage number of time steps to the reach their destination is %.2lf.\n", simulationData->averageCounter /= averageTracker);
            printf("Maximum number of time steps to the reach their destination is %d.\n", simulationData->maxStepsToDest);
            printf("\n");

            break;
        }

        /* check for grid lock */
        int cycledDetectedOn;
        if(cycle % simulationData->longestLightCycle == 0) {
            bool haveAnyCarsMoved = carReachedDest;

            for(i = 0; i < simulationData->numRoads; i++) {
                RoadData * currentRoad = simulationData->roads[i];
                Car ** car = currentRoad->carsOnRoad;

                for(j = 0; j < currentRoad->lengthOfRoad; j++) {
                    if(car[j] == NULL)
                        continue;
                    haveAnyCarsMoved = haveAnyCarsMoved || car[j]->hasMoved;
                    // int first time gird was detected
                    if(haveAnyCarsMoved == true)
                        cycledDetectedOn = cycle;
                    car[j]->hasMoved = false;
                }
            }
            if(haveAnyCarsMoved == false) {
                printf("CYCLE %d - Gridlock detected.\n", cycledDetectedOn + 1);
                break;
            }
        }
    }

    /* final print statements */
}

TrafficSimData * readTrafficData(char * filename) {
    TrafficSimData * simulationData = malloc(sizeof(TrafficSimData));

    FILE * fp;
    fp = fopen(filename, "r");

    int i, j, k;
    
    int verticies, edges;
    fscanf(fp, "%d", &verticies);
    fscanf(fp, "%d", &edges);
    
    simulationData->trafficGraph = createGraph(verticies);
    simulationData->events = createPQ();
    simulationData->roads = malloc(sizeof(RoadData) * edges);
    simulationData->numRoads = edges;
    int roadCounter = 0;

    for(i = 0; i < verticies; i++) {
        int toVertex, incomingRoads;
        fscanf(fp, "%d", &toVertex);
        fscanf(fp, "%d", &incomingRoads);

        if(!isVertex(simulationData->trafficGraph, toVertex))
            addVertex(simulationData->trafficGraph, toVertex);

        for(j = 0; j < incomingRoads; j++) {
            int fromVertex, lengthOfRoad, greenOn, greenOff, resetCycle;
            // scan in fromVertex & lengthOfEdge
            fscanf(fp, "%d", &fromVertex);
            fscanf(fp, "%d", &lengthOfRoad);

            // greenOn to i vertex
            fscanf(fp, "%d", &greenOn);
            // greenOff to i vertex
            fscanf(fp, "%d", &greenOff);
            // resetCycle to i vertex
            fscanf(fp, "%d", &resetCycle);

            RoadData *roadDataStruct = malloc(sizeof(RoadData));
            roadDataStruct->to = toVertex;
            roadDataStruct->from = fromVertex;
            roadDataStruct->lengthOfRoad = lengthOfRoad;
            roadDataStruct->greenOn = greenOn;
            roadDataStruct->greenOff = greenOff;
            roadDataStruct->resetCycle = resetCycle;
            roadDataStruct->lastTimeCarsEnqueued = -1;
            roadDataStruct->carsOnRoad = malloc(sizeof(Car) * lengthOfRoad);
            for(k = 0; k < lengthOfRoad; ++k)
                roadDataStruct->carsOnRoad[k] = NULL;

            roadDataStruct->waitingToEnter = createQueue();

            setEdge(simulationData->trafficGraph, fromVertex, toVertex, lengthOfRoad);
            setEdgeData(simulationData->trafficGraph, fromVertex, toVertex, roadDataStruct);

            simulationData->roads[roadCounter++] = roadDataStruct;
            if(simulationData->longestLightCycle < resetCycle)
                simulationData->longestLightCycle = resetCycle;
        }
    }

    int addCarCommands;
    fscanf(fp, "%d", &addCarCommands);
    for(i = 0; i < addCarCommands; i++) {
        int starting, ending, whenToAddCar, howManyToAdd;
        
        fscanf(fp, "%d", &starting);
        fscanf(fp, "%d", &ending);
        fscanf(fp, "%d", &whenToAddCar);
        fscanf(fp, "%d", &howManyToAdd);

        for(j = 0; j < howManyToAdd; j++) {
            // adding into an array?
            int destinationVertex;
            fscanf(fp, "%d", &destinationVertex);

            Event * event = malloc(sizeof(Event));
            event->starting = starting;
            event->ending = ending;
            event->whenToAddCar = whenToAddCar;
            event->destinationVertex = destinationVertex;

            enqueueByPriority(simulationData->events, event, whenToAddCar);
            simulationData->currentCarsActive++;
        }
    }

    int printRoadCommands;
    fscanf(fp, "%d", &printRoadCommands);
    simulationData->printCommandSteps = malloc(sizeof(int) * printRoadCommands);
    for(i = 0; i < printRoadCommands; i++) {
        int cycleToPrintRoads;
        fscanf(fp, "%d", &cycleToPrintRoads);
        simulationData->printCommandSteps[i] = cycleToPrintRoads;
    }
    fclose(fp);
    return simulationData;
}