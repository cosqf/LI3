#include <ncurses.h>
#include <panel.h>

#ifndef _INTERACTIVE_UTILS_H_
#define _INTERACTIVE_UTILS_H_

#define maxSize 60

/**
 * @brief Reads a numeric input from the user with constraints and validation.
 * This function prompts the user to enter a number within a specified range (minVal to maxVal). 
 * The function allows exiting by typing "exit", "ex" or "exi" (for 2 and 3 digit numbers).
 * 
 * @param win A pointer to the ncurses window for displaying input prompts.
 * @param posy The y-coordinate in the window where the input starts.
 * @param posx The x-coordinate in the window where the input starts.
 * @param digits The maximum number of digits allowed for input.
 * @param minVal The minimum acceptable value for the numeric input.
 * @param maxVal The maximum acceptable value for the numeric input.
 * 
 * @return The parsed number if input is valid or -1 if the user exits.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int getNumberFromInput (WINDOW* win, int posy, int posx, int digits, int minVal, int maxVal);


/**
 * @brief Reads a string from input.

 * @param win A pointer to the ncurses window for displaying input prompts. 
 * @param posy The y-coordinate in the window the text will be printed.
 * @param posx The x-coordinate in the window the text will be printed.
 * @param string A string buffer to store the input.
 * @param digits The maximum number of digits allowed for input.

 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
void getStringFromInput (WINDOW* win, int posy, int posx, char* string, int digits);

/**
 * @brief Reads an ID from input ("A0000000").
 * This function will check if the format is correct and only allow for User and Artist IDs.
 * 
 * @param win A pointer to the ncurses window for displaying input prompts. 
 * @param posy The y-coordinate in the window the text will be printed.
 * @param posx The x-coordinate in the window the text will be printed.
 * @param idString A string buffer to store the ID input.
 * @param flag Flag == 0: Will only accept Users as correct, Flag == 1: Will accept both Users and Artist IDs.
 * 
 * @return Returns the number of the ID.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int getIdFromInput (WINDOW* win, int posy, int posx, char* idString, int flag); // flag == 0 : just users, flag == 1 : users and artists

/**
 * @brief Reads the output file and returns an array with every line.
 * This function reads the file "resultados/command1_output.txt", reading a specified number of lines and storing every line.
 * 
 * @return An array of strings with the lines it read.
 */
char** readOutputFiles();

/**
 * @brief Will print the output results wrapping around the screen.
 * 
 * @param win A pointer to the ncurses window for displaying input prompts.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
void printResults (WINDOW* win);

/**
 * @brief Prints text in a window, with the option to be highlighted.
 * 
 * @param win A pointer to the ncurses window for displaying input prompts.
 * @param y The y-coordinate in the window the text will be printed.
 * @param x The x-coordinate in the window the text will be printed.
 * @param text The string that will be printed
 * @param highlight A flag that will tell if the text should be highlighted.
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
void printHighlightedText (WINDOW* win, int y, int x, char* text, bool highlight);


/**
 * @brief Prints a string with word wrapping.
 * This function displays a long string inside an ncurses window, wrapping
 * the text to fit within the specified width of the window, starting from 
 * the given position. This function will cut the words when wrapping.
 *
 * @param win A pointer to the ncurses window where the text will be printed.
 * @param str The string to be printed.
 * @param posy The y-coordinate where the printing starts.
 * @param posx The x-coordinate where the printing starts.
 *
 * @return The number of lines printed after wrapping.
 *
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int printWrapped (WINDOW* win, char* str, int posy, int posx);

/**
 * @brief This function will count how many lines a string will occupy with wrapping.
 * 
 * @param width The width of the screen.
 * @param str The string to be printed.
 * @param posx The x-coordinate where the printing starts.
 * 
 * @return The number of lines printed after wrapping.
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
int countLines (int width, char* str, int posx);

/**
 * @brief Displays output results in a scrollable ncurses pad.
 *
 * This function reads results from output files and displays them in a 
 * scrollable interface using an ncurses pad. It supports vertical scrolling
 * with arrow keys and allows exiting the view by pressing the 'Esc' key.
 *
 * @param height The height of the visible scrollable area.
 * @param width The width of the visible scrollable area.
 * @param posy The y-coordinate where the scrollable area starts.
 * @param posx The x-coordinate where the scrollable area starts.
 * 
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
void readResultsScrollable(int height, int width, int posy, int posx);

/**
 * @brief Will create a new window with a border around it.
 * 
 * @param height The height of the window.
 * @param width The width of the window.
 * @param posy The y-coordinate in the window where the input starts.
 * @param posx The x-coordinate in the window where the input starts.
 * 
 * @return A pointer to the newly created window.
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
WINDOW* newWindowWithBorder (int height, int width, int posy, int pox);

/**
 * @brief Will load a dot animation
 * @note 
 * This function uses ncurses for input and display, so it should be called within an ncurses session.
 */
void loadDotAnimation ();

#endif