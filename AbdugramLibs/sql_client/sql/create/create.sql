CREATE TABLE IF NOT EXISTS users (
  id INTEGER PRIMARY KEY,
  username TEXT UNIQUE,
  first_name TEXT,
  email TEXT UNIQUE,
  phone TEXT,
  avatar_url TEXT,
  is_online INTEGER,
  last_time_online DATETIME,
  url_to_profile TEXT,
  created_at DATETIME,
  updated_at DATETIME,
  deleted_at DATETIME
);

CREATE TABLE IF NOT EXISTS chats (
  id INTEGER PRIMARY KEY,
  name TEXT,
  description TEXT,
  picture_url TEXT,
  type TEXT CHECK(type IN ('private', 'group', 'channel')),
  created_at DATETIME,
  updated_at DATETIME,
  deleted_at DATETIME
);

CREATE TABLE IF NOT EXISTS chat_users (
  chat_id INTEGER,
  user_id INTEGER,
  role TEXT CHECK (role IN('owner', 'admin', 'user')),
  joined_at DATETIME,
  left_at DATETIME,
  updated_at DATETIME,
  PRIMARY KEY (chat_id, user_id),
  FOREIGN KEY (chat_id) REFERENCES chats(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS messages (
  id INTEGER PRIMARY KEY,
  chat_id INTEGER,
  sender_id INTEGER,
  reply_to_id INTEGER,
  text TEXT,
  is_edited INTEGER,
  created_at DATETIME,
  updated_at DATETIME,
  FOREIGN KEY (chat_id) REFERENCES chats(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (reply_to_id) REFERENCES messages(id) ON DELETE CASCADE ON UPDATE CASCADE
);


CREATE TABLE IF NOT EXISTS message_deletions (
  id INTEGER PRIMARY KEY,
  message_id INTEGER,
  deleted_for_user_id INTEGER,
  deleted_at DATETIME,
  FOREIGN KEY (message_id) REFERENCES messages(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (deleted_for_user_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS message_reads (
  id INTEGER PRIMARY KEY,
  message_id INTEGER,
  user_id INTEGER,
  read_at DATETIME,
  FOREIGN KEY (message_id) REFERENCES messages(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE VIEW IF NOT EXISTS chats_view AS
SELECT chats.id AS chat_id, chats.name AS chat_name, chats.picture_url AS picture_url, chats.type AS chat_type, messages.text AS last_message, messages.created_at AS message_date
FROM chats
LEFT JOIN messages ON chats.id = messages.chat_id
GROUP BY chats.id
ORDER BY MAX(messages.created_at) DESC;
