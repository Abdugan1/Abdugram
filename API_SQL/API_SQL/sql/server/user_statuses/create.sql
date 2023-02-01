CREATE TABLE IF NOT EXISTS user_statuses (
	id INTEGER PRIMARY KEY,
	is_active BOOLEAN,
	last_time_active VARCHAR(27),
	avatar TEXT,
	url TEXT,
	updated_at VARCHAR(27)
);
