#include <stdio.h>
#include "view_bulletins.h"
#include "../../model/model_bulletinsform.h"
#include "../read_replace_write.h"

void render_bulletins_editbulletin(const char *username,
				   const struct Model_bulletinsform *form,
				   int bulletins_id)
{
  char price_buf[255] = {'\0'};
  snprintf(price_buf,
	   sizeof(price_buf) / sizeof(price_buf[0]),
	   "%.2f",
	   form->price);
  char id_buf[255] = {'\0'};
  snprintf(id_buf,
	   sizeof(id_buf) / sizeof(id_buf[0]),
	   "%d",
	   bulletins_id);

  const char **labels = model_bulletinsform_attribute_labels();
  const struct Key_value map[] =
    {
     {
      .key = "BULLETINS_ID",
      .value = id_buf
     },
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
     {
      .key = "BULLETINSFORM_TITLE",
      .value = form->title
     },
     {
      .key = "BULLETINSFORM_INFO",
      .value = form->info
     },
     {
      .key = "BULLETINSFORM_CONTACTS",
      .value = form->contacts
     },
     {
      .key = "BULLETINSFORM_CITY",
      .value = form->city
     },
     {
      .key = "BULLETINSFORM_PRICE",
      .value = price_buf
     },
     {.key = "LOGIN", .value = username},
     {.key = NULL, .value = NULL}
    };
  read_replace_write("htmlt/bulletins_editbulletin.html", map, NULL);
}
