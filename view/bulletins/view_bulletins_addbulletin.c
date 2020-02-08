#include <stddef.h>
#include "view_bulletins.h"
#include "../../model/model_bulletinsform.h"
#include "../read_replace_write.h"
#include "../curr_date.h"

void render_bulletins_addbulletin(const char *username)
{
  const char **labels = model_bulletinsform_attribute_labels();
  char curr_year[8] = {'\0'};
  get_curr_year(curr_year, sizeof(curr_year) / sizeof(curr_year[0]));
  const struct Key_value map[] =
    {
     {
      .key = "BULLETINSFORM_TITLE_LABEL",
      .value = labels[BULLETINSFORM_TITLE_INDEX]
     },
     {
      .key = "BULLETINSFORM_INFO_LABEL",
      .value = labels[BULLETINSFORM_INFO_INDEX]
     },
     {
      .key = "BULLETINSFORM_CONTACTS_LABEL",
      .value = labels[BULLETINSFORM_CONTACTS_INDEX]
     },
     {
      .key = "BULLETINSFORM_CITY_LABEL",
      .value = labels[BULLETINSFORM_CITY_INDEX]
     },
     {
      .key = "BULLETINSFORM_PRICE_LABEL",
      .value = labels[BULLETINSFORM_PRICE_INDEX]
     },
     {.key = "LOGIN", .value = username},
     { .key = "CURRENT_YEAR", .value = curr_year },
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_addbulletin.html", map, NULL);
}
