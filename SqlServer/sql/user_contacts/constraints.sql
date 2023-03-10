ALTER TABLE user_contacts ADD CONSTRAINT fk_user_contacts_id_to_users_id FOREIGN KEY IF NOT EXISTS (id) REFERENCES users(id);
