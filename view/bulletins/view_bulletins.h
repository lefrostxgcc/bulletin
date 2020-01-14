#ifndef VIEW_BULLETINS_H
#define VIEW_BULLETINS_H

void render_bulletins_index(const char *username);
void render_bulletins_index_public(const char *username);
void render_bulletins_index_wait(const char *username);
void render_bulletins_index_deleted(const char *username);
void render_bulletins_addbulletin(const char *username);

#endif
