CREATE TABLE IF NOT EXISTS deleted_messages (
	id INTEGER PRIMARY KEY,
	message_id INTEGER,
	user_id INTEGER,

	FOREIGN KEY (message_id) REFERENCES messages(id),
	FOREIGN KEY (user_id) REFERENCES users(id)
);
