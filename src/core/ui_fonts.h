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
 * Write a text on a texture at a specified position
 *
 * @param SDL_Texture *target_texture Target texture (NULL to specify renderer)
 * @param const char *message The message to write on the renderer
 * @param SDL_Color *color The color of the text to write
 * @param int x
 * @param int y > Coordinates of the text
 * @param int required_text_height The height of the text
 * @param int style The style of the text
 * @param int render_mode The mode to use to render text
 */
void ui_font_write_texture(SDL_Texture *target_texture, const char *message, SDL_Color color, int x, int y, int required_text_height, int style, int render_mode);

/**
 * Prepare text rendering
 *
 * @param int style The style of the text
 */
void ui_font_prepare_rendering(int style);

/**
 * Determine the room taken by a text before rendering it
 *
 * @param const char *message The message to calculate
 * @param int style The style of the text
 * @param int *width The width of the text (target pointer)
 * @param int required_height The height of the text
 */
void ui_font_determine_text_size(const char *message, int style, int *width, int required_height);
#endif // UI_FONTS_H_INCLUDED
