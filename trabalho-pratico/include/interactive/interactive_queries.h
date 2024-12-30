#include <ncurses.h>
#include <panel.h>

#ifndef _INTERACTIVE_QUERIES_H_
#define _INTERACTIVE_QUERIES_H_

/**
 * @brief Displays the first query in an interface.
 * This function will prompt the user to insert an user or artist ID and 
 * will show the result of the query 1.
 * 
 * @param inWin A pointer to the window where the inputs will be shown.
 * @param outWin A pointer to the window where the outputs will be shown.
 * @param mngr A pointer to the main manager.
 * 
 * @result 0 if the function ends normally and -1 if the user exits earlier.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int loadQ1 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

/**
 * @brief Displays the second query in an interface.
 * This function will prompt the user for a number of artists and, optionally, a country.
 * It will then show in a scrollable window the results of the query2.
 * 
 * @param inWin A pointer to the window where the inputs will be shown.
 * @param mngr A pointer to the main manager.
 * 
 * @result 0 if the function ends normally and -1 if the user exits earlier.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int loadQ2 (WINDOW* inWin, hashtableManager* mngr);

/**
 * @brief Displays the third query in an interface.
 * This function will prompt the user for a minimum and maximum age and then
 * will show the result of the query 3.
 * 
 * @param inWin A pointer to the window where the inputs will be shown.
 * @param outWin A pointer to the window where the outputs will be shown.
 * @param mngr A pointer to the main manager.
 * 
 * @result 0 if the function ends normally and -1 if the user exits earlier.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int loadQ3 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

/**
 * @brief Displays the fourth query in an interface.
 * This function will ask the user if they want to insert any filters in a menu interface. 
 * If they choose to add filters, they'll be prompted to insert two dates in the YYYY/MM/DD format.
 * It will then show the result of the query 4.
 * 
 * @param inWin A pointer to the window where the inputs will be shown.
 * @param outWin A pointer to the window where the outputs will be shown.
 * @param mngr A pointer to the main manager.
 * 
 * @result 0 if the function ends normally and -1 if the user exits earlier.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int loadQ4 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

/**
 * @brief Displays the fifth query in an interface.
 * This function will prompt the user to insert an user ID and the number of recommendations.
 * It will then show in a scrollable window the results of the query5.
 * 
 * @param inWin A pointer to the window where the inputs will be shown.
 * @param mngr A pointer to the main manager.
 * 
 * @result 0 if the function ends normally and -1 if the user exits earlier.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int loadQ5 (WINDOW* inWin, hashtableManager* mngr);
#endif