#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Point of interest structure holds the location
// as latitude-longitude pair, and the type and
// the name of the POI as string
typedef struct pointOfInterest POI;

struct pointOfInterest {
    double location[2];
    char type[15];
    char* name;
    POI* next;
};

// Map structure holds the points of interest data for the map
// location as a POI structure array, the amount of POIs in
// the array and the name of the location for the map.
typedef struct map {
    POI* pointsOfInterest;
    char* locationName;
} Map;

// Function createPOI creates a linked list member with the given data.
POI* createPOI(char* name, char* type, double location[2]) {
    // Allocate memory for POI
    POI* poi = malloc(sizeof(POI));

    // Allocate memory for the POI name and copy it to the structure
    poi->name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(poi->name, name);

    // Store the type
    strcpy(poi->type, type);

    // Store the location, as lat-lon (from lon-lat)
    poi->location[0] = location[1];
    poi->location[1] = location[0];

    // Set the next pointer
    poi->next = NULL;

    return poi;
}

// Function createPOIs takes four parameters:
// - poiNames, an array of points of interests' names
// - poiTypes, an array of POI names
// - locations, an array of pairs of doubles (longitude-latitude pairs)
// - poiAmount, an integer that tells how many POIs there are in the arrays
// The function returns a POI structure array created
// from the data given as parameters
POI* createPOIs(char** poiNames, char** poiTypes,
                double locations[][2], int poiAmount) {

    POI* start = createPOI(poiNames[0], poiTypes[0], locations[0]);
    POI* poi = start;

    // Go through all the given data and store it in the linked list
    for(int i = 0; i < poiAmount; i++) {
        poi->next = createPOI(poiNames[i], poiTypes[i], locations[i]);
        poi = poi->next;
    }

    return poi;
}

// Function createMap take five parameters:
// - locationName, a string that tells the map location name
// - poiNames (forwarded to the createPOIs function, see it for details)
// - poiTypes (forwarded to the createPOIs function, see it for details)
// - locations (forwarded to the createPOIs function, see it for details)
// - poiAmount (forwarded to the createPOIs function, see it for details)
Map* createMap(char* locationName, char** poiNames, char** poiTypes,
               double locations[][2], int poiAmount) {

    // Allocate memory for the Map structure
    Map* map = malloc(sizeof(Map));

    // Store the location name
    map->locationName = malloc(strlen(locationName) + 1);
    strcpy(map->locationName, locationName);

    // Store the points of interest information
    map->pointsOfInterest = createPOIs(poiNames, poiTypes,
                                       locations, poiAmount);

    return map;
}

// Function printPoiInfo prints the Map structure information
// in the following format:
//
// <place name> has the following points of interest:
// Point of interest <name> at (latitude, longitude) if of type <type>.
// ...
void printPoiInfo(Map* map) {
    printf("%s has the following points of interest:\n", map->locationName);

    // Loop through the points of interest and print their info
    for(POI* curr = map->pointsOfInterest; curr != NULL;) {
        printf("Point of interest %s at (%f, %f) is of type %s.\n",
               curr->name, curr->location[0], curr->location[1], curr->type);
    }
}

// Function freeMemory frees all the dynamic memory
// allocated for the Map structure
void freeMemory(Map* map) {
    // Free linked list memory
    for(POI* curr = map->pointsOfInterest; curr != NULL;) {
        POI* del = curr;
        curr = curr->next;
        free(del->name);
        free(del->next);
        free(del);
    }
    free(map->locationName);
    free(map);
}

int main() {
    // Original data for the points of interests:
    // Names
    char* names[] = { "Aalto Maarintalo",
                      "Sodexo: Kvarkki",
                      "Ossinlammen viljelypalstat",
                      "Subway",
                      "Sodexo: T-talo",
                      "Kipsari",
                      "Ravintola Fat Lizard",
                      "Aalto-yliopisto Kandidaattikeskus",
                      "Amfi",
                      "Aalto-yliopisto Harald Herlin -oppimiskeskus",
                      "Alvarin aukio",
                      "Täffä" };

    char* types[] = { "building",
                      "restaurant",
                      "allotment",
                      "restaurant",
                      "restaurant",
                      "restaurant",
                      "restaurant",
                      "building",
                      "amphitheatre",
                      "building",
                      "park",
                      "restaurant" };

    // Point of interest location, a longitude-latitude pair
    double locations[][2] = { { 24.826246351003647, 60.1892566863454 },
                              { 24.83001083135605, 60.18825326911869 },
                              { 24.833179861307144, 60.188098586791284 },
                              { 24.821400940418243, 60.18700578872486 },
                              { 24.82165038585663, 60.186972450811226 },
                              { 24.824374169111252, 60.18569358288761 },
                              { 24.820403158664703, 60.1855755618042 },
                              { 24.828090369701385, 60.18630368511285 },
                              { 24.827543199062347, 60.185673579343984 },
                              { 24.827739000320435, 60.18472339698474 },
                              { 24.82895404100418, 60.184864092387755 },
                              { 24.833138287067413, 60.18608164922176 } };

    // Create a map structure based on the data
    Map* map = createMap("Otaniemi", names, types, locations, 12);

    // Print map tiles information
    printPoiInfo(map);

    // Free the reserved memory
    freeMemory(map);

    return 0;
}