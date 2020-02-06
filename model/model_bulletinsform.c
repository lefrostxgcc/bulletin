#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model_bulletinsform.h"
#include "../controller/session.h"

#define MAX_CONTENT_LEN 3200
#define MAX_FIELD_LEN 255

int
model_bulletinsform_validate(const struct Model_bulletinsform *bulletinsform)
{
  int status = BULLETINSFORM_VALID;
  if (strlen(bulletinsform->title) == 0)
    status |= EMPTY_BULLETINSFORM_TITLE;
  if (strlen(bulletinsform->info) == 0)
    status |= EMPTY_BULLETINSFORM_INFO;
  if (strlen(bulletinsform->contacts) == 0)
    status |= EMPTY_BULLETINSFORM_CONTACTS;
  if (strlen(bulletinsform->city) == 0)
    status |= EMPTY_BULLETINSFORM_CITY;
  if (bulletinsform->price == 0)
    status |= EMPTY_BULLETINSFORM_PRICE;
  return status;
}

const char **model_bulletinsform_attribute_labels(void)
{
  static const char *labels[BULLETINSFORM_ELEMENT_COUNT] =
    {
     [BULLETINSFORM_TITLE_INDEX] = "Заголовок",
     [BULLETINSFORM_INFO_INDEX] = "Информация",
     [BULLETINSFORM_CONTACTS_INDEX] = "Контакты",
     [BULLETINSFORM_CITY_INDEX] = "Город",
     [BULLETINSFORM_PRICE_INDEX] = "Цена",
    };
  return labels;
}

int
model_bulletinsform_load_by_post_request(struct Model_bulletinsform *form)
{
  const char *content_length = getenv("CONTENT_LENGTH");
  if (content_length == NULL)
      return 0;
  int length = atoi(content_length);
  if (length <= 0)
    return 0;
  char *content = malloc((length + 1) * sizeof(char));
  fread(content, length * sizeof(char), 1, stdin);
  content[length] = '\0';
  unescape_url(content);
  memset(form, '\0', sizeof(struct Model_bulletinsform));
  char *info = malloc(length * sizeof(char) + 1);
  info[0] = '\0';
  sscanf(content,
	 "title=%255[^&]&info=%[^&]&contacts=%255[^&]"
	 "&city=%255[^&]&price=%lf",
	 form->title, info, form->contacts,
	 form->city, &form->price);
  size_t info_len = strlen(info);
  form->info = malloc((info_len + 1) * sizeof(char));
  form->info[0] = '\0';
  strcpy(form->info, info);
  free(info);
  free(content);
  return 1;
}

void
model_bulletinsform_init_from_bulletin(struct Model_bulletinsform *form,
				       const struct Model_bulletins *bulletin)
{
  memset(form, '\0', sizeof(struct Model_bulletinsform));
  strcpy(form->title, bulletin->title);
  form->info = malloc(strlen(bulletin->info) * sizeof(char));
  form->info[0] = '\0';
  strcpy(form->info, bulletin->info);
  strcpy(form->contacts, bulletin->contacts);
  strcpy(form->city, bulletin->city);
  form->price = bulletin->price;
}

void model_bulletinsform_free(struct Model_bulletinsform *form)
{
  if (form)
    {
      free(form->info);
    }
}
