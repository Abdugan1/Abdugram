CREATE TABLE IF NOT EXISTS messages (
	id INTEGER PRIMARY KEY,
	sender_id INTEGER,
	conversation_id INTEGER,
	text_content VARCHAR(255),
	created_at VARCHAR(27),
	updated_at VARCHAR(27),

	FOREIGN KEY (id) REFERENCES deleted_messages(message_id),
	FOREIGN KEY (sender_id) REFERENCES users(id),
	FOREIGN KEY (conversation_id) REFERENCES conversations(id)
);
