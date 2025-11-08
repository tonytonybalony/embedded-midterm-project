#include "lv_examples.h"
#include "../../src/assets/icons/paused.c"
#include "../../src/assets/icons/next.c"
#include "../../src/assets/icons/previous.c"
#include <string.h>   /* for strcmp */

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
static lv_obj_t * g_slider;          /* store slider for button control */
static bool is_paused = false;       /* simple pause state */


static void button_event_cb(lv_event_t * e)
{
    const char * tag = (const char *)lv_event_get_user_data(e);
    if(!tag) return;

    if(strcmp(tag, "prev") == 0) {
        lv_slider_set_value(g_slider, 0, LV_ANIM_OFF);
        lv_label_set_text(slider_label, "0:00");              /* reset time label */
        LV_LOG_USER("Prev: slider reset to 0");
    }
    else if(strcmp(tag, "pause") == 0) {
        is_paused = !is_paused;
        LV_LOG_USER("Pause toggled. Now %s", is_paused ? "PAUSED" : "PLAYING");
        lv_obj_set_style_bg_opa(g_slider, is_paused ? LV_OPA_80 : LV_OPA_COVER, LV_PART_INDICATOR);
    }
    else if(strcmp(tag, "next") == 0) {
        lv_slider_set_value(g_slider, 0, LV_ANIM_OFF);
        lv_label_set_text(slider_label, "0:00");              /* reset time label */
        LV_LOG_USER("Next: slider reset to 0");
    }
}


/**
 * A default slider with a label displaying the current value
 */

void progress_bar(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    g_slider = slider; /* store globally for button events */
    lv_obj_set_pos(slider, 30, 300);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_range(slider, 0, 1000);

    lv_obj_set_style_anim_duration(slider, 2000, 0);

    /* Set slider background (track) to medium grey */
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x999999), LV_PART_MAIN);

    /* Set slider bar (filled portion) to light grey */
    lv_obj_set_style_bg_color(slider, lv_color_hex(0xD9D9D9), LV_PART_INDICATOR);

    /* Hide the knob by making it transparent and size 0 */
    lv_obj_set_style_opa(slider, LV_OPA_TRANSP, LV_PART_KNOB);

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
    lv_obj_add_event_cb(btn_prev, button_event_cb, LV_EVENT_CLICKED, (void*)"prev");
    lv_obj_set_style_bg_color(btn_prev, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(btn_prev, LV_OPA_TRANSP, 0);  /* Make transparent */
    lv_obj_set_style_border_opa(btn_prev, LV_OPA_TRANSP, 0);  /* Remove border */
    lv_obj_set_style_radius(btn_prev, LV_RADIUS_CIRCLE, 0);  /* Circle! */

    lv_obj_t * img_prev = lv_img_create(btn_prev);
    lv_img_set_src(img_prev, &previous);
    lv_obj_center(img_prev);

    /* Pause button (center) */
    lv_obj_t * btn_pause = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_pause, 50, 50);  /* Make it square */
    lv_obj_align_to(btn_pause, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);
    lv_obj_add_event_cb(btn_pause, button_event_cb, LV_EVENT_CLICKED, (void*)"pause");
    lv_obj_set_style_bg_color(btn_pause, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(btn_pause, LV_OPA_TRANSP, 0);  /* Make transparent */
    lv_obj_set_style_border_opa(btn_pause, LV_OPA_TRANSP, 0);  /* Remove border */
    lv_obj_set_style_radius(btn_pause, LV_RADIUS_CIRCLE, 0);  /* Circle! */

    lv_obj_t * img_pause = lv_img_create(btn_pause);
    lv_img_set_src(img_pause, &paused);
    lv_obj_center(img_pause);

    /* Next button */
    lv_obj_t * btn_next = lv_btn_create(lv_screen_active());
    lv_obj_set_size(btn_next, 50, 50);  /* Make it square */
    lv_obj_align_to(btn_next, slider, LV_ALIGN_OUT_BOTTOM_RIGHT, -10, 40);
    lv_obj_add_event_cb(btn_next, button_event_cb, LV_EVENT_CLICKED, (void*)"next");
    lv_obj_set_style_bg_color(btn_next, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(btn_next, LV_OPA_TRANSP, 0);  /* Make transparent */
    lv_obj_set_style_border_opa(btn_next, LV_OPA_TRANSP, 0);  /* Remove border */
    lv_obj_set_style_radius(btn_next, LV_RADIUS_CIRCLE, 0);  /* Circle! */

    lv_obj_t * img_next = lv_img_create(btn_next);
    lv_img_set_src(img_next, &next);
    lv_obj_center(img_next);
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target_obj(e);

    const int track_len_sec = 225; /* 3:45 */
    int32_t v      = lv_slider_get_value(slider);
    int32_t vmax   = lv_slider_get_max_value(slider);   /* now 1000 */
    int32_t seconds = (int32_t)((int64_t)v * track_len_sec / vmax);

    int mins = seconds / 60;
    int secs = seconds % 60;
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%d:%02d", mins, secs);
    lv_label_set_text(slider_label, buf);
}
