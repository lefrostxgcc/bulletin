#ifndef VIEW_SITE_H
#define VIEW_SITE_H

#include "../../model/model_bulletins.h"

void render_site_login(void);
void render_site_login_fail(const char *username);
void render_site_welcome(int user_id, int remember);

void render_site_index(const char *username,
		       const struct Model_bulletins *bulletins);

void render_site_index_guest(const struct Model_bulletins *bulletins);

void render_site_logout(int user_id);

void render_site_view_bulletin(const char *username,
			       const struct Model_bulletins *bulletin);

void render_site_view_bulletin_guest(const struct Model_bulletins *bulletin);


#endif
