#include "lv_examples.h"
#include "../../src/assets/icons/paused.c"
#include "../../src/assets/icons/next.c"
#include "../../src/assets/icons/previous.c"
LV_IMG_DECLARE(paused);
LV_IMG_DECLARE(next);
LV_IMG_DECLARE(previous);
/**
 * Using radial gradient as background
 */
void radial_gradient_background(void)
{
    static const lv_color_t grad_colors[2] = {
        LV_COLOR_MAKE(0xEE, 0xEE, 0xEE),
        LV_COLOR_MAKE(0x80, 0x80, 0x80),
    };

    int32_t width = lv_display_get_horizontal_resolution(NULL);
    int32_t height = lv_display_get_vertical_resolution(NULL);

    static lv_style_t style;
    lv_style_init(&style);

    /*First define a color gradient. I use a white to light gray color map.*/
    static lv_grad_dsc_t grad;

    lv_grad_init_stops(&grad, grad_colors, NULL, NULL, sizeof(grad_colors) / sizeof(lv_color_t));

    /*Make a radial gradient with the center in the middle of the object, extending to the farthest corner*/
    lv_grad_radial_init(&grad, LV_GRAD_CENTER, LV_GRAD_CENTER, LV_GRAD_RIGHT, LV_GRAD_BOTTOM, LV_GRAD_EXTEND_PAD);

    /*Set gradient as background*/
    lv_style_set_bg_grad(&style, &grad);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_set_size(obj, width, height);
    lv_obj_center(obj);
}

static void slider_event_cb(lv_event_t * e);
static lv_obj_t * slider_label;
static lv_obj_t * slider_label2;

static void button_event_cb(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target_obj(e);

    if (btn == (lv_obj_t *)lv_event_get_user_data(e)) {
        LV_LOG_USER("Button pressed");
    }
}


/**
 * A default slider with a label displaying the current value
 */
// ...existing code...

void progress_bar(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    lv_obj_set_pos(slider, 30, 300);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_set_style_anim_duration(slider, 2000, 0);

    /* Set slider background (track) to medium grey */
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x999999), LV_PART_MAIN);

    /* Set slider bar (filled portion) to light grey */
    lv_obj_set_style_bg_color(slider, lv_color_hex(0xCCCCCC), LV_PART_INDICATOR);

    /* Hide the knob by making it transparent and size 0 */
    lv_obj_set_style_opa(slider, LV_OPA_TRANSP, LV_PART_KNOB);
    lv_obj_set_style_width(slider, 0, LV_PART_KNOB);
    lv_obj_set_style_height(slider, 0, LV_PART_KNOB);

    /*Create labels below / beside the slider*/
    slider_label = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label, "0:00");

    slider_label2 = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label2, "3:45");

    /* Align labels once at creation */
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_LEFT, -10, 10);
    lv_obj_align_to(slider_label2, slider, LV_ALIGN_OUT_BOTTOM_RIGHT, 10, 10);

    /* Create three image buttons under the progress bar */


    /* Prev button */
    lv_obj_t * btn_prev = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_prev, 50, 50);  /* Make it square first */
    lv_obj_align_to(btn_prev, slider, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 40);
    lv_obj_add_event_cb(btn_prev, button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(btn_prev, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(btn_prev, LV_RADIUS_CIRCLE, 0);  /* Circle! */

    lv_obj_t * img_prev = lv_img_create(btn_prev);
    lv_img_set_src(img_prev, &previous);
    lv_obj_center(img_prev);

    /* Pause button (center) */
    lv_obj_t * btn_pause = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_pause, 50, 50);  /* Make it square */
    lv_obj_align_to(btn_pause, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);
    lv_obj_add_event_cb(btn_pause, button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(btn_pause, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(btn_pause, LV_RADIUS_CIRCLE, 0);  /* Circle! */

    lv_obj_t * img_pause = lv_img_create(btn_pause);
    lv_img_set_src(img_pause, &paused);
    lv_obj_center(img_pause);

    /* Next button */
    lv_obj_t * btn_next = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_next, 50, 50);  /* Make it square */
    lv_obj_align_to(btn_next, slider, LV_ALIGN_OUT_BOTTOM_RIGHT, -10, 40);
    lv_obj_add_event_cb(btn_next, button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(btn_next, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(btn_next, LV_RADIUS_CIRCLE, 0);  /* Circle! */

    lv_obj_t * img_next = lv_img_create(btn_next);
    lv_img_set_src(img_next, &next);
    lv_obj_center(img_next);
}

// ...existing code...

// ...existing code...

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target_obj(e);
    /* Format the slider value as minutes:seconds (mm:ss).
     * Interpretation: slider value represents seconds. Adjust if you use a different unit.
     */
    const int length_of_track_in_seconds = 225; // e.g., 3 minutes 45 seconds
    int val = (int)lv_slider_get_value(slider)*length_of_track_in_seconds/100; // assuming slider max is 100
    int mins = val / 60;
    int secs = val % 60;
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%d:%02d", mins, secs);
    lv_label_set_text(slider_label, buf);
}
