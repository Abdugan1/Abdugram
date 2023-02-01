ALTER TABLE user_statuses ADD CONSTRAINT fk_user_statuses_id_to_users_id FOREIGN KEY IF NOT EXISTS (id) REFERENCES users(id);
