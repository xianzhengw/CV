#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLANETS 100
#define MAX_RESEARCHERS 50
#define MAX_NAME_LENGTH 50
#define MAX_DESC_LENGTH 200

// Define Structures

// Planet structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    char type[MAX_NAME_LENGTH];
    double size;
    double distance_from_star;
    double orbital_period;
    char description[MAX_DESC_LENGTH];
    int discovered; // 1 if discovered, 0 if not
    int observed; // 1 if observed, 0 if not
} Planet;

// Researcher structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    int contributions; // Number of planets a researcher has worked on
} Researcher;

// Global arrays for storing planets and researchers
Planet planets[MAX_PLANETS];
Researcher researchers[MAX_RESEARCHERS];
int planet_count = 0;
int researcher_count = 0;

// Function Prototypes
void addPlanet();
void editPlanet();
void removePlanet();
void searchPlanet();
void addResearcher();
void editResearcher();
void viewStatistics();
void printPlanetDetails(Planet planet);
void printResearcherDetails(Researcher researcher);

// Main menu for Admin and Researchers
void adminMenu();
void researcherMenu();

// Helper functions
int findResearcherById(int id);
int findPlanetByName(char* name);

int main() {
    int choice;

    // Main menu for either admin or researcher
    while (1) {
        printf("Welcome to the Planet Catalog System\n");
        printf("1. Admin Menu\n");
        printf("2. Researcher Menu\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            adminMenu();
            break;
        case 2:
            researcherMenu();
            break;
        case 3:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Admin menu
void adminMenu() {
    int choice;
    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Add Planet\n");
        printf("2. Edit Planet\n");
        printf("3. Remove Planet\n");
        printf("4. Add Researcher\n");
        printf("5. Edit Researcher\n");
        printf("6. View Statistics\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addPlanet(); break;
        case 2: editPlanet(); break;
        case 3: removePlanet(); break;
        case 4: addResearcher(); break;
        case 5: editResearcher(); break;
        case 6: viewStatistics(); break;
        case 7: return;
        default: printf("Invalid choice. Please try again.\n");
        }
    }
}

// Researcher menu
void researcherMenu() {
    int choice;
    while (1) {
        printf("\nResearcher Menu:\n");
        printf("1. Search Planet\n");
        printf("2. View Contributions\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: searchPlanet(); break;
        case 2: {
            // For simplicity, assuming researcher 0 for now, can extend for actual logged-in researcher
            printf("Total contributions by this researcher: %d\n", researchers[0].contributions);
            break;
        }
        case 3: return;
        default: printf("Invalid choice. Please try again.\n");
        }
    }
}

// Add a planet
void addPlanet() {
    if (planet_count >= MAX_PLANETS) {
        printf("Planet catalogue is full!\n");
        return;
    }

    Planet new_planet;
    printf("Enter planet name: ");
    getchar(); // consume newline character
    fgets(new_planet.name, MAX_NAME_LENGTH, stdin);
    new_planet.name[strcspn(new_planet.name, "\n")] = 0; // remove newline from input

    printf("Enter planet type: ");
    fgets(new_planet.type, MAX_NAME_LENGTH, stdin);
    new_planet.type[strcspn(new_planet.type, "\n")] = 0;

    printf("Enter planet size: ");
    scanf("%lf", &new_planet.size);

    printf("Enter distance from star (in AU): ");
    scanf("%lf", &new_planet.distance_from_star);

    printf("Enter orbital period (in Earth years): ");
    scanf("%lf", &new_planet.orbital_period);

    printf("Enter planet description: ");
    getchar(); // consume newline character
    fgets(new_planet.description, MAX_DESC_LENGTH, stdin);
    new_planet.description[strcspn(new_planet.description, "\n")] = 0;

    printf("Is this planet discovered? (1 for Yes, 0 for No): ");
    scanf("%d", &new_planet.discovered);

    printf("Is this planet observed? (1 for Yes, 0 for No): ");
    scanf("%d", &new_planet.observed);

    planets[planet_count] = new_planet;
    planet_count++;
    printf("Planet added successfully!\n");
}

// Edit a planet
void editPlanet() {
    char name[MAX_NAME_LENGTH];
    printf("Enter planet name to edit: ");
    getchar(); // consume newline character
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // remove newline from input

    int idx = findPlanetByName(name);
    if (idx == -1) {
        printf("Planet not found.\n");
        return;
    }

    Planet* planet = &planets[idx];

    printf("Edit planet size (current: %.2lf): ", planet->size);
    scanf("%lf", &planet->size);

    printf("Edit distance from star (current: %.2lf AU): ", planet->distance_from_star);
    scanf("%lf", &planet->distance_from_star);

    printf("Edit orbital period (current: %.2lf years): ", planet->orbital_period);
    scanf("%lf", &planet->orbital_period);

    printf("Edit description: ");
    getchar(); // consume newline character
    fgets(planet->description, MAX_DESC_LENGTH, stdin);
    planet->description[strcspn(planet->description, "\n")] = 0;

    printf("Planet updated successfully!\n");
}

// Remove a planet
void removePlanet() {
    char name[MAX_NAME_LENGTH];
    printf("Enter planet name to remove: ");
    getchar(); // consume newline character
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // remove newline from input

    int idx = findPlanetByName(name);
    if (idx == -1) {
        printf("Planet not found.\n");
        return;
    }

    for (int i = idx; i < planet_count - 1; i++) {
        planets[i] = planets[i + 1]; // shift planets down
    }
    planet_count--;
    printf("Planet removed successfully!\n");
}

// Search for a planet by name
void searchPlanet() {
    char name[MAX_NAME_LENGTH];
    printf("Enter planet name to search: ");
    getchar(); // consume newline character
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // remove newline from input

    int idx = findPlanetByName(name);
    if (idx == -1) {
        printf("Planet not found.\n");
    }
    else {
        printPlanetDetails(planets[idx]);
    }
}

// Add a researcher
void addResearcher() {
    if (researcher_count >= MAX_RESEARCHERS) {
        printf("Researcher list is full!\n");
        return;
    }

    Researcher new_researcher;
    new_researcher.id = researcher_count + 1;

    printf("Enter researcher name: ");
    getchar(); // consume newline character
    fgets(new_researcher.name, MAX_NAME_LENGTH, stdin);
    new_researcher.name[strcspn(new_researcher.name, "\n")] = 0; // remove newline

    printf("Enter researcher email: ");
    fgets(new_researcher.email, MAX_NAME_LENGTH, stdin);
    new_researcher.email[strcspn(new_researcher.email, "\n")] = 0;

    new_researcher.contributions = 0;

    researchers[researcher_count] = new_researcher;
    researcher_count++;
    printf("Researcher added successfully!\n");
}

// Edit researcher
void editResearcher() {
    int id;
    printf("Enter researcher ID to edit: ");
    scanf("%d", &id);

    int idx = findResearcherById(id);
    if (idx == -1) {
        printf("Researcher not found.\n");
        return;
    }

    Researcher* researcher = &researchers[idx];
    printf("Edit researcher name (current: %s): ", researcher->name);
    getchar(); // consume newline
    fgets(researcher->name, MAX_NAME_LENGTH, stdin);
    researcher->name[strcspn(researcher->name, "\n")] = 0;

    printf("Edit researcher email (current: %s): ", researcher->email);
    fgets(researcher->email, MAX_NAME_LENGTH, stdin);
    researcher->email[strcspn(researcher->email, "\n")] = 0;

    printf("Researcher updated successfully!\n");
}

// View statistics
void viewStatistics() {
    int discovered = 0, observed = 0;
    for (int i = 0; i < planet_count; i++) {
        if (planets[i].discovered) discovered++;
        if (planets[i].observed) observed++;
    }

    printf("Number of planets catalogued: %d\n", planet_count);
    printf("Number of discovered planets: %d\n", discovered);
    printf("Number of observed planets: %d\n", observed);
}

// Helper function to find planet by name
int findPlanetByName(char* name) {
    for (int i = 0; i < planet_count; i++) {
        if (strcmp(planets[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Helper function to find researcher by ID
int findResearcherById(int id) {
    for (int i = 0; i < researcher_count; i++) {
        if (researchers[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Print planet details
void printPlanetDetails(Planet planet) {
    printf("\nPlanet Details:\n");
    printf("Name: %s\n", planet.name);
    printf("Type: %s\n", planet.type);
    printf("Size: %.2lf\n", planet.size);
    printf("Distance from Star: %.2lf AU\n", planet.distance_from_star);
    printf("Orbital Period: %.2lf years\n", planet.orbital_period);
    printf("Description: %s\n", planet.description);
    printf("Discovered: %s\n", planet.discovered ? "Yes" : "No");
    printf("Observed: %s\n", planet.observed ? "Yes" : "No");
}
