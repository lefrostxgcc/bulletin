#ifndef VIEW_SITE_H
#define VIEW_SITE_H

void render_site_login(void);
void render_site_login_fail(const char *username);
void render_site_welcome(int user_id);
void render_site_index(const char *username);
void render_site_logout(int user_id);

#endif
