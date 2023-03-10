CREATE TABLE IF NOT EXISTS users (
	id INTEGER PRIMARY KEY,
	created_at VARCHAR(27),
	updated_at VARCHAR(27),
	deleted_at VARCHAR(27),
	FOREIGN KEY (id) REFERENCES user_contacts(id),
	FOREIGN KEY (id) REFERENCES user_statuses(id)
);
