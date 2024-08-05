#ifndef WELCOME_PART_H
#define WELCOME_PART_H

#include <iostream> // Voor invoer/uitvoer operaties
#include <Windows.h> // Voor Windows-specifieke functies zoals system() en Sleep()

// Function declarations
void setupConsole(); // Verklaring van de functie setupConsole()
void displayWelcomeScreen(); // Verklaring van de functie displayWelcomeScreen()
void displayProgressBar(); // Verklaring van de functie displayProgressBar()

// Function definitions
inline void setupConsole() {
    // Stel de tekstkleur van de console in op wit (0F)
    system("COLOR 0F"); // Wijzigt de console tekstkleur naar wit

    // Wis het scherm van de console
    system("cls"); // Verwijdert alle tekst van de console
}

inline void displayWelcomeScreen() {
    // Print de titel van het spel
    printf("\Memory Card game"); // Drukt de titel "Memory Card game" af in de console

    // Stel de codepagina in op 437 voor correcte ASCII-tekenweergave
    SetConsoleCP(437); // Wijzigt de codepagina van de console naar 437 (IBM PC)

    // Stel de uitvoer codepagina van de console in op 437 voor correcte weergave van ASCII-tekens
    SetConsoleOutputCP(437); // Wijzigt de uitvoer codepagina van de console naar 437 (IBM PC)

    // Toon het welkomstbericht en de namen van de spelers
    std::cout << "\n\n\n\n\n\t\t\t\t\tWELCOME"; // Toont "WELCOME" op het scherm met voldoende afstand boven en links
    std::cout << "\n\n\n\n\t\t\t\t PLAYER 1      PLAYER 2 "; // Toont de spelersnamen met afstand erboven
}

inline void displayProgressBar() {
    int bar1 = 176, bar2 = 219; // Definieert de karakters voor de lege en gevulde voortgangsbalk

    std::cout << "\n\n\n\t\t\t\t"; // Voegt afstand toe voor de voortgangsbalk

    // Toon de lege voortgangsbalk
    for (int i = 0; i < 25; i++) {
        std::cout << (char)bar1; // Print teken 176 (lege balk) 25 keer
    }

    std::cout << "\r"; // Zet de cursor terug naar het begin van de regel
    std::cout << "\t\t\t\t"; // Voegt afstand toe

    // Animeer het vullen van de voortgangsbalk
    for (int i = 0; i < 25; i++) {
        std::cout << (char)bar2; // Print teken 219 (gevulde balk) 25 keer
        Sleep(150); // Wacht 150 milliseconden tussen elke stap
    }

    std::cout << "\n\t\t\t\t" << (char)1 << "!"; // Print een uitroepteken na de voortgangsbalk
}

#endif // WELCOME_PART_H

#pragma once
