#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "model_photoform.h"

static bool ends_with(const char *str, const char *pat)
{
  if (!str || !pat)
    return false;
  const char *s = str + strlen(str);
  const char *p = pat + strlen(pat);
  while (s != str && p != pat)
    if (*--s != *--p)
      return false;
  return p == pat;
}

int model_photoform_validate(const struct Model_photoform *photoform)
{
  int status = PHOTOFORM_VALID;
  if (photoform->file_size == 0)
    status |= PHOTOFORM_FILE_EMPTY;
  if (
      !ends_with(photoform->filename, ".png") &&
      !ends_with(photoform->filename, ".jpg")
      )
    status |= PHOTOFORM_FILE_INVALID_EXTENSION;
  return status;
}

const char **model_photoform_attribute_labels(void)
{
  static const char *labels[PHOTOFORM_ELEMENT_COUNT] =
    {
     [PHOTOFORM_FILE_INDEX] = "Загрузить изображение",
     [PHOTOFORM_LINK_INDEX] = "Ссылка",
     [PHOTOFORM_INFO_INDEX] = "Информация",
    };
  return labels;
}

static void *read_post_content(int *content_len)
{
  if (!getenv("CONTENT_LENGTH"))
      return NULL;
  *content_len = atoi(getenv("CONTENT_LENGTH"));
  void *data = malloc(*content_len);
  fread(data, *content_len, 1, stdin);
  return data;
}

static void *find_img_start(void *content, int content_len)
{
  const char *img_head = "Content-Type: image/png\r\n\r\n";
  const size_t img_head_len = strlen(img_head);
  void *img_start = memmem(content, content_len, img_head, img_head_len);
  return img_start ? img_start + img_head_len : NULL;
}

static void *find_img_end(void *img_start, int content_len)
{
  return memmem(img_start, content_len, "\r\n\x2d\x2d", 4);
}

static char *read_filename(void *content, int content_len)
{
  char *filename = calloc(1, 256);
  if (!filename)
    return NULL;
  const char *filename_head = "filename=";
  const char *filename_start = memmem(content, content_len,
				      filename_head, strlen(filename_head));
  sscanf(filename_start, "filename=\"%255[^\"]\"", filename);
  return filename;
}

static char *add_time_to_filename(const char *filename)
{
  char *newname = calloc(1, 512);
  if (!newname)
    return NULL;
  strcat(newname, "images/");
  strcat(newname, filename);
  char *newname_end = strrchr(newname, '.');
  if (!newname_end)
    newname_end = newname + strlen(newname_end);
  sprintf(newname_end, "_%ld", time(NULL));
  const char *filename_ext = strrchr(filename, '.');
  if (filename_ext)
      strcat(newname, filename_ext);
  return newname;
}

static void save_image_in_file(const char *filename, void *data, int len)
{
  FILE *f = fopen(filename, "wb");
  if (!f)
    return;
  fwrite(data, len, 1, f);
  fclose(f);
}

static struct Model_photoform *
model_photoform_new_from_content(void *img_start, size_t img_size,
				 const char *filename)
{
  struct Model_photoform *photoform =
    calloc(1, sizeof(struct Model_photoform));
  photoform->file = calloc(1, img_size);
  memcpy(photoform->file, img_start, img_size);
  photoform->file_size = img_size;
  strcpy(photoform->filename, filename);
  strcpy(photoform->link, "link");
  strcpy(photoform->info, "info");
  return photoform;
}

struct Model_photoform *model_photoform_load_by_post_request(void)
{
  void *content = NULL;
  char *content_filename = NULL;
  char *filename = NULL;
  struct Model_photoform *photoform = NULL;
  int content_len = 0;
  content = read_post_content(&content_len);
  if (!content)
    goto cleanup;
  void *img_start = find_img_start(content, content_len);
  if (!img_start)
    goto cleanup;
  void *img_end = find_img_end(img_start, content_len - (img_start - content));
  if (!img_end)
    goto cleanup;
  content_filename = read_filename(content, content_len);
  if (!content_filename)
    goto cleanup;
  filename = add_time_to_filename(content_filename);
  if (!filename)
    goto cleanup;
  const size_t img_size = img_end - img_start;
  save_image_in_file(filename, img_start, img_size);
  photoform =
    model_photoform_new_from_content(img_start, img_size, filename);
 cleanup:
  free(content);
  free(content_filename);
  free(filename);
  return photoform;
}

void model_photoform_free(struct Model_photoform *photoform)
{
  if (photoform)
    {
      free(photoform->file);
      free(photoform);
    }
}
