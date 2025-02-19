#include "liblvgl/core/lv_obj.h"
#include "liblvgl/widgets/lv_btn.h"
#include "main.h" // IWYU pragma: keep
#include "graphics.h" // IWYU pragma: keep

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

   if (code == LV_EVENT_CLICKED) {
      std::cout << "Clicked" << std::endl;
   } else if (code == LV_EVENT_VALUE_CHANGED) {
      std::cout << "Toggled" << std::endl;
   }
}

void mainScreen() {
  lv_obj_t *screen = lv_obj_create(NULL);
  lv_obj_t *label;

  lv_obj_t *button = lv_btn_create(screen);
  lv_obj_add_event_cb(button, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(button, LV_ALIGN_CENTER, 0, -40);

  label = lv_label_create(button);
  lv_label_set_text(label, "Button");
  lv_obj_center(label);

  lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  label = lv_label_create(btn2);
  lv_label_set_text(label, "Toggle");
  lv_obj_center(label);
}