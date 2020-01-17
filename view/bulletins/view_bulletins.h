#ifndef VIEW_BULLETINS_H
#define VIEW_BULLETINS_H

#include "../../model/model_bulletins.h"
#include "../../model/model_bulletinsform.h"

void render_bulletins_index(const char *username,
				 const struct Model_bulletins bulletins[]);
void render_bulletins_index_wait(const char *username,
				 const struct Model_bulletins bulletins[]);
void render_bulletins_index_public(const char *username,
				 const struct Model_bulletins bulletins[]);
void render_bulletins_index_deleted(const char *username,
				 const struct Model_bulletins bulletins[]);

void render_bulletins_addbulletin(const char *username);
void render_bulletins_editbulletin(const char *username,
				   const struct Model_bulletinsform *form,
				   int bulletins_id);

#endif
