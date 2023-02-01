ALTER TABLE users ADD CONSTRAINT fk_users_id_to_user_contacts_id FOREIGN KEY IF NOT EXISTS (id) REFERENCES user_contacts(id);
ALTER TABLE users ADD CONSTRAINT fk_users_id_to_user_statuses_id FOREIGN KEY IF NOT EXISTS (id) REFERENCES user_statuses(id);
