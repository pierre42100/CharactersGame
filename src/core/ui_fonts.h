#ifndef UI_FONTS_H_INCLUDED
#define UI_FONTS_H_INCLUDED

/**
 * UI fonts - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Font styles definition
 */
#define FONT_STYLE_NORMAL 0
#define FONT_STYLE_BOLD 1
#define FONT_STYLE_ITALIC 2
#define FONT_STYLE_UNDERLINE 3
#define FONT_STYLE_STRIKETHROUGH 4

/**
 * Font rendering modes
 */
#define FONT_RENDERING_SOLID 0
#define FONT_RENDERING_SHADED 1
#define FONT_RENDERING_BLENDED 2

/**
 * UI_Text object definition
 */
typedef struct UI_Text {

    //Message of the text
    char *message;

    //Target texture
    SDL_Texture *targetTexture;

    //Position on the texture
    int x;
    int y;

    //Text size & style
    int text_height;
    int text_width;
    int style;
    SDL_Color color;
    SDL_Color bgcolor; //Useful only if rendering mode is set to shaded

    //Rendering mode
    int render_mode;

} UI_Text;

/**
 * Initializate font library & open main programm font
 *
 * @param const char *filename Path to the TTF file
 * @param int ptsize Characters size to use
 */
void ui_font_init(const char *filename, int ptsize);

/**
 * Quit font library
 */
void ui_font_quit();

/**
 * Create a text variable
 *
 * @param const char *message The message of the object
 * @param int height The height of the newly created message
 * @return UI_Text Created write object with default options
 */
UI_Text ui_font_create_variable(char *message, int height);

/**
 * Write a text object on a texture
 *
 * @param UI_Text *data Informations about the text object
 */
void ui_font_write_texture(UI_Text *data);

/**
 * Prepare text rendering
 *
 * @param int style The style of the text
 */
void ui_font_prepare_rendering(int style);

/**
 * Determine the room taken by a text before rendering it
 *
 * @param UI_Text *data Informations about the text object
 */
void ui_font_determine_text_size(UI_Text *data);

/**
 * Update the font style of a message structure
 *
 * @param UI_Text *data Informations about the text object to update
 * @param int new_style The new style to use
 */
void ui_font_set_style(UI_Text *data, int new_style);

/**
 * Set the target texture of a message structure
 *
 * @param UI_Text *data Informations about the text object to update
 * @param SDL_Texture *texture The target texture of the message (NULL = Renderer)
 */
void ui_font_set_target_texture(UI_Text *data, SDL_Texture *texture);

/**
 * Set the coordinates where a message structure should be applied
 *
 * @param UI_Text *data Informations about the text object to update
 * @param int x
 * @param int y > Coordinates of the texture
 */
void ui_font_set_coordinates(UI_Text *data, int x, int y);

/**
 * Set a new message to a text structure
 *
 * @param UI_Text *data Informations about the text object to update
 * @param char *message The new message
 */
void ui_font_set_message(UI_Text *data, char *message);

/**
 * Set new message rendering mode
 *
 * @param UI_Text *data Informations about the text object to update
 * @param int renderer The rendering option
 */
void ui_font_set_rendering_mode(UI_Text *data, int rendering_mode);

#endif // UI_FONTS_H_INCLUDED
