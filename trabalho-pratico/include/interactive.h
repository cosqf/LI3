#include <ncurses.h>
#include <panel.h>
#include <utils.h>
#include <parsing.h>
#include <almightyManager.h>

#ifndef _INTERACTIVE_H_
#define _INTERACTIVE_H_

/**
 * @brief Displays the Main Menu interface.
 * This function creates and displays a Main Menu interface with 
 * two options: "Start" and "Leave". Pressing ESC exits immediately.
 * 
 * @return 0 if "Start" is selected or -1 if "Leave" is selected or ESC is pressed.
 */
int loadMainPage ();

/**
 * @brief Asks the user for a dataset path and loads the data.
 * This function displays an input prompt to the user, allowing them 
 * to specify the path to a dataset. It validates the input path and 
 * attempts to load the data using the provided manager. 
 * If the user types "exit", the function terminates.
 * 
 * @param win A pointer to the ncurses window used for displaying input prompts.
 * @param mngr A pointer to the manager used to store the dataset.
 * 
 * @return 0 if data loading is successful or -1 if the user exits or an error occurs.

 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int gettingData (WINDOW* win, AlmightyManager* mngr);

/**
 * @brief Allows the user to choose a query in a menu.
 * 
 * @param win A pointer to the ncurses window used for displaying input prompts.
 * @return The number of the query chosen or -1 if the user presses 'Esc'.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int gettingQuery (WINDOW* win);


/**
 * @brief Loads the greeting animation.
 * This function will fetch an ASCII image and print it on the screen.
 */
void loadGreeting ();

/**
 * @brief Loads the ending the program animation.
 * This function will fetch two ASCII images and print them on the screen.
 */
void loadBye ();


#endif