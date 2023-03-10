CREATE TABLE IF NOT EXISTS user_contacts (
	id INTEGER PRIMARY KEY,
	username VARCHAR(40),
	first_name VARCHAR(40),
	last_name VARCHAR(40),
	email VARCHAR(255),
	phone VARCHAR(16),
	updated_at VARCHAR(27)
);
