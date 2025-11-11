/*//////////////////////////////////////////////////////////////////////
INCLUDE FILES AND LIBRARIES
//////////////////////////////////////////////////////////////////////*/


#include "lv_examples.h"
#include "../../src/assets/icons/paused.c"
#include "../../src/assets/icons/next.c"
#include "../../src/assets/icons/previous.c"
#include "../../src/assets/icons/play.c"
#include <string.h>   // strcmp

/*//////////////////////////////////////////////////////////////////////
DECLARATIONS
//////////////////////////////////////////////////////////////////////*/


LV_IMG_DECLARE(paused);
LV_IMG_DECLARE(next);
LV_IMG_DECLARE(previous);
LV_IMG_DECLARE(play);

/*//////////////////////////////////////////////////////////////////////
REFERENCE FUNCTION
//////////////////////////////////////////////////////////////////////*/


/*  RADIAL GRADIENT BACKGROUND EXAMPLE FUNCTION

void lv_example_style_17(void)
{
    static const lv_color_t grad_colors[2] = {
        LV_COLOR_MAKE(0x9B, 0x18, 0x42),
        LV_COLOR_MAKE(0x00, 0x00, 0x00),
    };

    int32_t width = lv_display_get_horizontal_resolution(NULL);
    int32_t height = lv_display_get_vertical_resolution(NULL);

    static lv_style_t style;
    lv_style_init(&style);

    //First define a color gradient. In this example we use a purple to black color map.
    static lv_grad_dsc_t grad;

    lv_grad_init_stops(&grad, grad_colors, NULL, NULL, sizeof(grad_colors) / sizeof(lv_color_t));

    //Make a radial gradient with the center in the middle of the object, extending to the farthest corner
    lv_grad_radial_init(&grad, LV_GRAD_CENTER, LV_GRAD_CENTER, LV_GRAD_RIGHT, LV_GRAD_BOTTOM, LV_GRAD_EXTEND_PAD);

    //Set gradient as background
    lv_style_set_bg_grad(&style, &grad);

    //Create an object with the new style
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_set_size(obj, width, height);
    lv_obj_center(obj);
}
*/



/*  SLIDER WITH LABEL EXAMPLE FUNCTION

static void slider_event_cb(lv_event_t * e);
static lv_obj_t * slider_label;

// A default slider with a label displaying the current value

void lv_example_slider_1(void)
{
    //Create a slider in the center of the display
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    lv_obj_center(slider);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_set_style_anim_duration(slider, 2000, 0);
    //Create a label below the slider
    slider_label = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label, "0%");

    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target_obj(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
*/



/*

*/


/*//////////////////////////////////////////////////////////////////////
RADIAL GRADIENT BACKGROUND FUNCTION
//////////////////////////////////////////////////////////////////////*/





// My version
void radial_gradient_background(void)
{
    static const lv_color_t grad_colors[2] = {
        LV_COLOR_MAKE(0xEE, 0xEE, 0xEE),
        LV_COLOR_MAKE(0x80, 0x80, 0x80),
    };

    static lv_style_t style;
    lv_style_init(&style);

    //First define a color gradient.
    static lv_grad_dsc_t grad;

    lv_grad_init_stops(&grad, grad_colors, NULL, NULL, sizeof(grad_colors) / sizeof(lv_color_t));

    //Make a radial gradient with the center in the middle of the object, extending to the farthest corner
    lv_grad_radial_init(&grad, LV_GRAD_CENTER, LV_GRAD_CENTER, LV_GRAD_RIGHT, LV_GRAD_BOTTOM, LV_GRAD_EXTEND_PAD);

    //Set gradient as background
    lv_style_set_bg_grad(&style, &grad);

    lv_obj_t * scr = lv_screen_active();
    lv_obj_add_style(scr, &style, 0);
}

/*//////////////////////////////////////////////////////////////////////
PROGRESS BAR WITH LABELS AND BUTTONS FUNCTION
//////////////////////////////////////////////////////////////////////*/











static void slider_event_cb(lv_event_t * e);
static lv_obj_t * slider_label;
static lv_obj_t * slider_label2;
static lv_obj_t * g_slider;          // store slider for button control
static lv_obj_t * song_ticker;       // container
static lv_obj_t * song_label;        // text
static lv_obj_t * btn_prev;
static lv_obj_t * btn_pause;
static lv_obj_t * btn_next;

static lv_obj_t * img_pause;

static bool is_paused = false;       // pause state

static lv_obj_t * slider;


static void layout_update(void)
{
    LV_LOG_INFO("Layout update called");
    if(slider)  lv_obj_align(slider, LV_ALIGN_BOTTOM_MID, 0, -120);
    if(song_ticker && slider) lv_obj_align_to(song_ticker, slider, LV_ALIGN_OUT_TOP_MID, 0, -12);
    if(slider_label && slider)  lv_obj_align_to(slider_label,  slider, LV_ALIGN_OUT_BOTTOM_LEFT, -10, 10);
    if(slider_label2 && slider) lv_obj_align_to(slider_label2, slider, LV_ALIGN_OUT_BOTTOM_RIGHT, 10, 10);
    if(btn_prev && slider)  lv_obj_align_to(btn_prev,  slider, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 40);
    if(btn_pause && slider) lv_obj_align_to(btn_pause, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);
    if(btn_next && slider)  lv_obj_align_to(btn_next,  slider, LV_ALIGN_OUT_BOTTOM_RIGHT, -10, 40);
}

static void screen_resize_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    layout_update();
}






static void start_song_ticker(void)
{
    /* Ensure sizes are computed */
    lv_obj_update_layout(song_ticker);

    int w_text = lv_obj_get_width(song_label);
    int w_view = lv_obj_get_width(song_ticker);

    if(w_text <= w_view) {
        lv_obj_set_x(song_label, 0);
        return;
    }

    lv_obj_set_x(song_label, 0);
    lv_anim_del(song_label, (lv_anim_exec_xcb_t)lv_obj_set_x);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, song_label);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_values(&a, 0, -(w_text - w_view + 8));  // full travel with padding
    lv_anim_set_time(&a, 12000);                        // slower = larger
    lv_anim_set_delay(&a, 3000);                        // initial pause
    lv_anim_set_repeat_delay(&a, 5000);                 // pause between loops
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

static void restart_song_title(const char * title)
{
    lv_anim_del(song_label, (lv_anim_exec_xcb_t)lv_obj_set_x);
    if(title) lv_label_set_text(song_label, title);
    lv_obj_set_x(song_label, 0);
    start_song_ticker();
}

static void button_event_cb(lv_event_t * e)
{
    const char * tag = (const char *)lv_event_get_user_data(e);
    if(!tag) return;

    if(strcmp(tag, "prev") == 0) {
        lv_slider_set_value(g_slider, 0, LV_ANIM_OFF);
        lv_label_set_text(slider_label, "0:00");              // reset time label
        restart_song_title(NULL);               // reset song title scroll
        LV_LOG_USER("Prev: slider + title reset");
    }
    else if(strcmp(tag, "pause") == 0) {
        is_paused = !is_paused;
        LV_LOG_USER("Pause toggled. Now %s", is_paused ? "PAUSED" : "PLAYING");
        lv_obj_set_style_bg_opa(g_slider, is_paused ? LV_OPA_80 : LV_OPA_COVER, LV_PART_INDICATOR);

        if(img_pause) {                                   // safety guard
            lv_img_set_src(img_pause, is_paused ? &play : &paused);
        }
    }
    else if(strcmp(tag, "next") == 0) {
        lv_slider_set_value(g_slider, 0, LV_ANIM_OFF);
        lv_label_set_text(slider_label, "0:00");              // reset time label
        restart_song_title(NULL);              // reset song title scroll
        LV_LOG_USER("Next: slider + title reset");
    }
}


static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target_obj(e);

    const int track_len_sec = 225; // 3:45
    int32_t v      = lv_slider_get_value(slider);
    int32_t vmax   = lv_slider_get_max_value(slider);   // now 1000
    int32_t seconds = (int32_t)((int64_t)v * track_len_sec / vmax);

    int mins = seconds / 60;
    int secs = seconds % 60;
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%d:%02d", mins, secs);
    lv_label_set_text(slider_label, buf);
}


/**
 * A default slider with a label displaying the current value
 */

void progress_bar(void)
{
    // Create a slider in the center of the display

    slider = lv_slider_create(lv_screen_active());
    g_slider = slider;
    lv_obj_set_width(slider, 260);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_range(slider, 0, 1000);
    lv_obj_set_style_anim_duration(slider, 2000, 0);






    // TICKER CONTAINER
    song_ticker = lv_obj_create(lv_screen_active());
    lv_obj_set_size(song_ticker, lv_obj_get_width(slider), LV_SIZE_CONTENT);
    lv_obj_clear_flag(song_ticker, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(song_ticker, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_opa(song_ticker, LV_OPA_TRANSP, 0);
    lv_obj_align_to(song_ticker, slider, LV_ALIGN_OUT_TOP_MID, 0, -12);

    // Song title label
    song_label = lv_label_create(song_ticker);
    lv_obj_set_width(song_label, LV_SIZE_CONTENT);            // expand to text width
    lv_label_set_long_mode(song_label, LV_LABEL_LONG_CLIP);   // single line, no wrap
    lv_label_set_text(song_label, "dodger blue - (feat. Wallie the Sensei, Siete7x & Roddy Ricch)  ");
    lv_obj_align(song_label, LV_ALIGN_LEFT_MID, 0, 0);

    /* Start ticker after label width is known */
    start_song_ticker();




    // Set slider background (track) to medium grey
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x999999), LV_PART_MAIN);

    // Set slider bar (filled portion) to light grey
    lv_obj_set_style_bg_color(slider, lv_color_hex(0xD9D9D9), LV_PART_INDICATOR);

    // Hide the knob by making it transparent and size 0
    lv_obj_set_style_opa(slider, LV_OPA_TRANSP, LV_PART_KNOB);

    // Create labels below / beside the slider
    slider_label = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label, "0:00");

    slider_label2 = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label2, "3:45");

    // Align labels once at creation
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_LEFT, -10, 10);
    lv_obj_align_to(slider_label2, slider, LV_ALIGN_OUT_BOTTOM_RIGHT, 10, 10);

    /* Create three image buttons under the progress bar */


    // PREVIOUS BUTTON
    btn_prev = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_prev, 50, 50);  // Make it square first
    lv_obj_add_event_cb(btn_prev, button_event_cb, LV_EVENT_CLICKED, (void*)"prev");
    lv_obj_set_style_bg_color(btn_prev, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(btn_prev, LV_OPA_TRANSP, 0);  // Make transparent
    lv_obj_set_style_radius(btn_prev, LV_RADIUS_CIRCLE, 0);  // Circle!

    lv_obj_t * img_prev = lv_img_create(btn_prev);
    lv_img_set_src(img_prev, &previous);
    lv_obj_center(img_prev);

    // PAUSE BUTTON
    btn_pause = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_pause, 50, 50);  // Make it square
    lv_obj_add_event_cb(btn_pause, button_event_cb, LV_EVENT_CLICKED, (void*)"pause");
    lv_obj_set_style_bg_color(btn_pause, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(btn_pause, LV_OPA_TRANSP, 0);  // Make transparent
    lv_obj_set_style_radius(btn_pause, LV_RADIUS_CIRCLE, 0);  // Circle!

    img_pause = lv_img_create(btn_pause);
    lv_img_set_src(img_pause, &paused);
    lv_obj_center(img_pause);

    // NEXT BUTTON
    btn_next = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_next, 50, 50);  // Make it square
    lv_obj_add_event_cb(btn_next, button_event_cb, LV_EVENT_CLICKED, (void*)"next");
    lv_obj_set_style_bg_color(btn_next, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(btn_next, LV_OPA_TRANSP, 0);  // Make transparent
    lv_obj_set_style_radius(btn_next, LV_RADIUS_CIRCLE, 0);  // Circle!

    lv_obj_t * img_next = lv_img_create(btn_next);
    lv_img_set_src(img_next, &next);
    lv_obj_center(img_next);






    static bool resize_evt_added = false;
    if(!resize_evt_added) {
        resize_evt_added = true;
        lv_obj_add_event_cb(lv_screen_active(), screen_resize_cb, LV_EVENT_SIZE_CHANGED, NULL);
    }

    // After creating all related objects call:
    layout_update();
}
